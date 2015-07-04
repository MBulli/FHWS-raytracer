#include "StdAfx.h"
#include "Vector.h"
#include "math.h"

/*----------------------------------------------------------------------------*/
/* cross   berechnet das Kreuzprodukt zweier Vektoren                         */
/*----------------------------------------------------------------------------*/
Vector Vector::cross(const Vector &v) const
{
	return Vector( (y * v.z - v.y * z), 
				  -(x * v.z - v.x * z),
				   (x * v.y - v.x * y));
} /* cross() */


/*----------------------------------------------------------------------------*/
/* dot   berechnet das innere Produkt (Skalarprodukt) zweier Vektoren         */
/*----------------------------------------------------------------------------*/

double Vector::dot(const Vector &v) const
{
	return(x * v.x + y * v.y + z * v.z);
} /* dot() */

/*----------------------------------------------------------------------------*/
/* normalize   normalisiert den uebergebenen Vektor                           */
/*----------------------------------------------------------------------------*/
Vector Vector::normalize() const
{
	return svmpy( 1/veclength() );
} /* normalize() */


/*----------------------------------------------------------------------------*/
/* svmpy   berechnet das Produkt zwischen einem Skalar und einem Vektor       */
/*----------------------------------------------------------------------------*/
Vector Vector::svmpy(double s) const
{
	return Vector(s*x, s*y, s*z);
} /* svmpy() */

/*----------------------------------------------------------------------------*/
/* svdiv   berechnet die  Division zwischen einem Skalar und einem Vektor     */
/*----------------------------------------------------------------------------*/
Vector Vector::svdiv(double s) const
{
	return Vector(x/s, y/s, z/s);
}

/*----------------------------------------------------------------------------*/
/* vadd   berechnet die Summe zweier Vektoren                                 */
/* Aufrufparameter:    die beiden aufzusummierenden Vektoren                  */
/* Rueckgabeparameter: Vektorsumme                                            */
/*----------------------------------------------------------------------------*/

Vector Vector::vadd(const Vector &v) const
{
	return Vector(x+v.x, y+v.y, z+v.z);
} /* vadd() */

/*----------------------------------------------------------------------------*/
/* veclength   berechnet die Laenge eines Vektors                             */
/* Aufrufparameter:    Vektor, dessen Laenge berechnet werden soll            */
/* Rueckgabeparameter: Laenge des Vektors                                     */
/*----------------------------------------------------------------------------*/
double Vector::veclength () const
{
	return (sqrt (x*x + y*y + z*z));
} /* veclength() */


/*----------------------------------------------------------------------------*/
/* vsub   berechnet die Differenz zweier Vektoren                             */
/*----------------------------------------------------------------------------*/
Vector Vector::vsub(const Vector &v) const
{
	return Vector(x-v.x, y-v.y, z-v.z);
} /* vsub() */

