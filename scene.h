#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QVector>
#include "lowlevelgeometry.h"
#include "polygon.h"
#include "polyhedron.h"

class Scene : public QGLWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);
    void paintGL();
    void setAlpha(double);
    void setBeta(double);
    void setGamma(double);
    void clipping(QVector<Plane> planes, QVector<QColor> colors);
    void clipping(array<int, 3>&, double eq, const QColor& color);
    void clearAll();
    void undo();

public slots:
    void showScene(int);

Q_SIGNALS:
    void clipChanged(int);


private:
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

    QPoint ptrMousePosition;
    list<CPolygon> polygons_;

    Plane* plane_;
    QColor color_;
    Polyhedron* polyhedron_;
    QVector<Polyhedron> previous_;

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_left();
    void rotate_right();
    void translate_down();
    void translate_up();
    void defaultScene();

    void drawAxis();

    void drawFigure();
    array<double, 4> getGLColor(const QColor& color);

 protected:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void wheelEvent(QWheelEvent* pe);
    void keyPressEvent(QKeyEvent* pe);

};

#endif // SCENE_H
