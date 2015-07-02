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

	Color shaded_color(Light *light, Ray &reflectedray, Vector &normal, ObjektPtr obj);

public:
	Ray(void) : direction(), origin(), depth (0) {};
	Ray(const Vector &dir, Vector &orig, int d) : direction(dir), origin(orig), depth (d) {};
	Color shade(std::vector<ObjektPtr>&, std::vector<Light> &, const Color& background, const Color& globalAmbient);

	Vector getDirection() const { return direction; };
	Vector getOrigin() const { return origin; };
	int getDepth() const { return depth; };

	void setDirection(const Vector &v) { direction=v; };
	void setOrigin(Vector &v) { origin=v; };
	void setDepth(int d) { depth=d; };

	Ray reflect(Vector &origin, Vector &normal);
};


