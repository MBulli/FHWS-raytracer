#include "stdafx.h"

#include "QuadricObject.h"
#include "Ray.h"

QuadricObject::~QuadricObject()
{
}

Vector QuadricObject::get_normal(Vector& v) const
{
	Vector normal(
		v.dot(Vector(a + a, b, c)) + d,
		v.dot(Vector(b, e + e, f)) + g,
		v.dot(Vector(c, f, h + h)) + j);

	return normal.normalize();
}

double QuadricObject::intersect(const Ray& ray) const
{
	double t = -1.0;
	double acoef, bcoef, ccoef, root, disc;

	Vector direction = ray.getDirection();
	Vector origin = ray.getOrigin();

	acoef = Vector(direction.dot(Vector(a, b, c)),
		e*direction.y + f*direction.z,
		h*direction.z).dot(direction);

	bcoef =
		Vector(d, g, j).dot(direction) +
		origin.dot(Vector(
		direction.dot(Vector(a + a, b, c)),
		direction.dot(Vector(b, e + e, f)),
		direction.dot(Vector(c, f, h + h))));

	ccoef = origin.dot(
		Vector(Vector(a, b, c).dot(origin) + d,
		e*origin.y + f*origin.z + g,
		h*origin.z + j)) + k;

	if (1.0 + acoef != 1.0) {
		disc = bcoef * bcoef - 4 * acoef * ccoef;
		if (disc > -DBL_EPSILON) {
			root = sqrt(disc);
			t = (-bcoef - root) / (acoef + acoef);
			if (t < 0.0) {
				t = (-bcoef + root) / (acoef + acoef);
			}
		}
	}
	t = ((0.001 < t) ? t : -1.0);
	return t;
}