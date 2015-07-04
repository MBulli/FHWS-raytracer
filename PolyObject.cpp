#include "stdafx.h"

#include "Ray.h"
#include "PolyObject.h"

#include <map>



PolyObject::~PolyObject()
{
}

Vector PolyObject::get_normal(Vector& v) const
{
	return Vector();
}

double PolyObject::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	for (const TrianglePtr& tri : triangles)
	{
		double t = tri->intersect(ray, outChild);

		if (t != -1)
		{
			*outChild = tri;
			return t;
		}
	}

	// no intersection
	return -1;
}

void PolyObject::setProperty(PropertyPtr property)
{
	Objekt::setProperty(property);

	for (TrianglePtr& tri : triangles)
	{
		tri->setProperty(property);
	}
}

Triangle::~Triangle()
{
}

const Vector& Triangle::vertex(int i)
{
	switch (i)
	{
	case 0: return p0;
	case 1: return p1;
	case 2: return p2;
	default: throw std::string("Out of bound.");
	}
}

Vector Triangle::get_normal(Vector& v) const
{
	return e1.cross(e2).normalize();
}

double Triangle::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	static const double epsilon = 1e-7f;
	static const double epsilon2 = 1e-10;

	const Vector& q = ray.getDirection().cross(e2);

	const double a = e1.dot(q);

	// The ray is nearly parallel to the plane
	if (a <= epsilon) {
		return -1.0;
	}

	const Vector& s = ray.getOrigin().vsub(p0);
	const Vector& r = s.cross(e1);
	const double dist = e2.dot(r) / a;

	// The ray origin is behind the plane
	if (dist <= 0.0) {
		return -1.0;
	}

	// Bayrycentric vertex weights
	const double weight0 = s.dot(q) / a;
	const double weight1 = ray.getDirection().dot(r) / a;
	const double weight2 = 1.0f - (weight0 + weight1);

	// The ray is nearly parallel to the riangle, or the
	// intersection lies outside the triangle or behind
	// the ray origin
	if ((weight0 < -epsilon2)
		|| (weight1 < -epsilon2)
		|| (weight2 < -epsilon2))
	{
		return -1.0;
	}

	return dist;
}
