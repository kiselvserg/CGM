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
	void draw();
	bool polyhedronSection(const Plane& plane, Polyhedron* polyhedron1, Polyhedron* polyhedron2);
};

#endif // POLYHEDRON_H
