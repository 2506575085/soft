#pragma once
#ifndef ECC_H
#define ECC_H

#include <utility>
#include <vector>

#include "./EC.h"
#include "./ECC_key.h"

namespace ECC {
typedef std::pair<EC::point, unsigned_bigint<4>> Trinum;
Trinum encrypt(const EC::point PUB_KEY, const unsigned_bigint<4> M);
unsigned_bigint<4> decrypt(const EC::point G, const unsigned_bigint<4> sec_key,
                           const Trinum cipher);

class ECCInterface {
   private:
    const EC::curve& curve;
    const std::string identity;

   public:
    ECCInterface(const EC::curve& _curve, const std::string _identity)
        : curve(_curve), identity(_identity) {}

    ECC::PublicKey GenPubKey(const PrivateKey pri_key) const;

    Trinum encrypt(PublicKey PUB_KEY, unsigned_bigint<4> M) const;
    unsigned_bigint<4> decrypt(PrivateKey sec_key, Trinum cipher) const;

    int encryptFile(PublicKey PUB_KEY, std::string file_path,
                    std::string output_path) const;
    int decryptFile(PrivateKey sec_key, std::string file_path,
                    std::string output_path) const;
};

extern const EC::curve secp256k1_curve;
const ECCInterface secp256k1(secp256k1_curve, "ECC____SECP256K1");

extern const EC::curve secp256r1_curve;
const ECCInterface secp256r1(secp256k1_curve, "ECC____SECP256R1");

extern const EC::curve SM2_curve;
const ECCInterface SM2(SM2_curve, "ECC__________SM2");

}  // namespace ECC

#endif
