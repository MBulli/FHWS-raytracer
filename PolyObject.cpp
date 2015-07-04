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
	float weight[3];
	double t = intersect(ray, weight);
	return t;
}

double Triangle::intersect(const Ray& ray, float weight[3]) const
{
	const Vector& q = ray.getDirection().cross(e2);

	const float a = e1.dot(q);

	const Vector& s = ray.getOrigin().vsub(p0);
	const Vector& r = s.cross(e1);

	// Bayrycentric vertex weights
	weight[0] = s.dot(q) / a;
	weight[1] = ray.getDirection().dot(r) / a;
	weight[2] = 1.0f - (weight[0] + weight[1]);

	const float dist = e2.dot(r) / a;

	static const float epsilon = 1e-7f;
	static const float epsilon2 = 1e-10;

	// The ray is nearly parallel to the riangle, or the
	// intersection lies outside the triangle or behind
	// the ray origin
	if ((a <= epsilon)
		|| (weight[0] < -epsilon2)
		|| (weight[1] < -epsilon2)
		|| (weight[2] < -epsilon2)
		|| (dist <= 0.0f)) 
	{
		return -1.0;
	} 

	return dist;
}

