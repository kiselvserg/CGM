#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include "polygon.h"

class Polyhedron
{
private:
    vector<CPolygon> polygons_;
public:
	Polyhedron();
    Polyhedron(const vector<CPolygon>& polygons);
	// void setPolygons(const vector<CPolygon>& polygons) { polygons_ = polygons; }
    void addPolygonsList(const list<CPolygon> &polygons);
	void clear();
	void draw();
	bool polyhedronSection(const Plane& plane,
						   Polyhedron* polyhedron1,
						   Polyhedron* polyhedron2,
                           array<double, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});

	bool polyhedronGroupSection(const Plane& plane,
								const bool& xyzPlanesSymmetry,
								Polyhedron* polyhedron1,
								Polyhedron* polyhedron2,
                                array<double, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
};

#endif // POLYHEDRON_H
