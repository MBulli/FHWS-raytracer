#pragma once

#include <memory>

#include "Texture.h"
#include "Property.h"
#include "Vector.h"

class Ray;
class Objekt;

typedef std::shared_ptr<Objekt> ObjektPtr;
typedef std::shared_ptr<const Objekt> ObjektConstPtr;

class Objekt
{
protected:
	PropertyPtr property;
	std::string name;
public:

	Objekt(const char* name)		 : property(nullptr), name(name) {};
	Objekt(const std::string& name)  : property(nullptr), name(name) {};
	Objekt(void)			         : property(nullptr), name("")   {};

	virtual ~Objekt() {};

	virtual void setProperty(PropertyPtr property) { this->property = property; }

	const Property& getProperty() const { return *property; }
	const std::string& getName()  const { return name; }

	/*----------------------------------------------------------------------------*/
	/* get_normal   gibt den Normalenvektor der Oberflaeche eines Objekts an dem  */
	/*   in 'v' bestimmten Punkt zurueck.                                         */
	/* Aufrufparameter:    Punkt-Vektor, fuer den der N.-Vektor berechnet werd. s.*/
	/*                     Datenstruktur in der der Objektpointer enthalten ist   */
	/* Rueckgabeparameter: Berechneter Normalenvektor                             */
	/*----------------------------------------------------------------------------*/
	virtual Vector get_normal(Vector &v) const = 0;
	virtual Color get_color(const Ray& ray, const Vector& intersection, const Color& globalAmbient) const;
	virtual double intersect(const Ray& ray, ObjektConstPtr* outChild) const = 0;
};


