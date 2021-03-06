#include "stdafx.h"
#include "Parser.h"
#include "QuadricObject.h"
#include "SphereObject.h"
#include <iostream>
#include "PolyObject.h"
#include "WavefrontObjParser.h"

using namespace std;

std::vector<PropertyPtr> properties;
std::vector<ObjektPtr> rawObjects; // objects without property
std::vector<ObjektPtr> objekte;
std::vector<LightPtr> lights;

string currentPolyName;
vector<TrianglePtr> currentPolyTriangles;
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

double DOFSamples;
double apatureRadius;
double focalDistance;

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
		fprintf(stderr, "Error: Konnte Datei nicht �ffnen\n");
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

	// Depth of field
	void set_apertureRadius(double r) {
		apatureRadius = r;
	}
	void set_focalDistance(double d) {
		focalDistance = d;
	}
	void set_dofSamples(int s) {
		DOFSamples = s;
	}

	// lights
	void add_dirlight(char *n, double dirx, double diry, double dirz, double colr, double colg, double colb) {
		fprintf(stderr, "  adding directional light %f %f %f %f %f %f\n", dirx, diry, dirz, colr, colg, colb);

		LightPtr light = make_shared<DirectionalLight>(Color(colr, colg, colb), Vector(dirx, diry, dirz).normalize());
		lights.push_back(light);
	};

	
	void add_ptrlight(char* n, double posx, double posy, double posz, double colr, double colg, double colb) {
		fprintf(stderr, "  adding point light %f %f %f %f %f %f\n", posx, posy, posz, colr, colg, colb);

		LightPtr light = make_shared<PointLight>(Color(colr, colg, colb), Vector(posx, posy, posz));
		lights.push_back(light);
	};

	void add_circle_area_light(char* n, double posx, double posy, double posz, double dirx, double diry, double dirz, double radius, double colr, double colg, double colb)
	{
		fprintf(stderr, "  adding circle area light");
		LightPtr light = make_shared<CircleAreaLight>(Color(colr, colg, colb), 
													  Vector(posx, posy, posz),
													  Vector(dirx, diry, dirz), radius);
		lights.push_back(light);
	}


	// geometry
	void add_quadric(char *n, double a, double b, double c, double d, double e, double f, double g, double h, double j, double k) {
		fprintf(stderr, "  adding quadric %s %f %f %f %f %f %f %f %f %f %f\n", n, a, b, c, d, e, f, g, h, j, k);

		QuadricObjectPtr quad = make_shared<QuadricObject>(n, a, b, c, d, e, f, g, h, j, k);
		rawObjects.push_back(quad);
	};
	void add_sphere(char *n, double xm, double ym, double zm, double r){
		fprintf(stderr, "  adding sphere %s midpoint=(%f, %f, %f) r=%f", n, xm, ym, zm, r);

		SphereObjectPtr sphere = make_shared<SphereObject>(n, Vector(xm, ym, zm), r);
		rawObjects.push_back(sphere);
	};
	void add_wavefront(char* filename)
	{
		fprintf(stderr, "  wavefront object from file %s\n", filename);

		WavefrontObjParser parser = WavefrontObjParser(std::string(filename));
		
		parser.parseFile();

		for (const PolyObjectPtr& obj : parser.generateGeneratePolyObejekts())
		{
			if (obj->getName().length() == 0)
			{
				fprintf(stderr, "ERROR: Unnamed object in wavefront file %s", filename);
			}
			rawObjects.push_back(obj);
		}
	}

	void add_property(char *n, double ar, double ag, double ab, double r, double g, double b, double s, double shininess, double m, char* textureFilename, double refraction, double refractionIndex, double glossy, int glossySamples, double opacity) {
		fprintf(stderr, "  adding prop %f %f %f %f %f %s %f %f %f %d %f\n", r, g, b, s, m, textureFilename, refraction, refractionIndex, glossy, glossySamples, opacity);

		PropertyPtr prop = make_shared<Property>(n, Color(ar, ag, ab), Color(r, g, b), s, shininess, m, refraction, refractionIndex, glossy, glossySamples, opacity);

		std::string textureFile(textureFilename);
		if (textureFile.compare("null") != 0)
		{
			TexturePtr texture = make_shared<Texture>(textureFilename);
			texture->load();
			prop->setTexture(texture);
		}

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
		currentPolyName.assign(n);
		currentPolyVertices.clear();
		currentPolyTriangles.clear();
		currentTexMappings.clear();
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

		currentPolyTriangles.push_back(make_shared<Triangle>(v0, v1, v2, t0, t1, t2));
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

		currentPolyTriangles.push_back(make_shared<Triangle>(v0, v1, v2, t0, t1, t2));
		currentPolyTriangles.push_back(make_shared<Triangle>(v2, v3, v0, t2, t3, t0));
	}

	void add_poly_texmap(int index, double u, double v)	{
		currentTexMappings[index] = Vector(u, v, 0);
	}

	void end_poly_object() {
		PolyObjectPtr obj = make_shared<PolyObject>(currentPolyName, currentPolyTriangles);
		rawObjects.push_back(obj);

		currentPolyName.clear();
		currentPolyTriangles.clear();
		currentPolyVertices.clear();
		currentTexMappings.clear();
	}
}

// GETTER methods
const std::vector<PropertyPtr>& Parser::getProperties() const { return properties; }
const std::vector<ObjektPtr>&   Parser::getObjects()	const { return objekte; }
const std::vector<LightPtr>&    Parser::getLights()		const { return lights; }

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
double        Parser::getDOFSamples()	const { return DOFSamples; }
double		  Parser::getApatureRadius()   const { return apatureRadius; }
double        Parser::getFocalDistance()   const { return focalDistance; }
