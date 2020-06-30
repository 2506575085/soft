#pragma once
#ifndef RSA_Generate_H
#define RSA_Generate_H
#include <array>
#include <chrono>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include "../bigint/unsigned_bigint.h"
#include "RSA_key.h"

namespace RSA {
template <int LEN>
void Generate(PublicKey<LEN> &public_key, PrivateKey<LEN> &private_key,
              int jobs = 1, bool verbose = false);
namespace {
template <int LEN>
unsigned_bigint<LEN> generate_prime_number(int jobs);
template <int LEN>
int get_Naf_weight(unsigned_bigint<LEN> n);
}  // namespace

template <int LEN>
void Generate(PublicKey<LEN> &public_key, PrivateKey<LEN> &private_key,
              int jobs, bool verbose) {
    bool store = 0;
    unsigned_bigint<LEN> s;
    while (1) {
        unsigned_bigint<LEN> p,
            q = (unsigned_bigint<LEN>)(generate_prime_number<LEN / 2>(jobs));
        if (store) {
            p = s;
        } else {
            p = (unsigned_bigint<LEN>)(generate_prime_number<LEN / 2>(jobs));
        }
        store = 0;
        if (verbose)
            std::clog << std::hex << "p = " << p << std::endl
                      << "q = " << q << std::endl
                      << "|p-q| = " << (p > q ? p - q : q - p) << std::endl;
        unsigned_bigint<LEN> N = p * q, r = (p - 1) * (q - 1), e = 65537, d, y;
        if (r % e == 0) {
            if (verbose)
                std::clog << "regenerate prime number. r and e are not coprime"
                          << std::endl
                          << std::endl;
            continue;
        }
        if (get_Naf_weight(N) < (LEN * 64 >> 2)) {
            if (verbose)
                std::clog << "regenerate prime number. Naf weight is too small"
                          << std::endl
                          << std::endl;
            continue;
        }
        if (N.bit(LEN * 64 - 1) == 0) {
            if (verbose)
                std::clog << "regenerate prime number. N is not a " << std::dec
                          << LEN * 64 << std::hex << " bits number" << std::endl
                          << std::endl;
            store = 1;
            s = p > q ? p : q;
            continue;
        }
        if ((LEN * 64 / 2 - 100 > 0 &&
             (((p > q ? p - q : q - p) >> (LEN * 64 / 2 - 100)) ==
              unsigned_bigint<LEN>(0))) ||
            (((p > q ? p - q : q - p) >> (LEN * 64 / 3)) ==
             unsigned_bigint<LEN>(0))) {
            if (verbose)
                std::clog << "regenerate prime number. |p-q| is too small"
                          << std::endl
                          << "|p-q| = " << (p > q ? p - q : q - p) << std::endl
                          << ((p > q ? p - q : q - p) >> (LEN * 64 / 2 - 100))
                          << std::endl
                          << ((p > q ? p - q : q - p) >> (LEN * 64 / 3))
                          << std::endl
                          << std::endl;
            continue;
        }
        exgcd(e, r, d, y);  // ed - ry = 1 也即 ed mod r = 1
        if (verbose)
            std::clog << "r = " << r << std::endl
                      << "e = " << e << std::endl
                      << "d = " << d << std::endl;

        if (d <= (unsigned_bigint<LEN>(1) << (LEN * 64 / 2))) {
            if (verbose)
                std::clog << "regenerate prime number. d is too small"
                          << std::endl
                          << std::endl;
            continue;
        }
        // 使用中国剩余定理加速解密
        // https://blog.csdn.net/mrpre/article/details/79671263
        unsigned_bigint<LEN> dp, dq, qInv;
        dp = d % (p - 1);
        dq = d % (q - 1);
        // exgcd(q, p, qInv, y);
        // 这是素数，用扩展欧几里得可能会爆栈
        // 我们用费马小定理
        qInv = fast_pow_mod(q, p - 2, p);
        if (verbose)
            std::clog << "public key(N, e) = (" << N << ',' << e << ')'
                      << std::endl
                      << "private key(N, d, p, q, dp, dq, qInv) = (" << N << ','
                      << d << ',' << p << ',' << q << ',' << dp << ',' << dq
                      << ',' << qInv << ')' << std::endl;

        public_key.N = N;
        public_key.e = e;
        private_key.N = N;
        private_key.d = d;
        private_key.p = (unsigned_bigint<LEN / 2>)p;
        private_key.q = (unsigned_bigint<LEN / 2>)q;
        private_key.dp = (unsigned_bigint<LEN / 2>)dp;
        private_key.dq = (unsigned_bigint<LEN / 2>)dq;
        private_key.qInv = (unsigned_bigint<LEN / 2>)qInv;
        public_key.flash();
        private_key.flash();
        break;
    }
}

namespace {
template <int LEN>
unsigned_bigint<LEN> generate_prime_number(int jobs) {
    unsigned_bigint<LEN> a;
    while (a.bit(LEN * 64 - 1) == 0) {
        a = unsigned_bigint<LEN>::randIntel();
    }
    if (a.bit(0) == 0) a++;
    const std::array<int, 303> sieve = {
        2,    3,    5,    7,    11,   13,   17,   19,   23,   29,   31,   37,
        41,   43,   47,   53,   59,   61,   67,   71,   73,   79,   83,   89,
        97,   101,  103,  107,  109,  113,  127,  131,  137,  139,  149,  151,
        157,  163,  167,  173,  179,  181,  191,  193,  197,  199,  211,  223,
        227,  229,  233,  239,  241,  251,  257,  263,  269,  271,  277,  281,
        283,  293,  307,  311,  313,  317,  331,  337,  347,  349,  353,  359,
        367,  373,  379,  383,  389,  397,  401,  409,  419,  421,  431,  433,
        439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,
        509,  521,  523,  541,  547,  557,  563,  569,  571,  577,  587,  593,
        599,  601,  607,  613,  617,  619,  631,  641,  643,  647,  653,  659,
        661,  673,  677,  683,  691,  701,  709,  719,  727,  733,  739,  743,
        751,  757,  761,  769,  773,  787,  797,  809,  811,  821,  823,  827,
        829,  839,  853,  857,  859,  863,  877,  881,  883,  887,  907,  911,
        919,  929,  937,  941,  947,  953,  967,  971,  977,  983,  991,  997,
        1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
        1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163,
        1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249,
        1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321,
        1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439,
        1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
        1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601,
        1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693,
        1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783,
        1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877,
        1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987,
        1993, 1997, 1999};
    std::vector<std::future<void>> v;
    std::promise<unsigned_bigint<LEN>> numbers_promise;
    auto numbers_ready = numbers_promise.get_future();
    bool flag = true;
    for (int i = 0; i < jobs; i++) {
        v.push_back(std::async(
            std::launch::async,
            [&](unsigned_bigint<LEN> a) {
                std::array<int, 303> mod;
                for (int i = 0; i < sieve.size(); i++) {
                    mod[i] = (int)((unsigned long long)(a % sieve[i]));
                }
                while (flag) {
                    for (int i = 0; i < sieve.size(); i++) {
                        if (mod[i] == 0) {
                            goto next_loop;
                        }
                    }
                    if (flag && a.is_prime_number(8, false)) {
                        flag = false;
                        numbers_promise.set_value(a);
                        return;
                    }

                next_loop:
                    a += 2 * jobs;
                    for (int i = 0; i < sieve.size(); i++) {
                        mod[i] += 2 * jobs;
                        if (mod[i] >= sieve[i]) mod[i] -= sieve[i];
                    }
                }
            },
            a));
        a += 2;
    }
    numbers_ready.wait();
    return numbers_ready.get();
}

template <int LEN>
int get_Naf_weight(unsigned_bigint<LEN> n) {
    unsigned_bigint<LEN> m = (n << 1) + n;
    m = m | n;
    int ans = 0;
    for (int i = 0; i < LEN * 64; i++) {
        if (m.bit(i) == 1) {
            ans++;
        }
    }
    return ans;
}
}  // namespace
}  // namespace RSA
#endif
