#pragma once

#include "Objekt.h"
#include <vector>
#include <map>

class Triangle : public Objekt
{
	Vector p0, p1, p2;
public:
	Triangle() : Objekt("") {};
	Triangle(Vector p0, Vector p1, Vector p2) : Objekt(""), p0(p0), p1(p1), p2(p2) {};
	~Triangle();

	const Vector& vertex(int i);

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray) const override;
	double intersect(const Ray& ray, float weight[3]) const;
};

class PolyObject : public Objekt
{
private:
	std::vector<Triangle> triangles;
	std::map<Vector, Triangle> intersectedTriangles;
public:
	PolyObject(char *n) : Objekt(n) {};
	~PolyObject();

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray) const override;

	void addTriangle(Vector p0, Vector p1, Vector p2) { triangles.emplace_back(p0, p1, p2); }
};

typedef std::shared_ptr<PolyObject> PolyObjectPtr;
