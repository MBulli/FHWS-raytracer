#pragma once
#include "Color.h"
#include "string"
#include <memory>
#include "Texture.h"

class Property
{
	Color reflectance;
	Color ambient;
	double specular, shininess, mirror, refraction, refractionIndex;
	std::string name;
	TexturePtr texture = nullptr;
public:
	Property(void) : reflectance(), specular(0.0), shininess(0.0), mirror(0.0), refraction(0.0), refractionIndex(1.0) {};
	Property(char *n, Color &a, Color &r, double s, double shininess, double m, double refraction, double refractionIndex)
		: reflectance(r), ambient(a), specular(s), shininess(shininess), mirror(m), refraction(refraction), refractionIndex(refractionIndex), name(n) {};

	void setTexture(TexturePtr tex) { texture = tex; }

	Color getAmbient()			 const { return ambient; };
	Color getReflectance()		 const { return reflectance; };
	double getSpecular()		 const { return specular; };
	double getShininess()		 const { return shininess; }
	double getMirror()			 const { return mirror; };
	double getRefraction()		 const { return refraction; };
	double getRefractionIndex()  const { return refractionIndex; }
	std::string getName()		 const { return name; };
	TextureConstPtr getTexture() const { return texture; }
};

typedef std::shared_ptr<Property> PropertyPtr;