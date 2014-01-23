#include <QCoreApplication>
#include "polygon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GLfloat width = 1.0f, height = 1.0f, depth = 1.0f;

    std::vector<point> v = { point(-width, -height, -depth),
                             point(width, -height, -depth),
                             point(width,  height, -depth),
                             point(-width,  height, -depth),
                             point(-width, -height,  depth),
                             point(width, -height,  depth),
                             point(width,  height,  depth),
                             point(-width,  height,  depth)
                           };
    MyPolygon *p = new MyPolygon(v);
    p->drawMyPolygon();
    return a.exec();
}
