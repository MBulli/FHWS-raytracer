#pragma once

#include "Objekt.h"
#include <vector>
#include <map>

class Triangle : public Objekt
{
	Vector p0, p1, p2;
	Vector e1, e2;
	Vector tex0, tex1, tex2;
public:
	Triangle() : Objekt("") {};
	Triangle(Vector p0, Vector p1, Vector p2,
			 Vector t0 = Vector(), Vector t1 = Vector(), Vector t2 = Vector()) 
			 : Objekt(""), p0(p0), p1(p1), p2(p2), e1(p1.vsub(p0)), e2(p2.vsub(p0)), tex0(t0), tex1(t1), tex2(t2)
	{};
	~Triangle();

	const Vector& vertex(int i);

	Vector get_normal(Vector& v) const override;

	Color get_color(const Ray& ray, const Vector& intersection, const Color& globalAmbient) const override;
	double intersect(const Ray& ray, ObjektConstPtr* child) const override;

	Vector barycentric(const Vector& point) const;
};

typedef std::shared_ptr<Triangle> TrianglePtr;

class PolyObject : public Objekt
{
private:
	std::vector<TrianglePtr> triangles;
public:
	PolyObject(char *n) : Objekt(n) {};
	~PolyObject();

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray, ObjektConstPtr* outChild) const override;

	void setProperty(PropertyPtr property) override;
	void addTriangle(Vector p0, Vector p1, Vector p2, Vector t0, Vector t1, Vector t2) { triangles.emplace_back(std::make_shared<Triangle>(p0, p1, p2, t0, t1, t2)); }
	void addTriangle(TrianglePtr tri) { triangles.push_back(tri); }
};

typedef std::shared_ptr<PolyObject> PolyObjectPtr;
