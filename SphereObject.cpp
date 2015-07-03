#include "stdafx.h"
#include "SphereObject.h"

#include "Ray.h"
#include <algorithm>

SphereObject::~SphereObject()
{
}

Vector SphereObject::get_normal(Vector& v) const
{
	return v.vsub(center).normalize();
}

double SphereObject::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	Vector dir = ray.getDirection();
	Vector org = ray.getOrigin();

	double a = dir.veclength()*dir.veclength();
	double b = 2*org.vsub(center).dot(dir);
	double c = org.vsub(center).veclength()*org.vsub(center).veclength() - radius*radius;

	double D = b*b - 4*a*c;

	if (D < 0)
	{
		return -1;
	}

	double t1 = (-b + sqrt(D)) / 2*a;
	double t2 = (-b - sqrt(D)) / 2*a;

	double t = std::min(t1, t2);
	return t;
}