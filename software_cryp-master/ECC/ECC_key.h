#pragma once
#ifndef ECC_KEY_H
#define ECC_KEY_H

#include <string>

namespace ECC {
class PublicKey;
class PrivateKey;
}  // namespace ECC

#include "./ECC.h"

namespace ECC {
class PublicKey {
   public:
    EC::point p;
    const EC::curve *c;
    PublicKey();
    constexpr PublicKey(const EC::point _p, const EC::curve *_c)
        : p(_p), c(_c) {}
    void read(std::string path);
    void save(std::string path);
};
class PrivateKey {
   public:
    unsigned_bigint<4> k;
    PrivateKey();
    constexpr PrivateKey(unsigned_bigint<4> _k) : k(_k) {}
    static PrivateKey Generate();

    void read(std::string path);
    void save(std::string path);
};
}  // namespace ECC

#endif
