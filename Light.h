#pragma once
#include "Vector.h"
#include "Color.h"

enum LightType {
	Directional,
	Point,
	Area,
	Spot
};

class Light
{
	LightType type;
	Color	 color;
public:
	Light(void) : color() {};
	Light(LightType type, const Color &c) : type(type), color(c) {};

	virtual ~Light() {};

	LightType getType()     const { return type; }
	const Color& getColor() const { return color; }

	virtual const Vector& getDirection(const Vector& point) const = 0;
};

class DirectionalLight : public Light
{
	Vector	 direction;
public:
	DirectionalLight(void) : Light(), direction() {};
	DirectionalLight(const Color& color, const Vector& direction) : Light(Directional, color), direction(direction) {};

	const Vector& getDirection(const Vector& point) const override { return direction; };
};

class PointLight : public Light
{
	Vector position;
public:
	PointLight(void) : Light(), position() {};
	PointLight(const Color& color, const Vector& position) : Light(Point, color), position(position) {};

	const Vector& getDirection(const Vector& point) const override { return position.vsub(point); };
};

typedef std::shared_ptr<Light> LightPtr;
typedef std::shared_ptr<const Light> LightConstPtr;
