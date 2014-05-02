#ifndef CPolygon_H
#define CPolygon_H

#include <QtOpenGL>

#include <utility>
#include <vector>
#include <list>
//#include <tuple>

#include "lowlevelgeometry.h"


using namespace std;


class CPolygon
{
	private:
		vector<Point> vertexes_;
        array<double, 4> color_;
	public:

        CPolygon(array<double, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
        CPolygon(vector<Point> vertexes, array<double, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
        CPolygon(list<Point> vertexes, array<double, 4> color = {{0.20f, 0.20f, 1.00f, 0.5f}});
        CPolygon& operator = (CPolygon const & CPolygon);
		void clear();
		inline void addVertex(const Point &vertex); // Добавляем вершину (в конец, а последовательность важна)
		void addVertexesList(const list<Point> &vertexes);
		void draw(); // Рисуем полигон
		bool empty();


		// Принимаем плоскость и две ссылки на указатели
		// Если функция создаёт полигоны, то первый обязательно НАД секущей плоскостью (>0)
        bool polygonSection(Plane plane,
                            CPolygon* CPolygonPointer1,
                            CPolygon* CPolygonPointer2,
							list<Point>* sectionStraightLine);

        //void drawCPolygon();

};



#endif // CPolygon_H
