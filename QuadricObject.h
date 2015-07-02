#pragma once
#include "Objekt.h"
class QuadricObject : public Objekt
{
public:
	double a, b, c, d, e, f, g, h, j, k;

	QuadricObject(void) : Objekt(""), a(0.0), b(0.0), c(0.0), d(0.0), e(0.0), f(0.0), g(0.0), h(0.0), j(0.0), k(0.0) {};
	QuadricObject(char *n, double _a, double _b, double _c, double _d, double _e, double _f, double _g, double _h, double _j, double _k) :
		Objekt(n), a(_a), b(_b), c(_c), d(_d), e(_e), f(_f), g(_g), h(_h), j(_j), k(_k) {};
	~QuadricObject();

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray) const override;
};

typedef std::shared_ptr<QuadricObject> QuadricObjectPtr;