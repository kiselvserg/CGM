#include "lowlevelgeometry.h"

Point::Point()
{
	point_[0] = 0;
	point_[1] = 0;
	point_[2] = 0;
}


Point::Point(const double& firstComponent, const double&  secondComponent, const double&  thirdComponent)
{
	point_[0] = firstComponent;
	point_[1] = secondComponent;
	point_[2] = thirdComponent;
}

double& Point::operator [](unsigned int index)
{
		return point_[index];
}

bool Point::operator == (Point a)
{
	return (fabs((*this)[0] - a[0]) < COMPARING_ERROR) &&
		   (fabs((*this)[1] - a[1]) < COMPARING_ERROR) &&
		   (fabs((*this)[2] - a[2]) < COMPARING_ERROR);
}

bool Point::operator == (double a)
{
	return (fabs((*this)[0] - a) < COMPARING_ERROR) &&
		   (fabs((*this)[1] - a) < COMPARING_ERROR) &&
		   (fabs((*this)[2] - a) < COMPARING_ERROR);
}

Point Point::operator + (Point a)
{
	return Point((*this)[0]+a[0], (*this)[1]+a[1], (*this)[2]+a[2]);
}

Point Point::operator - (Point a)
{
	return Point((*this)[0]-a[0], (*this)[1]-a[1], (*this)[2]-a[2]);
}

double Point::operator / (Point a)
{
    double temp1 = 0, temp2 = 0, temp3 = 0;
	if( (((a[0] != 0) + ((*this)[0] != 0)) != 1) ||
		(((a[1] != 0) + ((*this)[1] != 0)) != 1) ||
		(((a[2] != 0) + ((*this)[2] != 0)) != 1) )
		; // Генерируем исключение
	else
	{
		temp1 = (*this)[0]/(a[0] + (a[0] == 0));
		temp2 = (*this)[1]/(a[1] + (a[1] == 0));
		temp3 = (*this)[2]/(a[2] + (a[2] == 0));
	}
	if(temp1 != temp2 || temp2 != temp3)
		; // Генерируем исключение
	return temp1;

}

Point& Point::operator += (Point a)
{
	(*this)[0] += a[0];
	(*this)[1] += a[1];
	(*this)[2] += a[2];
	return (*this);

}

const double& Point::getComponent(uint index) const
{
	return point_[index];
}


StraightLine::StraightLine()
{

}


Point& StraightLine::operator [](uint index)
{
		return points_[index];
}

const Point& StraightLine::getPoint(uint index) const
{
		return points_[index];
}


Piece::Piece(const Point& point1, const Point& point2)
{
	points_[0] = point1;
	points_[1] = point2;
}

Point& Piece::operator [](unsigned int index)
{
		return points_[index];
}

Point& Piece::getFirstPoint()
{
	return points_[0];
}

Point& Piece::getSecondPoint()
{
	return points_[1];
}

Plane::Plane(double firstCoefficient, double secondCoefficient, double thirdCoefficient, double fourthCoefficient)
{
	coefficients_[0] = firstCoefficient;
	coefficients_[1] = secondCoefficient;
	coefficients_[2] = thirdCoefficient;
	coefficients_[3] = fourthCoefficient;
}

double& Plane::operator [](uint index)
{
		return coefficients_[index];
}

const double& Plane::getCoefficient(uint index) const
{
		return coefficients_[index];
}

PlanesGroup_xyzPlanesSymmetry::PlanesGroup_xyzPlanesSymmetry(const Plane& plane)
{
	unsigned char counter = 0, temp = 0;
	planes_.push_back(plane);
	for(unsigned char i=0; i<3; ++i)
		if(planes_.front()[i] != 0)
			planes_.insert(++planes_.begin(), planes_.begin(), planes_.end());

	for(unsigned char i=0, k=1; i<3; ++i)
		if(planes_.front()[i] != 0)
		{
			temp = planes_.size()/pow(2, k);
			for(auto j = planes_.begin(); j != planes_.end(); ++j, ++counter)
				(*j)[i] *= 1 + (-2)*(bool)((counter/temp)%2 != 0);
			++k; counter = 0;
		}
}


bool sortPointsOnStraightLine(list<Point>* points, Point directingVector)
{
	if(points->size() < 3)
		return true;
    double alpha = 0;
	bool check = true;
	list<Point>::iterator i=(++(++(points->begin())));

	alpha = (*(++points->begin()) - points->front())/directingVector;
	for (; check != false && i != points->end(); ++i)
		check = alpha*(((*i) - points->front())/directingVector) > 0;
	if(check == false)
		points->splice(points->begin(), *points, i, points->end());
	return true;
}


schar pointProvisionRelativeToPlane(const Point& point, const Plane& plane)
{
	return ((plane.getCoefficient(0)*point.getComponent(0) + plane.getCoefficient(1)*point.getComponent(1) +
				plane.getCoefficient(2)*point.getComponent(2) + plane.getCoefficient(3)) > COMPARING_ERROR)
			-
		   ((plane.getCoefficient(0)*point.getComponent(0) + plane.getCoefficient(1)*point.getComponent(1) +
				plane.getCoefficient(2)*point.getComponent(2) + plane.getCoefficient(3)) < -COMPARING_ERROR);
}


bool planeCrossingByStraightLine(Plane plane, StraightLine line, Point* crossingPoint)
{
	Point bufPoint;
    double numerator = 0, denominator = 0, alpha = 0;
	bufPoint[0] = line[0][0] - line[1][0];
	bufPoint[1] = line[0][1] - line[1][1];
	bufPoint[2] = line[0][2] - line[1][2];
	numerator = plane[3] + plane[0]*line[0][0] + plane[1]*line[0][1] + plane[2]*line[0][2];
	/*
		crossingPoint->operator [](0) = piece[0][0];
		crossingPoint->operator [](1) = piece[0][1];
		crossingPoint->operator [](2) = piece[0][2];
		return true;
	*/
	denominator = - plane[0]*bufPoint[0] - plane[1]*bufPoint[1] - plane[2]*bufPoint[2];
	if(denominator != 0)
	{
		alpha = numerator/denominator;
		if(crossingPoint != 0)
		{
			crossingPoint->operator [](0) = bufPoint[0]*alpha + line[0][0];
			crossingPoint->operator [](1) = bufPoint[1]*alpha + line[0][1];
			crossingPoint->operator [](2) = bufPoint[2]*alpha + line[0][2];
		}
		return true;

	}
	else
		return false;
}

bool planeCrossingByPiece(Plane plane, Piece piece, Point* crossingPoint)
{
	StraightLine line;
	line[0] = piece[0];
	line[1] = piece[1];
	Point* tempCrossingPoint = new Point;
	if(planeCrossingByStraightLine(plane, line, tempCrossingPoint))
	{
		if(crossingPoint != 0)
			*crossingPoint = *tempCrossingPoint;

		ushort i=0;
		for(i=0; piece[0][i] == piece[1][i]; ++i)
			;
		if(((piece[0][i] <= (*tempCrossingPoint)[i]) && (piece[1][i] >= (*tempCrossingPoint)[i])) ||
		   ((piece[0][i] >= (*tempCrossingPoint)[i]) && (piece[1][i] <= (*tempCrossingPoint)[i])))
			return true;
	}
	return false;
}

// Не дописано
bool planeCrossingByPlane(Plane plane1, Plane plane2, StraightLine* crossingStraightLine)
{
	Point directingVector(plane1[1]*plane2[2] - plane1[2]*plane2[1],
						  plane1[2]*plane2[0] - plane1[0]*plane2[2],
						  plane1[0]*plane2[1] - plane1[1]*plane2[0]);
	
}
