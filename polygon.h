#ifndef MyPolygon_H
#define MyPolygon_H

#include <QtOpenGL>

#include <utility>
#include <vector>

#define ushort ushort

using namespace std;

struct point
{
    point() {}
    point(GLfloat x, GLfloat y, GLfloat z) { point_[0] = x; point_[1] = y; point_[2] = z; }
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

class MyPolygon
{
	private:
        vector<point> vertexes_;
	public:

        MyPolygon();
        MyPolygon(vector<point> vertexes);
        MyPolygon& operator = (MyPolygon const & MyPolygon);
		void addVertex(const point &vertex); // Добавляем вершину (в конец, а последовательность важна)
        void drawMyPolygon(); // Рисуем полигон


		// Принимаем плоскость и две ссылки на указатели
		// Если функция создаёт полигоны, то первый обязательно НАД секущей плоскостью (>0)
        sectionFuncReturn MyPolygonSection(vector<GLfloat> plane, MyPolygon*& MyPolygonPointer1, MyPolygon*& MyPolygonPointer2);

        //void drawMyPolygon();

};



#endif // MyPolygon_H
