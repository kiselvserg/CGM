#ifndef LOWLEVELGEOMETRY_H
#define LOWLEVELGEOMETRY_H

#include <QtOpenGL>

#include <utility>
#include <vector>
#include <error.h>


#define schar signed char

#define COMPARING_ERROR 0.0001

using namespace std;

struct Point
{
    double point_[3];
	Point();
    Point(const double& firstComponent, const double&  secondComponent, const double&  thirdComponent);
	bool operator == (Point a);
    bool operator == (double a);
	Point operator + (Point a);
	Point operator - (Point a);
    double operator / (Point a);
	Point& operator += (Point a);
    double& operator [](unsigned int index);
    const double& getComponent(unsigned int index) const;
};

struct StraightLine
{
	Point points_[2];
	StraightLine();
	StraightLine(const Point& point1, const Point& point2);
	Point& operator [](uint index);
	const Point& getPoint(uint index) const;
};

/*
struct StraightLine
{
	Point point_;
	Point vector_;
	StraightLine(const Point& point, const Point& vector);
	Point& operator [](unsigned int index);
	Point& getPoint();
	Point& getVector();
};
*/

struct Piece
{
	Point points_[2];
	Piece(const Point& point1, const Point& point2);
	Point& operator [](unsigned int index);
	Point& getFirstPoint();
	Point& getSecondPoint();
};

struct Plane
{
    double coefficients_[4];

    Plane(double firstCoefficient, double secondCoefficient, double thirdCoefficient, double fourthCoefficient);
    double& operator [](uint index);
    const double& getCoefficient(uint index) const;
};

struct PlanesGroup_xyzPlanesSymmetry
{
	list<Plane> planes_;

	PlanesGroup_xyzPlanesSymmetry(const Plane& plane);
	Plane& operator [](uint index);
	const Plane& getPlane(uint index) const;
};

bool sortPointsOnStraightLine(list<Point>* points, Point directingVector);

schar pointProvisionRelativeToPlane(const Point& point, const Plane& plane);

bool planeCrossingByStraightLine(Plane plane, StraightLine line, Point* crossingPoint);

bool planeCrossingByPiece(Plane plane, Piece piece, Point* crossingPoint);



bool planeCrossingByPlane(Plane plane1, Plane plane2, StraightLine* crossingStraightLine);
#endif // LOWLEVELGEOMETRY_H
