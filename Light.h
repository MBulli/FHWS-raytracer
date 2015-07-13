#pragma once
#include "Vector.h"
#include "Color.h"

enum LightType {
	Directional,
	Point,
	AreaCircle,
	AreaRectangle,
	Spot
};

class Light
{
protected:
	LightType type;
	Color	 color;
public:
	Light(void) : color() {};
	Light(LightType type, const Color &c = Color()) : type(type), color(c) {};

	virtual ~Light() {};

	LightType getType()     const { return type; }
	const Color& getColor() const { return color; }

	// Select a point uniformly at random on the surface of the light
	virtual Vector randomPoint() const = 0;

	// gets the direction from a given point to the light
	virtual Vector getDirection(const Vector& point, const Vector& lightPoint) const;
	// gets the distance from a given point to the light
	virtual double getDistance(const Vector& point, const Vector& lightPoint) const;
	// gets the itensity of the light source at a given point
	virtual double getItensity(const Vector& point, const Vector& lightPoint) const { return 1.0; };
};

class DirectionalLight : public Light
{
	Vector	 direction;
public:
	DirectionalLight(void) : Light(Directional), direction() {};
	DirectionalLight(const Color& color, const Vector& direction) : Light(Directional, color), direction(direction.normalize()) {};

	Vector randomPoint() const override { return Vector(); };

	Vector getDirection(const Vector& point, const Vector& lightPoint) const override { return direction; };
	double getDistance(const Vector& point, const Vector& lightPoint) const override { return std::numeric_limits<double>::infinity(); };
};

class PointLight : public Light
{
	Vector position;
public:
	PointLight(void) : Light(Point), position() {};
	PointLight(const Color& color, const Vector& position) : Light(Point, color), position(position) {};

	Vector randomPoint() const override { return position; };
};

class CircleAreaLight : public Light
{
	Vector position;
	Vector normal;
	double radius;

	// coord system of the light using: normal, u and v
	Vector u, v;
public:
	CircleAreaLight(void) : Light(AreaCircle) {};
	CircleAreaLight(const Color& color, const Vector& position, const Vector& normal, double radius);

	Vector randomPoint() const override;
};

typedef std::shared_ptr<Light> LightPtr;
typedef std::shared_ptr<const Light> LightConstPtr;
