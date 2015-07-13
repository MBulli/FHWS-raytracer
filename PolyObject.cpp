#include "stdafx.h"

#include "Ray.h"
#include "PolyObject.h"

#include <map>
#include <cmath>

void PolyObject::calcBoundingSphere()
{
	Vector min(DBL_MAX, DBL_MAX, DBL_MAX), max(-DBL_MAX, -DBL_MAX, -DBL_MAX);

	for (auto& triangle : triangles)
	{
		for (const auto& v : triangle->getPoints())
		{
			if (v->x < min.x) min.x = v->x;
			if (v->x > max.x) max.x = v->x;
			if (v->y < min.y) min.y = v->y;
			if (v->y > max.y) max.y = v->y;
			if (v->z < min.z) min.z = v->z;
			if (v->z > max.z) max.z = v->z;
		}
	}

	boundingSphereCenter = min.vadd(max).svmpy(0.5);

	for (const auto& triangle : triangles)
	{
		for (const auto& v : triangle->getPoints())
		{
			float d = v->vsub(boundingSphereCenter).veclength();
			if (d > boundingSphereRadius) 
				boundingSphereRadius = d;
		}
	}
}

bool PolyObject::intersectsWithBoundingSphere(const Ray& ray) const
{
	return boundingSphereCenter.vsub(ray.getOrigin()).cross(ray.getDirection()).veclength() <= boundingSphereRadius;
}

PolyObject::~PolyObject()
{
}

Vector PolyObject::get_normal(Vector& v) const
{
	return Vector();
}

double PolyObject::intersect(const Ray& ray, ObjektConstPtr* outChild) const
{
	if (!intersectsWithBoundingSphere(ray)) {
		return NAN;
	}

	double min_t = DBL_MAX;
	for (const TrianglePtr& tri : triangles)
	{
		double t = tri->intersect(ray, outChild);

		if (!isnan(t) && t < min_t)
		{
			*outChild = tri;
			min_t = t;
		}
	}

	// no intersection
	return min_t == DBL_MAX ? NAN : min_t;
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

void Triangle::setTextureCoords(Vector t0, Vector t1, Vector t2)
{
	this->tex0 = t0;
	this->tex1 = t1;
	this->tex2 = t2;
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

Color Triangle::get_texture_color(const Vector& intersection) const
{
	Color matColor = Objekt::get_texture_color(intersection);
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
		return NAN;
	}

	const Vector& s = ray.getOrigin().vsub(p0);
	const Vector& r = s.cross(e1);
	const double dist = e2.dot(r) / a;

	// The ray origin is behind the plane
	if (dist <= 0.0) {
		return NAN;
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
		return NAN;
	}

	return dist > 0.001 ? dist : NAN;
}

