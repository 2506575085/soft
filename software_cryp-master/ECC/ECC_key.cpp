#include "pch.h"

#include <fstream>

#include "./ECC_key.h"

namespace ECC {

PrivateKey::PrivateKey() {}
PrivateKey PrivateKey::Generate() {
    return PrivateKey(unsigned_bigint<4>::randIntel());
}

void PrivateKey::save(std::string path) {
    std::ofstream file(path);
    file << std::hex << this->k;
    file.close();
}

void PrivateKey::read(std::string path) {
    std::ifstream file(path);
    file >> std::hex >> this->k;
    file.close();
}

PublicKey::PublicKey() {}

void PublicKey::save(std::string path) {
    std::ofstream file(path);
    if (this->c == &secp256k1_curve) {
        file << "secp256k1\n";
    } else if (this->c == &secp256r1_curve) {
        file << "secp256r1\n";
    } else if (this->c == &SM2_curve) {
        file << "SM2\n";
    }
    file << std::hex << this->p.x << '\n' << this->p.y << '\n';
    file.close();
}

void PublicKey::read(std::string path) {
    std::ifstream file(path);
    std::string type;
    file >> type;
	file.get();
    const EC::curve *c = nullptr;
    if (type == "secp256k1") {
        c = &secp256k1_curve;
    } else if (type == "secp256r1") {
        c = &secp256r1_curve;
    } else if (type == "SM2") {
        c = &SM2_curve;
    }
    unsigned_bigint<4> x, y;
    file >> std::hex >> x >> y;
    this->c = c;
    this->p = EC::point(x, y, c);
    file.close();
}
}  // namespace ECC
