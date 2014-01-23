#ifndef POLYGON_H
#define POLYGON_H

#include <QtOpenGL>

#include <utility>
#include <vector>

#define ushort ushort

using namespace std;

struct point
{
    GLfloat point_[3];
    GLfloat& operator [](unsigned int index);
};

struct sectionFuncReturn
{
	vector<point> newPoints_; // Новые вершины
	vector<ushort>  morePoints_; // При подстановке в уравнение плоскости этих вершин > 0
	vector<ushort>  lessPoints_; // < 0
	vector<ushort>  onPoints_; // == 0
	sectionFuncReturn(vector<point> newPoints,
					  vector<ushort> morePoints,
					  vector<ushort> lessPoints,
					  vector<ushort> onPoints);
};

class Polygon
{
	private:
        vector<point> vertexes_;
	public:

        Polygon();
        Polygon(vector<point> vertexes);
        Polygon& operator = (Polygon const & polygon);
		void addVertex(const point &vertex); // Добавляем вершину (в конец, а последовательность важна)
		void drawPolygon(); // Рисуем полигон


		// Принимаем плоскость и две ссылки на указатели
		// Если функция создаёт полигоны, то первый обязательно НАД секущей плоскостью (>0)
		sectionFuncReturn polygonSection(vector<GLfloat> plane, Polygon*& polygonPointer1, Polygon*& polygonPointer2);

		//void drawPolygon();

};



#endif // POLYGON_H
