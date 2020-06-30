#pragma once
#ifndef RSA_key_H
#define RSA_key_H

#include <fstream>
#include <string>
#include "../bigint/unsigned_bigint.h"

namespace RSA {
template <int LEN>
class PublicKey {
   public:
    unsigned_bigint<LEN> N, e, NInv;
    void read(std::string path);
    void flash();
    void save(std::string path);
    ~PublicKey();
};
template <int LEN>
class PrivateKey {
   public:
    unsigned_bigint<LEN> N, d;
    unsigned_bigint<LEN / 2> p, q, dp, dq, qInv;

    // 预计算参数
    unsigned_bigint<LEN / 2> qInv2, pInv2, pRmod, qRmod;
    void read(std::string path);
    void flash();
    void save(std::string path);
    ~PrivateKey();
};

template <int LEN>
void PublicKey<LEN>::read(std::string path) {
    std::ifstream public_key(path);
    public_key >> std::hex >> this->N >> this->e;
    flash();
}
template <int LEN>
void PublicKey<LEN>::flash() {
    unsigned_bigint<LEN> y;
    exgcd(unsigned_bigint<LEN>(1) << 64, N, y, NInv);
}

template <int LEN>
void PublicKey<LEN>::save(std::string path) {
    std::ofstream public_key(path);
    public_key << std::hex << this->N << '\n' << this->e << '\n';
}

template <int LEN>
PublicKey<LEN>::~PublicKey() {
    memset(this, 0xcc, sizeof this);
}

template <int LEN>
void PrivateKey<LEN>::read(std::string path) {
    std::ifstream private_key(path);
    private_key >> std::hex >> this->N >> this->d >> this->p >> this->q >>
        this->dp >> this->dq >> this->qInv;
    flash();
}

template <int LEN>
void PrivateKey<LEN>::flash() {
    unsigned_bigint<LEN / 2> y;
    exgcd(unsigned_bigint<LEN / 2>(1) << 64, p, y, pInv2);
    exgcd(unsigned_bigint<LEN / 2>(1) << 64, q, y, qInv2);
    pRmod = unsigned_bigint<LEN / 2>(1).toMontgomery(p);
    qRmod = unsigned_bigint<LEN / 2>(1).toMontgomery(q);
}

template <int LEN>
void PrivateKey<LEN>::save(std::string path) {
    std::ofstream private_key(path);
    private_key << std::hex << this->N << '\n'
                << this->d << '\n'
                << this->p << '\n'
                << this->q << '\n'
                << this->dp << '\n'
                << this->dq << '\n'
                << this->qInv << '\n';
}

template <int LEN>
PrivateKey<LEN>::~PrivateKey() {
    memset(this, 0xcc, sizeof this);
}
}  // namespace RSA
#endif
