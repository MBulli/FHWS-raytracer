#pragma once

#include "Objekt.h"
#include <vector>
#include <map>

class Triangle : public Objekt
{
	Vector p0, p1, p2;
	Vector e1, e2;
public:
	Triangle() : Objekt("") {};
	Triangle(Vector p0, Vector p1, Vector p2) 
		: Objekt(""), p0(p0), p1(p1), p2(p2), e1(p1.vsub(p0)), e2(p2.vsub(p0))
	{};
	~Triangle();

	const Vector& vertex(int i);

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray, ObjektConstPtr* child) const override;
	double intersect(const Ray& ray, float weight[3]) const;
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
	void addTriangle(Vector p0, Vector p1, Vector p2) { triangles.emplace_back(std::make_shared<Triangle>(p0, p1, p2)); }
};

typedef std::shared_ptr<PolyObject> PolyObjectPtr;
