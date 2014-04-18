#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "polygon.h"

class Polyhedron
{
private:
	vector<Polygon> polygons_;
public:
	Polyhedron();
	Polyhedron(const vector<Polygon>& polygons);
	void addPolygonsList(const list<Polygon> &polygons);
	void clear();
	void draw();
	bool polyhedronSection(const Plane& plane,
						   Polyhedron* polyhedron1,
						   Polyhedron* polyhedron2,
						   array<float, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});

	bool polyhedronGroupSection(const Plane& plane,
								const bool& xyzPlanesSymmetry,
								Polyhedron*& polyhedron1,
								Polyhedron*& polyhedron2,
								array<float, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
};

#endif // POLYHEDRON_H
