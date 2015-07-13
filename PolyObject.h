#pragma once

#include "Objekt.h"
#include <vector>
#include <array>

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

	void setTextureCoords(Vector t0, Vector t1, Vector t2);

	Vector get_normal(Vector& v) const override;

	Color get_texture_color(const Vector& intersection) const override;
	double intersect(const Ray& ray, ObjektConstPtr* child) const override;
	Vector barycentric(const Vector& point) const;

	std::array<const Vector*, 3> getPoints() const { return std::array<const Vector*, 3>{{ &p0, &p1, &p2 }}; }
};

typedef std::shared_ptr<Triangle> TrianglePtr;

class PolyObject : public Objekt
{
private:
	std::vector<TrianglePtr> triangles;

	Vector boundingSphereCenter;
	double boundingSphereRadius;

	void calcBoundingSphere();
	bool intersectsWithBoundingSphere(const Ray& ray) const;
public:
	PolyObject(char *n) : Objekt(n) {};
	PolyObject(const std::string& name, std::vector<TrianglePtr>& triangles)
		: Objekt(name), triangles(triangles)
	{
		calcBoundingSphere();
	}
	~PolyObject();

	Vector get_normal(Vector& v) const override;
	double intersect(const Ray& ray, ObjektConstPtr* outChild) const override;

	void setProperty(PropertyPtr property) override;
};

typedef std::shared_ptr<PolyObject> PolyObjectPtr;
