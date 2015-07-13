#include "StdAfx.h"
#include "Ray.h"
#include "math.h"
#include "float.h"

#include "Objekt.h"
#include <functional>
#include <random>

using namespace std;

/*----------------------------------------------------------------------------*/
/* shade   arbeitet den folgenden Algorithmus ab:                             */
/*   Schneide den Sichtstrahl mit jedem Objekt. Merke, welches Objekt den     */
/*   kleinsten Parameterwert fuer den Schnittpunkt liefert. Wurde kein Objekt */
/*   geschnitten, dann setze den Farbwert auf Hintergrund. Von dem kleinsten  */
/*   Schnittpunkt aus, bestimme Strahl zu jeder Lichtquelle. Trifft dieser    */
/*   Strahl ein Objekt, dann traegt diese Lichtquelle nicht zur Beleuchtung   */
/*   bei. Bestimme den Farbwert nach der Lichtgleichung.                      */
/*   Dann berechne den Reflektionsstrahl und fuehre Beleuchtungsberechnung    */
/*   auch fuer diesen Strahl durch und addiere dessen Farbwerte zu den        */
/*   bereits bestimmten Farbwerten.                                           */
/* Rueckgabeparameter: Farbe, die auf diesem Strahl zu sehen ist              */
/*----------------------------------------------------------------------------*/
Color Ray::shade(const vector<ObjektConstPtr> &objects, const vector<LightConstPtr> &lights, const Color& background, const Color& globalAmbient)
{
	ObjektConstPtr closest = nullptr;
	Color cur_color; 
	double min_t = DBL_MAX, t;

	Vector intersection_position, normal;
	Ray lv, reflected_ray, refracted_ray, translucent_ray;
	bool something_intersected = false;

	for (const ObjektConstPtr& obj : objects)
	{
		ObjektConstPtr child = nullptr;
		t = obj->intersect(*this, &child);

		if (!isnan(t) && t < min_t) {
			min_t = t;

			if (child) {
				closest = child;
			} else {
				closest = obj;
			}
		}
	}

	if (closest == NULL) {
		if (depth == 0)
			cur_color = background; //background_color;
		else
			cur_color = Color(0,0,0);
	} else {
		intersection_position = intersectionPoint(min_t);
		normal = closest->get_normal(intersection_position);
		cur_color = closest->get_color(*this, intersection_position, globalAmbient); // Ambient color

		reflected_ray = reflect(intersection_position, normal);
		refracted_ray = refraction(intersection_position, normal, closest);
		translucent_ray = transculent(intersection_position);

		for (const LightConstPtr& li : lights) {

			const Vector randomLightPoint = li->randomPoint();

			double lightDist = li->getDistance(intersection_position, randomLightPoint);
			lv.setDirection(li->getDirection(intersection_position, randomLightPoint));
			lv.setOrigin(intersection_position);

			something_intersected = false;
			for (const ObjektConstPtr& obj : objects)
			{
				ObjektConstPtr child = nullptr;
				t = obj->intersect(lv, &child);
				if (t > 0.0 && t < lightDist) {
					// Shadow
					something_intersected = true;
					break;
				}
			}

			// Light color
			if (something_intersected == false) {
				Color new_color = shaded_color(li, randomLightPoint, reflected_ray, normal, closest);
				cur_color = cur_color.addcolor(new_color);
			} 
		}

		// only calculate reflaction/refraction if the recursive limit is not hit
		// otherwise we would possibly spawn infinite rays
		if (depth < 5) 
		{
			// Reflection
			const double mirror = closest->getProperty().getMirror();
			if (mirror != 0.0)
			{
				Color mirrorColor;
				const double glossy = closest->getProperty().getGlossy();
				if (glossy != 0.0) {
					// reduce the number of samples linear to the reflection recursive depth
					const int glossySamples = int(closest->getProperty().getGlossySamples() / float(depth+1));
					mirrorColor = glossyReflectionShade(reflected_ray, normal, closest, glossy, glossySamples, objects, lights, background, globalAmbient);
				}
				else {
					mirrorColor = reflected_ray.shade(objects, lights, background, globalAmbient);
				}

				cur_color = cur_color.addcolor(mirrorColor.scmpy(mirror));
			}
			
			// Refraction
			if (this->currentRefractionIndex != refracted_ray.currentRefractionIndex)
			{
				// if total internal reflection
				if (!isnan(refracted_ray.getDirection().x))
				{
					Color refrac_color = refracted_ray.shade(objects, lights, background, globalAmbient);
					refrac_color = refrac_color.scmpy(closest->getProperty().getRefraction());
					cur_color = cur_color.addcolor(refrac_color);
				}
			}
		}

		// Opacity
		const double opacity = closest->getProperty().getOpacity();
		if (opacity != 0.0)
		{
			const double alpha = 1.0 - opacity;

			const Color trans_color = translucent_ray.shade(objects, lights, background, globalAmbient);
			cur_color = cur_color.scmpy(alpha).addcolor(trans_color.scmpy(1.0 - alpha));
		}
	}
	return(cur_color);
} /* shade() */


/*----------------------------------------------------------------------------*/
/* shaded_color   berechnet die Farbe im Treffpunkt, die durch die           */
/*   Lichtquelle hervorgerufen wird.                                          */
/* Aufrufparameter:    Lichtquelle                                            */
/*                     Reflexionsstrahl                                       */
/*                     Normalenvektor im Treffpunkt                           */
/*                     aktuelles Objekt                                       */
/* Rueckgabeparameter: errechnete Farbe                                       */
/*----------------------------------------------------------------------------*/

Color Ray::shaded_color(const LightConstPtr& light, const Vector& lightPoint, const Ray& reflectedray, const Vector& normal, ObjektConstPtr& obj)
{
	Color reflected_color = Color();

	const Vector lightDir = light->getDirection(reflectedray.getOrigin(), lightPoint);
	const double lightIntensity = light->getItensity(reflectedray.getOrigin(), lightPoint);

	// Diffuse light
	double ldot = lightDir.dot(normal);
	if (1.0 + ldot > 1.0) {
		Color lambert = light->getColor().scmpy(ldot);
		reflected_color = lambert.outprodc(obj->getProperty().getReflectance());
	}

	// Specular light
	double spec = reflectedray.getDirection().dot(lightDir);
	if (1.0 + spec > 1.0) {
		spec = pow(spec, obj->getProperty().getShininess());
		spec *= obj->getProperty().getSpecular();
		Color specular =  light->getColor().scmpy(spec);
		reflected_color = reflected_color.addcolor(specular);
	}
	
	return reflected_color.scmpy(lightIntensity);
} /* shaded_color() */

/*----------------------------------------------------------------------------*/
/* reflect   berechnet einen Reflektionsstrahl aus dem einfallenden Strahl an */
/*    dem Reflektionspunkt mit Hilfe des Normalenvektors an dieser Stelle.    */
/* Aufrufparameter:    einfallender Strahl                                    */
/*                     Reflektionspunkt                                       */
/*                     Normalenvektor                                         */
/* Rueckgabeparameter: Reflektionsstrahl                                      */
/*----------------------------------------------------------------------------*/

Ray Ray::reflect(Vector &origin, Vector &normal)
{
	const double incdot = normal.dot(this->direction);
	const Vector dir = this->direction.vsub(normal.svmpy(2.0*incdot)).normalize();

	return Ray(dir, origin, this->depth + 1);
} /* reflect() */

Ray Ray::refraction(Vector& origin, Vector& normal, ObjektConstPtr object)
{
	const double n1 = currentRefractionIndex;
	const double n2 = object->getProperty().getRefractionIndex(); // brechungs index

	const double n = n1 / n2;
	const double cosI = normal.dot(this->getDirection());
	const double sinT2 = n * n * (1.0 - cosI * cosI);

	if (sinT2 > 1.0)
	{
		// total internal reflection
		// theres no transmission vector
		// see http://www.flipcode.com/archives/reflection_transmission.pdf
		return Ray(Vector(NAN, NAN, NAN), Vector(NAN, NAN, NAN), 1);
	}

	const Vector x = this->getDirection().svmpy(n);
	const Vector y = normal.svmpy(n + sqrt(1.0 - sinT2));
	const Vector t = x.vsub(y); // refraction direction

	return Ray(t.normalize(), origin, this->depth + 1, n2);
}

Ray Ray::transculent(Vector& origin)
{
	return Ray(this->direction, origin, this->depth + 1, this->currentRefractionIndex);
}

Color Ray::glossyReflectionShade(Ray& reflectedRay, const Vector& normal, const ObjektConstPtr& object, const double glossy, const int glossySamples, const std::vector<ObjektConstPtr>& objects, const std::vector<LightConstPtr>& lights, const Color& background, const Color& globalAmbient)
{
	static std::default_random_engine generator;
	static uniform_real_distribution<double> distribution(0, 1);
	static auto random = std::bind(distribution, generator);

	// glossy reflection
	const Vector reflZ = reflectedRay.getDirection();
	const Vector reflX = reflZ.cross(normal).normalize();
	const Vector reflY = reflZ.cross(reflX).normalize();

	AccumulatedColor accMirrColor;
	for (int i = 0; i < glossySamples; i++)
	{
		const double angle = random() * 2 * M_PI;
		const double radius = random() * glossy;
		const Vector r = reflZ
			.vadd(reflX.svmpy(radius*cos(angle)))
			.vadd(reflY.svmpy(radius*sin(angle)));

		// if reflected ray intersects with object, skip it
		if (normal.dot(r) < 0)
			continue;

		reflectedRay.setDirection(r.normalize());
		const Color clr = reflectedRay.shade(objects, lights, background, globalAmbient);

		accMirrColor.addcolor(clr);
	}

	return accMirrColor.getColor();
}

