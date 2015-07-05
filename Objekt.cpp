#include "StdAfx.h"
#include "Objekt.h"
#include "Ray.h"


Color Objekt::get_color(const Vector& intersection, const Color& globalAmbient) const
{
	return property->getAmbient().outprodc(globalAmbient);
}