#pragma once
#ifndef RSA_Encryption_H
#define RSA_Encryption_H
#include <fstream>
#include <string>
#include "../bigint/unsigned_bigint.h"
#include "RSA_key.h"

namespace RSA {
template <int LEN>
int EncryptionFile(const PublicKey<LEN> &public_key, std::string file_path,
                   std::string output_path,
                   void (*callback)(size_t, size_t, void *) =
                       [](size_t, size_t, void *) {},
                   void *extdata = nullptr);
template <int LEN>
int EncryptionMessage(const PublicKey<LEN> &public_key,
                      const unsigned_bigint<LEN> &message,
                      unsigned_bigint<LEN> &secret);
namespace {
// 对指数为65537时进行特化，使用加法链实现，理论上可以提升5%的性能
template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_65537(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv);
// 对指数为5时进行特化，使用加法链实现，理论上可以提升25%的性能
template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_5(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv);
// 对指数为3时进行特化，使用加法链实现，理论上可以提升33%的性能
template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_3(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv);
}  // namespace
template <int LEN>
int EncryptionFile(const PublicKey<LEN> &public_key, std::string file_path,
                   std::string output_path,
                   void (*callback)(size_t, size_t, void *), void *extdata) {
    // 打开文件
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) return 1;
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0);

    // 输出文件头
    output << "RSAENCRY";
    unsigned long long len = LEN;
    output.write(reinterpret_cast<char *>(&len), sizeof(unsigned long long));

    // 加密数据
    while (!file.eof()) {
        unsigned_bigint<LEN> data, secret;
        file.read(reinterpret_cast<char *>(&(data.data[0])),
                  sizeof(data.data[0]) * (LEN - 1));
        data.data[LEN - 1] = file.gcount();
        EncryptionMessage(public_key, data, secret);
        output.write(reinterpret_cast<char *>(secret.data), sizeof secret.data);
        callback(file.tellg(), file_size, extdata);
    }

    file.close();
    output.close();
    return 0;
}

template <int LEN>
int EncryptionMessage(const PublicKey<LEN> &public_key,
                      const unsigned_bigint<LEN> &message,
                      unsigned_bigint<LEN> &secret) {
    const unsigned_bigint<LEN> &N = public_key.N, &e = public_key.e,
                               &NInv = public_key.NInv;
    if (message > N) return 1;
    if (e == 65537) {
        secret = fast_pow_mod_65537(message, N, NInv);
    } else if (e == 3) {
        secret = fast_pow_mod_3(message, N, NInv);
    } else if (e == 5) {
        secret = fast_pow_mod_5(message, N, NInv);
    } else {
        secret = fast_pow_mod(message, e, N, NInv);
    }
    return 0;
}

namespace {
template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_65537(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv) {
    assert(mod.bit(0) == 1);  // 模数必须与2^64互质，换言之必须是奇数
    unsigned_bigint<LEN> a_pow[17], ans;
    a_pow[0] = a.toMontgomery(mod);
    // 转换完毕
    for (int i = 1; i < 17; i++) {
        a_pow[i] =
            multiply_mod_Montgomery(a_pow[i - 1], a_pow[i - 1], mod, modInv);
    }
    ans = multiply_mod_Montgomery(a, a_pow[16], mod, modInv);
    return ans;
}

template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_5(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv) {
    assert(mod.bit(0) == 1);  // 模数必须与2^64互质，换言之必须是奇数
    unsigned_bigint<LEN> a_pow[3], ans;
    a_pow[0] = a.toMontgomery(mod);
    // 转换完毕
    for (int i = 1; i < 3; i++) {
        a_pow[i] =
            multiply_mod_Montgomery(a_pow[i - 1], a_pow[i - 1], mod, modInv);
    }
    ans = multiply_mod_Montgomery(a, a_pow[2], mod, modInv);
    return ans;
}

template <int LEN>
constexpr unsigned_bigint<LEN> fast_pow_mod_3(
    const unsigned_bigint<LEN> a, const unsigned_bigint<LEN> mod,
    const unsigned_bigint<LEN> modInv) {
    assert(mod.bit(0) == 1);  // 模数必须与2^64互质，换言之必须是奇数
    unsigned_bigint<LEN> a_pow[2], ans;
    a_pow[0] = a.toMontgomery(mod);
    // 转换完毕
    a_pow[1] = multiply_mod_Montgomery(a_pow[0], a_pow[0], mod, modInv);
    ans = multiply_mod_Montgomery(a, a_pow[1], mod, modInv);
    return ans;
}
}  // namespace
}  // namespace RSA
#endif
