#pragma once
#ifndef EC_H
#define EC_H

#include "../bigint/unsigned_bigint.h"

namespace EC {
class point;
class point_jacobi;
class curve;

class point {
   private:
   public:
    const curve* c;
    unsigned_bigint<4> x = 0, y = 0;
    constexpr point() : c(nullptr) {}
    constexpr point(const unsigned_bigint<4> x, const unsigned_bigint<4> y,
                    const curve* _c)
        : c(_c) {
        this->x = x;
        this->y = y;
    }
    point(point_jacobi& p);
    curve getCurve() const;
    point_jacobi operator+(point b) const;
    point_jacobi operator*(unsigned_bigint<4> k) const;
    point& operator=(point_jacobi b);
};
point_jacobi operator*(unsigned_bigint<4> k, point a);

class point_jacobi {
   public:
    const curve* c;
    unsigned_bigint<4> X, Y, Z;
    point_jacobi();
    point_jacobi(const point p);
    curve getCurve() const;
    point_jacobi double_point() const;
    point_jacobi operator+(const point_jacobi b) const;
    point_jacobi operator*(unsigned_bigint<4> k) const;
};

class curve {
   private:
   public:
    const unsigned_bigint<4> a, b, p;
    // 预计算参数
    unsigned_bigint<4> modInv;
    const point G;
    curve(const unsigned_bigint<4> &_a, const unsigned_bigint<4> &_b,
          const unsigned_bigint<4> &_p, const unsigned_bigint<4> &_Gx,
          const unsigned_bigint<4> &_Gy);

    bool operator==(curve b) const;
};

}  // namespace EC

#endif
