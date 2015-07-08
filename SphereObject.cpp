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

Color SphereObject::get_color(const Ray& ray, const Vector& intersection, const Color& globalAmbient) const
{
	Color matColor = Objekt::get_color(ray, intersection, globalAmbient);
	if (property->getTexture())
	{
		const double len = intersection.veclength();

		//double u = intersection.x / len;
		//double v = intersection.y / len;

		double u = (atan2(intersection.z, intersection.x) / M_PI + 1.0f) * 0.5f;
		double v = acos(intersection.y / len) / M_PI;

		Color tex = property->getTexture()->getTexel(u, v);

		matColor = matColor.outprodc(tex);
	}
	return matColor;
}

double SphereObject::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	Vector dir = ray.getDirection();
	Vector org = ray.getOrigin();

	double a = dir.veclength()*dir.veclength();
	double b = 2*org.vsub(center).dot(dir);
	double c = org.vsub(center).veclength()*org.vsub(center).veclength() - radius*radius;

	double D = b*b - 4*a*c;

	if (D < 0) {
		return NAN;
	}

	double t1 = (-b + sqrt(D)) / 2*a;
	double t2 = (-b - sqrt(D)) / 2*a;

	double t = std::min(t1, t2);
	return t > 0.001 ? t : NAN;
}