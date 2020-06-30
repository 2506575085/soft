#pragma once
#pragma once
#ifndef RSA_Decryption_H
#define RSA_Decryption_H
#include <cstring>
#include <fstream>
#include <string>
#include "../bigint/unsigned_bigint.h"
#include "RSA_key.h"

namespace RSA {
template <int LEN>
int DecryptionFile(const PrivateKey<LEN> &private_key, std::string file_path,
                   std::string output_path,
                   void (*callback)(size_t, size_t, void *) =
                       [](size_t, size_t, void *) {},
                   void *extdata = nullptr);
template <int LEN>
int DecryptionMessage(const PrivateKey<LEN> &public_key,
                      const unsigned_bigint<LEN> &secret,
                      unsigned_bigint<LEN> &message);
template <int LEN>
int DecryptionFile(const PrivateKey<LEN> &private_key, std::string file_path,
                   std::string output_path,
                   void (*callback)(size_t, size_t, void *), void *extdata) {
    // 打开文件
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) return 1;
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0);

    // 检查文件头信息
    char str[] = "RSAENCRY", tmp[9];
    file.read(tmp, 8);
    tmp[8] = '\0';
    if (std::strcmp(str, tmp) != 0) {
        file.close();
        output.close();
        return 1;
    }
    unsigned long long len;
    file.read(reinterpret_cast<char *>(&len), sizeof len);
    if (len != LEN) {
        file.close();
        output.close();
        return 2;
    }

    // 解密数据
    unsigned_bigint<LEN> data, secret;
    while (!file.eof()) {
        file.read(reinterpret_cast<char *>(secret.data), sizeof secret.data);
        if (file.gcount() == 0) break;
        DecryptionMessage(private_key, secret, data);
        output.write(reinterpret_cast<char *>(&data.data[0]),
                     data.data[LEN - 1]);
        callback(file.tellg(), file_size, extdata);
    }
    file.close();
    output.close();
    return 0;
}

template <int LEN>
int DecryptionMessage(const PrivateKey<LEN> &private_key,
                      const unsigned_bigint<LEN> &secret,
                      unsigned_bigint<LEN> &message) {
    const unsigned_bigint<LEN> &N = private_key.N;
    const unsigned_bigint<LEN / 2> &p = private_key.p, &q = private_key.q,
                                   &dp = private_key.dp, &dq = private_key.dq,
                                   &qInv = private_key.qInv,
                                   &pInv2 = private_key.pInv2,
                                   &pRmod = private_key.pRmod,
                                   &qInv2 = private_key.qInv2,
                                   &qRmod = private_key.qRmod;
    unsigned_bigint<LEN> m1, m2;

    unsigned_bigint<LEN / 2> h;
    if (secret > N) return 1;
    m1 = fast_pow_mod((unsigned_bigint<LEN / 2>)(secret % p), dp, p, pInv2,
                      pRmod);
    m2 = fast_pow_mod((unsigned_bigint<LEN / 2>)(secret % q), dq, q, qInv2,
                      qRmod);
    unsigned_bigint<LEN> m1_sub_m2;
    if (m1 >= m2) {
        m1_sub_m2 = (m1 - m2) % p;
    } else {
        m1_sub_m2 = (unsigned_bigint<LEN>)p - ((m2 - m1) % p);
    }
    h = multiply_mod(qInv, (unsigned_bigint<LEN / 2>)m1_sub_m2, p);
    message = m2 + (unsigned_bigint<LEN>)h * (unsigned_bigint<LEN>)q;
    return 0;
}
}  // namespace RSA
#endif
