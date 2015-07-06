#pragma once
#include "Color.h"
#include "string"
#include <memory>

class Property
{
	Color reflectance;
	Color ambient;
	double specular, shininess, mirror;
	std::string name;
public:
	Property(void) : reflectance(), specular(0.0), shininess(0.0), mirror(0.0) {};
	Property(char *n, Color &a, Color &r, double s, double shininess, double m) 
		: reflectance(r), ambient(a), specular(s), shininess(shininess), mirror(m), name(n) {};

	Color getAmbient()     const { return ambient; };
	Color getReflectance() const { return reflectance; };
	double getSpecular()   const { return specular; };
	double getShininess()  const { return shininess; }
	double getMirror()     const { return mirror; };
	std::string getName()  const { return name; };
};

typedef std::shared_ptr<Property> PropertyPtr;