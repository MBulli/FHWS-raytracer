#include "StdAfx.h"
#include "Color.h"

/*----------------------------------------------------------------------------*/
/* addcolor   addiert zwei Farben zusammen                                    */
/*----------------------------------------------------------------------------*/
Color Color::addcolor(const Color &c) const
{
	return Color(r+c.r, g+c.g, b+c.b);
} /* addcolor() */


/*----------------------------------------------------------------------------*/
/* outprodc   'filtert' eine Farbe                                            */
/*----------------------------------------------------------------------------*/

Color Color::outprodc(const Color &c) const
{
	return Color(r*c.r, g*c.g, b*c.b);
} /* outprodc() */


/*----------------------------------------------------------------------------*/
/* scmpy   skaliert (dimmt) eine Farbe                                        */
/*----------------------------------------------------------------------------*/

Color Color::scmpy(double s) const
{
	return Color(r*s, g*s, b*s);
} /* scmpy */


void AccumulatedColor::addcolor(const Color& c)
{
	count++;
	r += c.r;
	g += c.g;
	b += c.b;
}

Color AccumulatedColor::getColor() const
{
	return Color(r/count, g/count, b/count);
}