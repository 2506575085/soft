#include "pch.h"

#include <cassert>

#include "./EC.h"

namespace EC {
curve point::getCurve() const { return *c; }
curve point_jacobi::getCurve() const { return *c; }

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

unsigned_bigint<4> add_mod(const unsigned_bigint<4> &a,
                           const unsigned_bigint<4> &b,
                           const unsigned_bigint<4> &mod) {
    unsigned_bigint<4> ans = a + b;
    if (ans < a || ans < b) ans -= mod;
    return ans;
}

unsigned_bigint<4> sub_mod(const unsigned_bigint<4> &a,
                           const unsigned_bigint<4> &b,
                           const unsigned_bigint<4> &mod) {
    return a >= b ? a - b : mod - (b - a);
}
}  // namespace

curve::curve(const unsigned_bigint<4> &_a, const unsigned_bigint<4> &_b,
             const unsigned_bigint<4> &_p, const unsigned_bigint<4> &_Gx,
             const unsigned_bigint<4> &_Gy)
    : a(_a),
      b(_b),
      p(_p),
      G(point(_Gx, _Gy, this)),
      modInv(((unsigned_bigint<4>(1) << 64) -
              inverse(unsigned_bigint<4>(1) << 64, _p))
                 .data[0]) {}

bool curve::operator==(curve b) const {
    return this->a == b.a && this->b == b.b && this->p == b.p &&
           this->G.x == b.G.x && this->G.y == b.G.y;
}
point::point(point_jacobi &p) {
    unsigned_bigint<4> zp2, zp3, zp2Inv, zp3Inv;
    zp2 = multiply_mod_Montgomery(p.Z, p.Z, p.c->p, p.c->modInv);
    zp2 = multiply_mod_Montgomery(zp2, unsigned_bigint<4>(1), p.c->p,
                                  p.c->modInv);
    zp3 = multiply_mod_Montgomery(zp2, p.Z, p.c->p, p.c->modInv);
    zp2Inv = inverse(p.c->p, zp2);
    zp3Inv = inverse(p.c->p, zp3);
    this->x = multiply_mod_Montgomery(p.X, zp2Inv, p.c->p, p.c->modInv);
    this->y = multiply_mod_Montgomery(p.Y, zp3Inv, p.c->p, p.c->modInv);
    this->c = p.c;
}

point_jacobi point::operator+(point b) const {
    assert(this->c == b.c);
    return point_jacobi(*this) + point_jacobi(b);
}

point_jacobi point::operator*(unsigned_bigint<4> x) const {
    return point_jacobi(*this) * x;
}

point &point::operator=(point_jacobi b) {
    *this = point(b);
    return *this;
}

point_jacobi::point_jacobi(const point p) {
    this->X = p.x.toMontgomery(p.c->p);
    this->Y = p.y.toMontgomery(p.c->p);
    this->Z = unsigned_bigint<4>(1).toMontgomery(p.c->p);
    this->c = p.c;
}

point_jacobi::point_jacobi() {}

point_jacobi point_jacobi::double_point() const {
    if (this->Y == 0) {
        return point(0, 0, this->c);
    }
    unsigned_bigint<4> s, yp2, m, m2;
    point_jacobi p;
    p.c = this->c;
    unsigned_bigint<4> &x2 = p.X, &y2 = p.Y, &z2 = p.Z;
    yp2 = multiply_mod_Montgomery(Y, Y, c->p, c->modInv);
    s = multiply_mod_Montgomery(yp2, X, c->p, c->modInv);
    s = add_mod(s, s, c->p);
    s = add_mod(s, s, c->p);

    m2 = multiply_mod_Montgomery(X, X, c->p, c->modInv);
    m = add_mod(m2, m2, c->p);
    m = add_mod(m, m2, c->p);
    if (c->a != 0) {
        m2 = multiply_mod_Montgomery(Z, Z, c->p, c->modInv);
        m2 = multiply_mod_Montgomery(m2, m2, c->p, c->modInv);
        m2 = multiply_mod_Montgomery(m2, c->a, c->p, c->modInv);
        m = add_mod(m, m2, c->p);
    }
    x2 = sub_mod(multiply_mod_Montgomery(m, m, c->p, c->modInv),
                 add_mod(s, s, c->p), c->p);
    y2 = multiply_mod_Montgomery(m, sub_mod(s, x2, c->p), c->p, c->modInv);
    yp2 = multiply_mod_Montgomery(yp2, yp2, c->p, c->modInv);
    yp2 = add_mod(yp2, yp2, c->p);
    yp2 = add_mod(yp2, yp2, c->p);
    yp2 = add_mod(yp2, yp2, c->p);
    y2 = sub_mod(y2, yp2, c->p);
    z2 = multiply_mod_Montgomery(Y, Z, c->p, c->modInv);
    z2 = add_mod(z2, z2, c->p);
    return p;
}

point_jacobi point_jacobi::operator+(const point_jacobi b) const {
    assert((this->c == b.c));
    const EC::curve &c = this->getCurve();
    point_jacobi ans;
    ans.c = this->c;
    if (this->X == b.X && this->Y == b.Y && this->Z == b.Z) {
        return this->double_point();
    }

    const unsigned_bigint<4> &x1 = this->X, &y1 = this->Y, &z1 = this->Z,
                             &x2 = b.X, &y2 = b.Y, &z2 = b.Z;
    unsigned_bigint<4> &x3 = ans.X, &y3 = ans.Y, &z3 = ans.Z;
    if (x1 == 0 && y1 == 0) {
        return b;
    } else if (x2 == 0 && y2 == 0) {
        return *this;
    }

    unsigned_bigint<4> u1, u2, s1, s2, h, r;
    unsigned_bigint<4> z1p2, z2p2, z1p3, z2p3, hp2, hp3, tmp;
    z1p2 = multiply_mod_Montgomery(z1, z1, c.p, c.modInv);
    z2p2 = multiply_mod_Montgomery(z2, z2, c.p, c.modInv);
    z1p3 = multiply_mod_Montgomery(z1, z1p2, c.p, c.modInv);
    z2p3 = multiply_mod_Montgomery(z2, z2p2, c.p, c.modInv);
    u1 = multiply_mod_Montgomery(x1, z2p2, c.p, c.modInv);
    u2 = multiply_mod_Montgomery(x2, z1p2, c.p, c.modInv);
    s1 = multiply_mod_Montgomery(y1, z2p3, c.p, c.modInv);
    s2 = multiply_mod_Montgomery(y2, z1p3, c.p, c.modInv);
    if (u1 == u2) {
        if (s1 != s2) {
            return point(0, 0, this->c);
        } else {
            return this->double_point();
        }
    }
    h = sub_mod(u2, u1,c.p);
    r = sub_mod(s2, s1,c.p);
    hp2 = multiply_mod_Montgomery(h, h, c.p, c.modInv);
    hp3 = multiply_mod_Montgomery(h, hp2, c.p, c.modInv);
    x3 = sub_mod(multiply_mod_Montgomery(r, r, c.p, c.modInv), hp3, c.p);
    tmp = multiply_mod_Montgomery(u1, hp2, c.p, c.modInv);
    x3 = sub_mod(x3, tmp, c.p);
    x3 = sub_mod(x3, tmp, c.p);

    y3 = multiply_mod_Montgomery(r, sub_mod(tmp, x3, c.p), c.p, c.modInv);
    y3 = sub_mod(y3, multiply_mod_Montgomery(s1, hp3, c.p, c.modInv), c.p);

    z3 = multiply_mod_Montgomery(
        h, multiply_mod_Montgomery(z1, z2, c.p, c.modInv), c.p, c.modInv);

    return ans;
}

point_jacobi point_jacobi::operator*(unsigned_bigint<4> x) const {
    point_jacobi ans(point(0, 0, this->c)), a = *this;
    const int k = 5;  // 滑动窗口法的参数
    std::vector<point_jacobi> an;
    an.resize(1i64 << k);
    point_jacobi a2 = a + a;
    an[1] = a;
    for (int i = 3; i < (1 << k); i += 2) {
        an[i] = an[i - 2] + a2;
    }
    for (int i = 255; i >= 0; i--) {
        if (x.bit(i) == 0) {
            ans = ans.double_point();
        } else {
            int s = std::max(i - k + 1, 0);
            while (x.bit(s) == 0) s++;
            int u = 0;
            for (int j = 0; j <= i - s; j++) {
                ans = ans.double_point();
                u |= x.bit(s + j) << j;
            }
            ans = ans + an[u];
            i = s;
        }
    }
    return ans;
}

point_jacobi operator*(unsigned_bigint<4> k, point a) { return a * k; }
}  // namespace EC
