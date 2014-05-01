#include "polyhedron.h"
#include <fstream>

Polyhedron::Polyhedron()
{
}

Polyhedron::Polyhedron(const vector<CPolygon>& polygons)
{
	polygons_ = polygons;
}

void Polyhedron::clear()
{
	polygons_.clear();
}

void Polyhedron::addPolygonsList(const list<CPolygon> &polygons)
{
    for(list<CPolygon>::const_iterator i = polygons.begin() ; i != polygons.end(); ++i)
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
                                   array<double, 4> color)
{
    CPolygon tempPolygon1, tempPolygon2;
	list<Point> tempSectionLine;
    list<CPolygon> polygonsList1, polygonsList2;
	list<list<Point>> sectionLines;

	// Для дебага

	for(ushort i=0; i < polygons_.size(); ++i)
	{
		if(polygons_[i].polygonSection(plane, &tempPolygon1, &tempPolygon2, &tempSectionLine))
		{

			polygonsList1.push_back(tempPolygon1);
			polygonsList2.push_back(tempPolygon2);
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
	// Костыль в костыле. Деревянная нога капитана Флинта (не помню была ли у него деревянная нога)
	// Поиск и удаление повторений.

	if(sectionLines.size() > 2)
		for(auto i = sectionLines.begin(), j = i; i != --sectionLines.end(); ++i, j = i)
			for(++j; j != sectionLines.end(); )
			{
				if((i->front() == j->front() && i->back() == j->back()) ||
				   (i->front() == j->back() && i->back() == j->front())	)
					j = sectionLines.erase(j);
				else
					++j;
			}


	for(bool endThis = false; sectionLines.size() > 2 && endThis != true; )
	{

		for(auto i = ++sectionLines.begin(); i != sectionLines.end(); ++i)
			if(i->front() == sectionLines.front().back())
			{
				/*
				if(sectionLines.front().front() == i->back())
				{
					endThis = true;
					break;
				}
				*/
				sectionLines.front().push_back(i->back());
				sectionLines.erase(i);
				break;
			}
			else if(i->back() == sectionLines.front().back())
			{
				/*
				if(sectionLines.front().front() == i->front())
				{
					endThis = true;
					break;
				}
				*/
				sectionLines.front().push_back(i->front());
				sectionLines.erase(i);
				break;
			}
	}

	if(sectionLines.size() > 0 && sectionLines.front().size() > 2)
	{
        polygonsList1.push_back(CPolygon(sectionLines.front(), color));
        polygonsList2.push_back(CPolygon(sectionLines.front(), color));
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
                            array<double, 4> color)
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
