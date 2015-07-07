#pragma once
#include "Vector.h"
#include "Color.h"

class Light
{
	Vector	 direction;
	Color	 color;
public:
	Light(void): direction(), color() {};
	Light(const Vector &v, const Color &c): direction(v), color(c) {};

	const Vector& getDirection() const { return direction; };
	const Color& getColor() const { return color; };
};

typedef std::shared_ptr<Light> LightPtr;
typedef std::shared_ptr<const Light> LightConstPtr;
