#pragma once

#include "Objekt.h"

class SphereObject : public Objekt
{
private:
	Vector center;
	double radius;

public:
	SphereObject(void) : Objekt(""), center(), radius(0.0) {};
	SphereObject(char* name, Vector center, double radius) : Objekt(name), center(center), radius(radius) {};

	~SphereObject();

	Vector getCenter() const { return center; }
	double getRadius() const { return radius; }

	Vector get_normal(Vector& v) const override;

	Color get_texture_color(const Vector& intersection) const override;
	double intersect(const Ray& ray, ObjektConstPtr* outChild) const override;
};

typedef std::shared_ptr<SphereObject> SphereObjectPtr;