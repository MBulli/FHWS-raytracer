#include "stdafx.h"

#include "Ray.h"
#include "PolyObject.h"

#include <map>
#include <cmath>

PolyObject::~PolyObject()
{
}

Vector PolyObject::get_normal(Vector& v) const
{
	return Vector();
}

double PolyObject::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	double min_t = DBL_MAX;
	for (const TrianglePtr& tri : triangles)
	{
		double t = tri->intersect(ray, outChild);

		if (t > 0.0 && t < min_t)
		{
			*outChild = tri;
			min_t = t;
		}
	}

	// no intersection
	return min_t == DBL_MAX ? -1 : min_t;
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

Vector Triangle::barycentric(const Vector& point) const
{
	Vector v0 = p1.vsub(p0);
	Vector v1 = p2.vsub(p0);
	Vector v2 = point.vsub(p0);
	double d00 = v0.dot(v0);
	double d01 = v0.dot(v1);
	double d11 = v1.dot(v1);
	double d20 = v2.dot(v0);
	double d21 = v2.dot(v1);
	double denom = d00 * d11 - d01 * d01;
	double v = (d11 * d20 - d01 * d21) / denom;
	double w = (d00 * d21 - d01 * d20) / denom;
	double u = 1.0f - v - w;

	return Vector(u, v, w);
}

Color Triangle::get_color(const Ray& ray, const Vector& intersection, const Color& globalAmbient) const
{
	Color matColor = Objekt::get_color(ray, intersection, globalAmbient);
	if (property->getTexture())
	{
		Vector bary = barycentric(intersection);

		double u = bary.x * tex0.x + bary.y * tex1.x + bary.z * tex2.x;
		double v = bary.x * tex0.y + bary.y * tex1.y + bary.z * tex2.y;

		// fix float rounding errors
		u = fmin(fmax(0, u), 1);
		v = fmin(fmax(0, v), 1);

		Color tex = property->getTexture()->getTexel(u, v);
		return tex;

		//return Color(bary.x, bary.y, bary.z);
		//matColor = tex.outprodc(matColor);
	}

	return matColor;
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

