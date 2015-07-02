// raytrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include "Ray.h"
#include "Color.h"
#include "Image.h"

#include "Objekt.h"
#include "QuadricObject.h"
#include "SphereObject.h"

#include <vector>
#include <iostream>

using namespace std;

vector<PropertyPtr> properties;
vector<ObjektPtr> rawObjects; // objects without property
vector<ObjektPtr> objekte;
vector<Light> lights;

int resolutionX = 1250;
int resolutionY = 1250;
Color backgroundColor;
Color globalAmbient;

Vector eyePoint;
Vector lookatPoint;
Vector up;
double fieldOfViewX; // in rad
double aspect;

extern "C" {
	extern FILE *yyin;
	int yyparse();

	// picture parameters
	void set_output_resolution(int x, int y) {
		fprintf(stderr, " set resolution X=%d, Y=%d\n", x, y);
		resolutionX = x;
		resolutionY = y;
	};
	void set_scene_background(double r, double g, double b) {
		fprintf(stderr, " set background (%f, %f, %f)\n", r, g, b);
		backgroundColor = Color(r, g, b);
	};

	// viewing parameters
	void set_eyepoint(double x, double y, double z) {
		eyePoint = Vector(x, y, z);
	}
	void set_lookat(double x, double y, double z) {
		lookatPoint = Vector(x, y, z);
	}
	void set_up(double x, double y, double z) {
		up = Vector(x, y, z);
	}
	void set_fovx(double fovxInDeg) {
		fieldOfViewX = fovxInDeg * M_PI / 180.0;
	}
	void set_aspect(double a) {
		aspect = a;
	}
	void set_global_ambience(double r, double g, double b) {
		globalAmbient = Color(r, g, b);
	}

	// light
	void add_light(char *n, double dirx, double diry, double dirz, double colr, double colg, double colb) {
		fprintf(stderr,"  adding light %f %f %f %f %f %f\n", dirx, diry, dirz, colr, colg, colb);
		lights.push_back(Light(Vector(dirx,diry,dirz).normalize(), Color(colr, colg, colb)));
	};

	// geometry
	void add_quadric(char *n, double a, double b, double c, double d, double e, double f, double g, double h, double j, double k) {
		fprintf(stderr,"  adding quadric %s %f %f %f %f %f %f %f %f %f %f\n", n, a,b,c,d,e,f,g,h,j,k);

		QuadricObjectPtr quad = make_shared<QuadricObject>(n, a, b, c, d, e, f, g, h, j, k);
		rawObjects.push_back(quad);
	};
	void add_sphere(char *n, double xm, double ym, double zm, double r){
		fprintf(stderr, "  adding sphere %s midpoint=(%f, %f, %f) r=%f", n, xm, ym, zm, r);

		SphereObjectPtr sphere = make_shared<SphereObject>(n, Vector(xm, ym, zm), r);
		rawObjects.push_back(sphere);
	};
	void add_property(char *n,  double ar, double ag, double ab, double r, double g, double b, double s, double m) {
		fprintf(stderr,"  adding prop %f %f %f %f %f\n", r, g, b, s, m);

		PropertyPtr prop = make_shared<Property>(n, Color(ar, ag, ab), Color(r, g, b), s, m);
		properties.push_back(prop);
	};
	void add_objekt(char *ns, char *np) {
		ObjektPtr objekt = nullptr;
		PropertyPtr property = nullptr;
		string ss(ns);
		string sp(np);

		for (ObjektPtr obj : rawObjects)
		{
			if (obj->getName() == ss)
			{
				objekt = obj;
				break;
			}
		}

		for (PropertyPtr prop : properties)
		{
			if (prop->getName() == sp)
			{
				property = prop;
				break;
			}
		}

		if(objekt == nullptr) {
			fprintf(stderr, "Objekt not found: %s\n", ns);
			exit(1);
		}
		if(property == nullptr) {
			fprintf(stderr, "Property not found: %s\n", np);
			exit(1);
		}
		
		objekt->setProperty(property);
		objekte.push_back(objekt);
		fprintf(stderr, "  adding object %s, property %s\n", ns, np);
	}
}

int main(int argc, _TCHAR* argv[])
{
	/* parse the input file */
	yyin = fopen("data/test.data","r");
	if(yyin == NULL) {
		fprintf(stderr, "Error: Konnte Datei nicht öffnen\n");
		return 1;
	}
	if (yyparse()) {
		fprintf(stderr, "Error: Konnte Datei nicht einlesen\n");
		std::cin.get();
		return 1;
	}
	fclose (yyin);
	
	
	Vector lookatVector = lookatPoint.vsub(eyePoint);

	double fovx = fieldOfViewX;
	double fovy = fovx / aspect;
	
	double width  = 2 * tan(0.5*fovx)*lookatVector.veclength();
	double height = width / aspect;
		
	Vector xdir = lookatVector.cross(up).normalize();
	Vector ydir = lookatVector.cross(xdir).normalize();

	Vector dx = xdir.svmpy(width / resolutionX);
	Vector dy = ydir.svmpy(height / resolutionY);

	Vector start = lookatPoint;
	start = start.vadd(xdir.svmpy(-0.5*width))
			     .vadd(ydir.svmpy(-0.5*height));

	Ray	ray(Vector(), eyePoint, 0);
	Image bild(resolutionX, resolutionY);

	for (int scanline=0; scanline < resolutionY; scanline++) {
		printf("%4d\r", resolutionY-scanline);
	
		Vector renderPoint = start;
		
		for (int sx=0; sx < resolutionX; sx++) {
			ray.setDirection(renderPoint.vsub(ray.getOrigin()).normalize());

			Color color = ray.shade(objekte, lights, backgroundColor, globalAmbient);

			bild.set(sx, scanline,
				color.r > 1.0 ? 255 : int(255 * color.r),
				color.g > 1.0 ? 255 : int(255 * color.g),
				color.b > 1.0 ? 255 : int(255 * color.b));

			renderPoint = renderPoint.vadd(dx);
		}

		start = start.vadd(dy);
	}

	char *name = "raytrace-bild.ppm";
	bild.save(name);

	std::cin.get();
	return 0;
}

