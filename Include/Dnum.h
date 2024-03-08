#ifndef DNUM_H
#define DNUM_H
#include <cmath> 

struct Dnum {
	float value, derivative;
	Dnum(float f0 = 0, float d0 = 0) { value = f0, derivative = d0; }

	Dnum operator-() { return Dnum(-value, -derivative); }
	
	float& f() { return value; }
	float& d() { return derivative; }
};

inline Dnum operator+(Dnum l, Dnum r) { return Dnum(l.f() + r.f(), l.d() + r.d()); }
inline Dnum operator-(Dnum l, Dnum r) { return Dnum(l.f() - r.f(), l.d() - r.d()); }
inline Dnum operator*(Dnum l, Dnum r) { return Dnum(l.f() * r.f(), l.f() * r.d() + l.d() * r.f()); }
inline Dnum operator/(Dnum l, Dnum r) { return Dnum(l.f() / r.f(), (l.d() * r.f() - l.f() * r.d()) / r.f() / r.f()); }

// Elementary functions prepared for the chain rule as well
inline Dnum Sin(Dnum g) { return Dnum(sin(g.f()), cos(g.f()) * g.d()); }
inline Dnum Cos(Dnum g) { return Dnum(cos(g.f()), -sin(g.f()) * g.d()); }
inline Dnum Tan(Dnum g) { return Sin(g) / Cos(g); }
inline Dnum Log(Dnum g) { return Dnum(logf(g.f()), 1 / g.f() * g.d()); }
inline Dnum Exp(Dnum g) { return Dnum(expf(g.f()), expf(g.f()) * g.d()); }
inline Dnum Pow(Dnum g, float n) { return Dnum(powf(g.f(), n), n * powf(g.f(), n - 1) * g.d()); }


#endif // DNUM_H
