#pragma once
#include "Property.h"
#include "Objekt.h"
#include "Light.h"

#include <vector>

class Parser
{
private:
	std::string filename;

public:
	Parser(char* filename) : filename(filename) {}
	~Parser();

	bool start();

	const std::vector<PropertyPtr>& getProperties() const;
	const std::vector<ObjektPtr>& getObjects()      const;
	const std::vector<LightPtr>& getLights()	    const;

	int getResoultionX() const;
	int getResoultionY() const;

	const Color& getBackgroundColor() const;
	const Color& getGlobalAmbient()   const;

	const Vector& getEyePoint()		const;
	const Vector& getLookatPoint()  const;
	const Vector& getUp()           const;
	double        getFieldOfViewX() const; // in rad; NaN if not set
	double        getFieldOfViewY() const; // in rad; NaN if not set
	double		  getAspectRatio()  const;

	double        getDOFSamples()	const;
	double		  getApatureRadius()   const;
	double        getFocalDistance()   const;
};

