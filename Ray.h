#pragma once
#include "Vector.h"
#include "Color.h"
#include "Light.h"
#include "vector"
#include "Objekt.h"

class Ray
{
	Vector direction, origin;
	int	 depth;
	double currentRefractionIndex;

	Color shaded_color(const LightConstPtr& light, Ray& reflectedray, Vector& normal, ObjektConstPtr obj);

public:
	Ray(void) : direction(), origin(), depth (0), currentRefractionIndex(1.0) {};
	Ray(const Vector &dir, const Vector &orig, int depth, double refractionIndex = 1.0)
		: direction(dir), origin(orig), depth (depth), currentRefractionIndex(refractionIndex) {};

	Color shade(const std::vector<ObjektConstPtr>& objects,
				const std::vector<LightConstPtr>& lights,
				const Color& background,
				const Color& globalAmbient);

	const Vector& getDirection() const { return direction; };
	const Vector& getOrigin() const { return origin; };
	int getDepth() const { return depth; };

	void setDirection(const Vector &v) { direction=v; };
	void setOrigin(const Vector &v) { origin=v; };
	void setDepth(int d) { depth=d; };

	Ray reflect(Vector &origin, Vector &normal);
	Ray refraction(Vector& origin, Vector& normal, ObjektConstPtr object);

	Color glossyReflectionShade(Ray& reflectedRay, 
								const Vector& normal,
								const ObjektConstPtr& object,
								const double glossy,
								const int glossySamples,
								const std::vector<ObjektConstPtr>& objects,
								const std::vector<LightConstPtr>& lights,
								const Color& background,
								const Color& globalAmbient);

	Vector intersectionPoint(double t) const { return origin.vadd(direction.svmpy(t)); }
};


