#pragma once
#include "Color.h"
#include "string"
#include <memory>

class Property
{
	Color reflectance;
	Color ambient;
	double specular, mirror;
	std::string name;
public:
	Property(void) : reflectance(), specular(0.0), mirror(0.0) {};
	Property(char *n, Color &a, Color &r, double s, double m) 
		: reflectance(r), ambient(a), specular(s), mirror(m), name(n) {};

	Color getAmbient()     const { return ambient; };
	Color getReflectance() const { return reflectance; };
	double getSpecular()   const { return specular; };
	double getMirror()     const { return mirror; };
	std::string getName()  const { return name; };
};

typedef std::shared_ptr<Property> PropertyPtr;