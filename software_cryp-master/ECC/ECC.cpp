#include "pch.h"

#include <fstream>
#include <string>

#include "./ECC.h"

using EC::curve;
using EC::point;

namespace ECC {
namespace {
unsigned_bigint<4> inverse(unsigned_bigint<4> n, unsigned_bigint<4> b) {
    unsigned_bigint<5> x, y;
    binexgcd(b, n, x, y);
    while (x.bit(5 * 64 - 1) == 1) {
        x += n;
    }
    x %= n;
    return (unsigned_bigint<4>)x;
}
}  // namespace
Trinum encrypt(const point PUB_KEY, const unsigned_bigint<4> M) {
    curve c = PUB_KEY.getCurve();
    point G = c.G;
    Trinum result;
    unsigned_bigint<4> M_new;
    point temp1;
    unsigned_bigint<4> r;
    r = unsigned_bigint<4>::rand();
    result.first = r * G;

    temp1 = r * PUB_KEY;

    result.second = multiply_mod(M, temp1.y, c.p);
    return result;
}

unsigned_bigint<4> decrypt(const point G, const unsigned_bigint<4> sec_key,
                           const Trinum cipher) {
    curve c = G.getCurve();
    point P, H;
    unsigned_bigint<4> enc_M, message, temp1;
    P = cipher.first;
    enc_M = cipher.second;
    H = sec_key * P;
    temp1 = inverse(c.p, H.y);
    message = multiply_mod(enc_M, temp1, c.p);
    return message;
}

ECC::PublicKey ECCInterface::GenPubKey(const PrivateKey pri_key) const {
	EC::point_jacobi p2 = pri_key.k * this->curve.G;
	EC::point p(p2);
    return PublicKey(p, &(this->curve));
}

Trinum ECCInterface::encrypt(PublicKey PUB_KEY, unsigned_bigint<4> M) const {
    assert(PUB_KEY.c == &(this->curve));
    return ECC::encrypt(PUB_KEY.p, M);
}

unsigned_bigint<4> ECCInterface::decrypt(PrivateKey sec_key,
                                         Trinum cipher) const {
    return ECC::decrypt(this->curve.G, sec_key.k, cipher);
}

int ECCInterface::encryptFile(PublicKey PUB_KEY, std::string file_path,
                              std::string output_path) const {
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) return 1;
    // 输出文件头
    output << this->identity.substr(0, 16);
    // 加密数据
    while (!file.eof()) {
        unsigned_bigint<4> data;
        Trinum secret;
        file.read(reinterpret_cast<char *>(&(data.data[0])),
                  sizeof(data.data) - 1);
        *(reinterpret_cast<unsigned char *>(data.data) + sizeof(data.data) - 1) =
            file.gcount();

        secret = this->encrypt(PUB_KEY, data);
        output.write(reinterpret_cast<char *>(secret.first.x.data),
                     sizeof secret.first.x.data);
        output.write(reinterpret_cast<char *>(secret.first.y.data),
                     sizeof secret.first.y.data);
        output.write(reinterpret_cast<char *>(secret.second.data),
                     sizeof secret.second.data);
    }

    file.close();
    output.close();
    return 0;
}

int ECCInterface::decryptFile(PrivateKey sec_key, std::string file_path,
                              std::string output_path) const {
    // 打开文件
    std::ifstream file(file_path, std::ios_base::binary | std::ios::in);
    std::ofstream output(output_path, std::ios_base::binary);
    if (!file.is_open()) return 1;
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0);

    // 检查文件头信息
    char str[17], tmp[17];
    memcpy(str, (this->identity).substr(0, 16).c_str(), 17);
    file.read(tmp, 16);
    tmp[16] = '\0';
    if (std::strcmp(str, tmp) != 0) {
        file.close();
        output.close();
        return 1;
    }

    // 解密数据
    unsigned_bigint<4> data;
    Trinum secret;
    while (!file.eof()) {
        unsigned_bigint<4> x, y;
        file.read(reinterpret_cast<char *>(x.data), sizeof x.data);
        file.read(reinterpret_cast<char *>(y.data), sizeof y.data);
        secret.first = EC::point(x, y, &(this->curve));
        file.read(reinterpret_cast<char *>(secret.second.data),
                  sizeof secret.second.data);

        if (file.gcount() == 0) break;
        data = this->decrypt(sec_key, secret);

        output.write(
            reinterpret_cast<char *>(&data.data[0]),
            *(reinterpret_cast<unsigned char *>(data.data) + sizeof(data.data) - 1));
    }
    file.close();
    output.close();
    return 0;
}

const EC::curve secp256k1_curve(
    unsigned_bigint<4>(0), unsigned_bigint<4>(7),
    unsigned_bigint<4>(
        "0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"),
    unsigned_bigint<4>(
        "0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"),
    unsigned_bigint<4>(
        "0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"));

const EC::curve secp256r1_curve(
    unsigned_bigint<4>(
        "0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFC"),
    unsigned_bigint<4>(
        "0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B"),
    unsigned_bigint<4>(
        "0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF"),
    unsigned_bigint<4>(
        "0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296"),
    unsigned_bigint<4>(
        "0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5"));

const EC::curve SM2_curve(
    unsigned_bigint<4>(
        "0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC"),
    unsigned_bigint<4>(
        "0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93"),
    unsigned_bigint<4>(
        "0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF"),
    unsigned_bigint<4>(
        "0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7"),
    unsigned_bigint<4>(
        "0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0"));

}  // namespace ECC
