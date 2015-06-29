// raytrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 
#include "Ray.h"
#include "Color.h"
#include "Image.h"
#include "vector"

#include <iostream>

const double SCREENWIDTH = 1000;
const double SCREENHEIGHT = 1000;

using namespace std;

vector<Surface> surfaces;
vector<Property> properties;
vector<Objekt> objekte;
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
		surfaces.push_back(Surface(n, a,b,c,d,e,f,g,h,j,k));
	};
	void add_sphere(char *n, double xm, double ym, double zm, double r){
		fprintf(stderr, "  adding sphere %s midpoint=(%f, %f, %f) r=%f", n, xm, ym, zm, r);

		// A = E = H = 1.0; B = C = F = 0.0; D = -2Xm, G = -2Ym, J = -2Zm und
		// K = Xm ^ 2 + Ym ^ 2 + Zm ^ 2 - Radius ^ 2
		double a, e, h;
		double b, c, f;

		a = e = h = 1;
		b = c = f = 0;

		double d = -2 * xm;
		double g = -2 * ym;
		double j = -2 * zm;
		double k = xm*xm + ym*ym + zm*zm - r*r;

		surfaces.push_back(Surface(n, a, b, c, d, e, f, g, h, j, k));
	};
	void add_property(char *n,  double ar, double ag, double ab, double r, double g, double b, double s, double m) {
		fprintf(stderr,"  adding prop %f %f %f %f %f\n", r, g, b, s, m);
		properties.push_back(Property(n, Color(ar, ag, ab), Color(r, g, b), s, m));
	};
	void add_objekt(char *ns, char *np) {
		Surface *s = NULL;
		Property *p = NULL;
		string ss(ns);
		string sp(np);

		for(vector<Surface>::iterator i = surfaces.begin(); i != surfaces.end(); ++i) 
			if(i->getName() == ss) {
				s = &(*i);
				break;
			}
		for(vector<Property>::iterator i = properties.begin(); i != properties.end(); ++i) 
			if(i->getName() == sp) {
				p = &(*i);
				break;
			}

		if(s == NULL) {
			fprintf(stderr, "Surface not found: %s\n", ns);
			exit(1);
		}
		if(p == NULL) {
			fprintf(stderr, "Property not found: %s\n", np);
			exit(1);
		}
		objekte.push_back(Objekt(s, p));
		fprintf(stderr, "  adding object: surface %s, property %s\n", ns, np);
	}
}

int main(int argc, _TCHAR* argv[])
{
	/* parse the input file */
	yyin = fopen("data/test.data","r");
	if(yyin == NULL) {
		fprintf(stderr, "Error: Konnte Datei nicht �ffnen\n");
		return 1;
	}
	if (yyparse()) {
		fprintf(stderr, "Error: Konnte Datei nicht einlesen\n");
		std::cin.get();
		return 1;
	}
	fclose (yyin);
	
	
	Vector eye(eyePoint.x, eyePoint.y, eyePoint.z);
	Vector lookatVector = lookatPoint.vsub(eyePoint);

	Ray	ray(lookatVector.normalize(), eye, 0);

	double width = resolutionX;
	double height = resolutionY;
	double aspect = width / height;

	double fovx = fieldOfViewX;
	double fovy = fovx / aspect;
	double x0 = 2 * (0 - (width / 2))*tan(fovx / 2.0) / width;
	double y0 = 2 * (0 - (height / 2))*tan(fovy / 2.0) / height;
	double dx = 2 * tan(fovx / 2.0) / width;
	double dy = 2 * tan(fovy / 2.0) / height;


	Image bild(resolutionX, resolutionY);

	double y = y0;
	for (int scanline=0; scanline < resolutionY; scanline++) {
		printf("%4d\r", resolutionY-scanline);

		y += dy;
		double x = x0;

		for (int sx=0; sx < resolutionX; sx++) {
			x += dx;
			ray.setDirection(Vector(x, y, -1.0).vsub(ray.getOrigin()).normalize());

			Color color = ray.shade(objekte, lights, backgroundColor, globalAmbient);

			bild.set(sx, scanline,
				color.r > 1.0 ? 255 : int(255 * color.r),
				color.g > 1.0 ? 255 : int(255 * color.g),
				color.b > 1.0 ? 255 : int(255 * color.b));
		}
	}

	char *name = "raytrace-bild.ppm";
	bild.save(name);

	std::cin.get();
	return 0;
}

