#include "StdAfx.h"
#include "Light.h"
#include <functional>
#include <random>

Vector Light::getDirection(const Vector& point, const Vector& lightPoint) const
{
	return lightPoint.vsub(point).normalize();
}

double Light::getDistance(const Vector& point, const Vector& lightPoint) const
{
	return lightPoint.vsub(point).veclength();
}


CircleAreaLight::CircleAreaLight(const Color& color, const Vector& position, const Vector& normal, double radius)
	: Light(AreaCircle, color), position(position), normal(normal.normalize()), radius(radius)
{
	// find vector (1,1,z) orthogonal to normal with dot product
	u = Vector(1, 1, (-normal.x - normal.y) / normal.z).normalize();
	v = normal.cross(u).normalize();
}

Vector CircleAreaLight::randomPoint() const
{
	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0, 1);
	static auto random = std::bind(distribution, generator);

	const double a = random();
	const double b = random();

	const double x = b*radius*cos(2 * M_PI*a);
	const double y = b*radius*sin(2 * M_PI*a);

	const Vector randPoint = position.vadd(u.svmpy(x)).vadd(v.svmpy(y));

	return randPoint;
}


