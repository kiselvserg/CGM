#include "polyhedron.h"

Polyhedron::Polyhedron()
{
}

Polyhedron::Polyhedron(const vector<Polygon>& polygons)
{
	polygons_ = polygons;
}

void Polyhedron::addPolygonsList(const list<Polygon> &polygons)
{
	for(list<Polygon>::const_iterator i = polygons.begin() ; i != polygons.end(); ++i)
		polygons_.push_back(*i);
}

void Polyhedron::draw()
{
	for(ushort i=0; i<polygons_.size(); ++i)
		polygons_[i].draw();
}

bool Polyhedron::polyhedronSection(const Plane& plane, Polyhedron* polyhedron1, Polyhedron* polyhedron2)
{
	Polygon tempPolygon1, tempPolygon2;
	list<Point> tempSectionLine;
	list<Polygon> polygonsList1, polygonsList2;
	list<list<Point>> sectionLines;
	for(ushort i=0; i<polygons_.size(); ++i)
	{

		if(polygons_[i].polygonSection(plane, &tempPolygon1, &tempPolygon2, &tempSectionLine))
		{
			polygonsList1.push_back(tempPolygon1);
			polygonsList2.push_back(tempPolygon2);
			sectionLines.push_back(tempSectionLine);
		}

		tempPolygon1.clear(); tempPolygon2.clear(); tempSectionLine.clear();

	}

	// Костыль! Такой большой и деревянный. Нет, на самом деле это можно оставить, но так не хочется.

	while(sectionLines.size() > 2)
	{

		for(auto i = ++sectionLines.begin(); i != sectionLines.end(); ++i)
			if(i->front() == sectionLines.front().back())
			{
				sectionLines.front().push_back(i->back());
				sectionLines.erase(i);
				break;
			}
			else if(i->back() == sectionLines.front().back())
			{
				sectionLines.front().push_back(i->front());
				sectionLines.erase(i);
				break;
			}
	}
	if(sectionLines.front().size() > 2)
	{
		polygonsList1.push_back(Polygon(sectionLines.front()));
		polygonsList2.push_back(Polygon(sectionLines.front()));
	}


	if(polyhedron1 != 0)
		polyhedron1->addPolygonsList(polygonsList1);
	if(polyhedron2 != 0)
		polyhedron2->addPolygonsList(polygonsList2);
}
