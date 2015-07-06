#include "stdafx.h"
#include "Parser.h"
#include "QuadricObject.h"
#include "SphereObject.h"
#include <iostream>
#include "PolyObject.h"

using namespace std;

std::vector<PropertyPtr> properties;
std::vector<ObjektPtr> rawObjects; // objects without property
std::vector<ObjektPtr> objekte;
std::vector<Light> lights;

PolyObjectPtr currentPolyObject = nullptr;
vector<Vector> currentPolyVertices;
map<int, Vector> currentTexMappings;

int resolutionX = 1250;
int resolutionY = 1250;
Color backgroundColor;
Color globalAmbient;

Vector eyePoint;
Vector lookatPoint;
Vector up;
double fieldOfViewX = NAN; // in rad
double fieldOfViewY = NAN; // in rad
double aspect;

extern "C" {
	extern FILE *yyin;
	int yyparse();
}

Parser::~Parser()
{
}

bool Parser::start()
{
	/* parse the input file */
	yyin = fopen(&filename[0], "r");
	if (yyin == NULL) {
		fprintf(stderr, "Error: Konnte Datei nicht öffnen\n");
		return false;
	}
	if (yyparse()) {
		fprintf(stderr, "Error: Konnte Datei nicht einlesen\n");
		std::cin.get();
		return false;
	}
	fclose(yyin);

	return true;
}


extern "C" {
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
		if (isnan(fieldOfViewY)) {
			fieldOfViewX = fovxInDeg * M_PI / 180.0;
		} else {
			fprintf(stderr, "fovy already set. Ignoring fovx.");
		}
	}
	void set_fovy(double fovyInDeg)	{
		if (isnan(fieldOfViewX)) {
			fieldOfViewY = fovyInDeg * M_PI / 180.0;
		} else {
			fprintf(stderr, "fovx already set. Ignoring fovy.");
		}
	}

	void set_aspect(double a) {
		aspect = a;
	}
	void set_global_ambience(double r, double g, double b) {
		globalAmbient = Color(r, g, b);
	}

	// light
	void add_light(char *n, double dirx, double diry, double dirz, double colr, double colg, double colb) {
		fprintf(stderr, "  adding light %f %f %f %f %f %f\n", dirx, diry, dirz, colr, colg, colb);
		lights.push_back(Light(Vector(dirx, diry, dirz).normalize(), Color(colr, colg, colb)));
	};

	// geometry
	void add_quadric(char *n, double a, double b, double c, double d, double e, double f, double g, double h, double j, double k) {
		fprintf(stderr, "  adding quadric %s %f %f %f %f %f %f %f %f %f %f\n", n, a, b, c, d, e, f, g, h, j, k);

		QuadricObjectPtr quad = make_shared<QuadricObject>(n, a, b, c, d, e, f, g, h, j, k);
		rawObjects.push_back(quad);
	};
	void add_sphere(char *n, double xm, double ym, double zm, double r){
		fprintf(stderr, "  adding sphere %s midpoint=(%f, %f, %f) r=%f", n, xm, ym, zm, r);

		SphereObjectPtr sphere = make_shared<SphereObject>(n, Vector(xm, ym, zm), r);
		if (r == 50) {
			TexturePtr tex = make_shared<Texture>("chess.png");
			tex->load();
			sphere->setTexture(tex);
		}

		rawObjects.push_back(sphere);
	};
	void add_property(char *n, double ar, double ag, double ab, double r, double g, double b, double s, double shininess, double m) {
		fprintf(stderr, "  adding prop %f %f %f %f %f\n", r, g, b, s, m);

		PropertyPtr prop = make_shared<Property>(n, Color(ar, ag, ab), Color(r, g, b), s, shininess, m);
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

		if (objekt == nullptr) {
			fprintf(stderr, "Objekt not found: %s\n", ns);
			exit(1);
		}
		if (property == nullptr) {
			fprintf(stderr, "Property not found: %s\n", np);
			exit(1);
		}

		objekt->setProperty(property);
		objekte.push_back(objekt);
		fprintf(stderr, "  adding object %s, property %s\n", ns, np);
	}

	// Poly objects
	void begin_poly_object(char* n)	{
		currentPolyObject = make_shared<PolyObject>(n);
		currentPolyVertices.clear();
	}

	void add_poly_vertex(double x, double y, double z) {
		currentPolyVertices.emplace_back(x, y, z);
	}

	void add_poly_triangle(int i0, int i1, int i2) {
		Vector& v0 = currentPolyVertices.at(i0-1);
		Vector& v1 = currentPolyVertices.at(i1-1);
		Vector& v2 = currentPolyVertices.at(i2-1);

		Vector& t0 = currentTexMappings[i0];
		Vector& t1 = currentTexMappings[i1];
		Vector& t2 = currentTexMappings[i2];

		currentPolyObject->addTriangle(v0, v1, v2, t0, t1, t2);
	}

	void add_poly_rectangle(int i0, int i1, int i2, int i3)	{
		Vector& v0 = currentPolyVertices.at(i0-1);
		Vector& v1 = currentPolyVertices.at(i1-1);
		Vector& v2 = currentPolyVertices.at(i2-1);
		Vector& v3 = currentPolyVertices.at(i3-1);

		Vector& t0 = currentTexMappings[i0];
		Vector& t1 = currentTexMappings[i1];
		Vector& t2 = currentTexMappings[i2];
		Vector& t3 = currentTexMappings[i3];

		currentPolyObject->addTriangle(v0, v1, v2, t0, t1, t2);
		currentPolyObject->addTriangle(v2, v3, v0, t2, t3, t0);
	}

	void add_poly_texmap(int index, double u, double v)	{
		currentTexMappings[index] = Vector(u, v, 0);
	}

	void end_poly_object() {
		rawObjects.push_back(currentPolyObject);
		currentPolyObject = nullptr;
		currentPolyVertices.clear();
		currentTexMappings.clear();
	}
}

// GETTER methods
const std::vector<PropertyPtr>& Parser::getProperties() const { return properties; }
const std::vector<ObjektPtr>&   Parser::getObjects()	const { return objekte; }
const std::vector<Light>&       Parser::getLights()		const { return lights; }

int Parser::getResoultionX() const { return resolutionX; }
int Parser::getResoultionY() const { return resolutionY; }

const Color& Parser::getBackgroundColor() const { return backgroundColor; }
const Color& Parser::getGlobalAmbient()   const { return globalAmbient; }

const Vector& Parser::getEyePoint()		const { return eyePoint; }
const Vector& Parser::getLookatPoint()  const { return lookatPoint; }
const Vector& Parser::getUp()           const { return up; }
double        Parser::getFieldOfViewX() const { return fieldOfViewX; }
double        Parser::getFieldOfViewY() const { return fieldOfViewY; }
double		  Parser::getAspectRatio()  const { return aspect; }