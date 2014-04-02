#ifndef POLYGON_H
#define POLYGON_H

#include <QtOpenGL>

#include <utility>
#include <vector>
#include <list>
//#include <tuple>

#include "lowlevelgeometry.h"


using namespace std;



struct sectionFuncReturn
{
	vector<Point> newPoints_; // Новые вершины
	vector<ushort>  morePoints_; // При подстановке в уравнение плоскости этих вершин > 0
	vector<ushort>  lessPoints_; // < 0
	vector<ushort>  onPoints_; // == 0
	sectionFuncReturn(vector<Point> newPoints,
					  vector<ushort> morePoints,
					  vector<ushort> lessPoints,
					  vector<ushort> onPoints);
};

class Polygon
{
	private:
		vector<Point> vertexes_;
		array<float, 4> color_;
	public:

		Polygon(array<float, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
		Polygon(vector<Point> vertexes, array<float, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
		Polygon(list<Point> vertexes, array<float, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
        Polygon& operator = (Polygon const & polygon);
		void clear();
		inline void addVertex(const Point &vertex); // Добавляем вершину (в конец, а последовательность важна)
		void addVertexesList(const list<Point> &vertexes);
		void draw(); // Рисуем полигон


		// Принимаем плоскость и две ссылки на указатели
		// Если функция создаёт полигоны, то первый обязательно НАД секущей плоскостью (>0)
		bool polygonSection(Plane plane, Polygon* polygonPointer1, Polygon* polygonPointer2, list<Point>* sectionStraightLine);

		//void drawPolygon();

};



#endif // POLYGON_H
