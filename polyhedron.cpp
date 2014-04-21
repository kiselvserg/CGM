#include "polyhedron.h"
#include <fstream>

Polyhedron::Polyhedron()
{
}

Polyhedron::Polyhedron(const vector<Polygon>& polygons)
{
	polygons_ = polygons;
}

void Polyhedron::clear()
{
	polygons_.clear();
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

bool Polyhedron::polyhedronSection(const Plane& plane,
								   Polyhedron* polyhedron1,
								   Polyhedron* polyhedron2,
								   array<float, 4> color)
{
	Polygon tempPolygon1, tempPolygon2;
	list<Point> tempSectionLine;
	list<Polygon> polygonsList1, polygonsList2;
	list<list<Point>> sectionLines;

	// Для дебага

	for(ushort i=0; i < polygons_.size(); ++i)
	{
		if(polygons_[i].polygonSection(plane, &tempPolygon1, &tempPolygon2, &tempSectionLine))
		{

			polygonsList1.push_back(tempPolygon1);
			polygonsList2.push_back(tempPolygon2);

			debugCounter.push_back(i);
		}
		else
		{
			if(!tempPolygon1.empty())
				polygonsList1.push_back(tempPolygon1);
			if(!tempPolygon2.empty())
				polygonsList2.push_back(tempPolygon2);
		}
		if(tempSectionLine.size() > 1)
			sectionLines.push_back(tempSectionLine);

		tempPolygon1.clear(); tempPolygon2.clear(); tempSectionLine.clear();

	}

	// Костыль! Такой большой и деревянный. Нет, на самом деле это можно оставить, но так не хочется.

	while((sectionLines.size() > 2) && !(sectionLines.front().back() == sectionLines.front().front()) )
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

	if(sectionLines.size() > 0 && sectionLines.front().size() > 2)
	{
		polygonsList1.push_back(Polygon(sectionLines.front(), color));
		polygonsList2.push_back(Polygon(sectionLines.front(), color));
	}


	if(polyhedron1 != 0)
	{
		polyhedron1->clear();
		polyhedron1->addPolygonsList(polygonsList1);
	}
	if(polyhedron2 != 0)
	{
		polyhedron2->clear();
		polyhedron2->addPolygonsList(polygonsList2);
	}
	return (polygonsList1.size() > 3) && (polygonsList2.size() > 3);
}

bool Polyhedron::polyhedronGroupSection(const Plane& plane,
							const bool& xyzPlanesSymmetry,
							//const bool& someVectorSymmetry,
							Polyhedron* polyhedron1,
							Polyhedron* polyhedron2,
							array<float, 4> color)
{
	bool temp = false;
	temp = temp || this->polyhedronSection(plane, polyhedron1, polyhedron2, color);


	if(xyzPlanesSymmetry == true)
	{
		PlanesGroup_xyzPlanesSymmetry planesXYZ(plane);
		for(auto i = ++planesXYZ.planes_.begin(); i != planesXYZ.planes_.end(); ++i)
			polyhedron1->polyhedronSection((*i), polyhedron1, polyhedron2, color);
	}

}
