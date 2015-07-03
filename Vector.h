#pragma once
#include <memory>

class Vector
{
public:
	double x,y,z;
public:
	Vector(void) : x(0.0), y(0.0), z(0.0) {};
	Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	Vector cross (const Vector &v) const;
	double dot(const Vector &v) const;
	Vector normalize(void) const;
	Vector svmpy(double s) const;
	Vector svdiv(double s) const;
	Vector vadd(const Vector &v) const; 
	double veclength (void) const;
	Vector vsub(const Vector &v) const;
};

typedef std::shared_ptr<Vector> VectorPtr;

