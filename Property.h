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
	double glossy; int glossySamples;
	double opacitiy;
	std::string name;
	TexturePtr texture = nullptr;
public:
	Property(void) 
		: reflectance(), specular(0.0), shininess(0.0), mirror(0.0), refraction(0.0), refractionIndex(1.0), glossy(0.0), glossySamples(0), opacitiy(0.0) {};
	Property(const char *n, Color &a, Color &r, double s, double shininess, double m, double refraction, double refractionIndex, double glossy, int glossySamples, double opacitiy)
		: reflectance(r), ambient(a), specular(s), shininess(shininess), mirror(m), refraction(refraction), refractionIndex(refractionIndex), glossy(glossy), glossySamples(glossySamples), opacitiy(opacitiy), name(n) {};

	void setTexture(TexturePtr tex) { texture = tex; }

	Color getAmbient()			 const { return ambient; };
	Color getReflectance()		 const { return reflectance; };
	double getSpecular()		 const { return specular; };
	double getShininess()		 const { return shininess; }
	double getMirror()			 const { return mirror; };
	double getRefraction()		 const { return refraction; };
	double getRefractionIndex()  const { return refractionIndex; }
	double getGlossy()			 const { return glossy; }
	int    getGlossySamples()    const { return glossySamples; }
	double getOpacity()			 const { return opacitiy; }
	std::string getName()		 const { return name; };
	TextureConstPtr getTexture() const { return texture; }
};

typedef std::shared_ptr<Property> PropertyPtr;