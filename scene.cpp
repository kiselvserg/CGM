#include <QtGui>
#include <math.h>

#include "scene.h"

const static double pi=3.141593, k=pi/180;

GLfloat VertexArray[12][3];
GLfloat ColorArray[12][3];
GLubyte IndexArray[20][3];

Scene::Scene(QWidget* parent) : QGLWidget(parent), plane_(nullptr)
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=0.1;
}

void Scene::initializeGL()
{
	//glEnable(GL_MULTISAMPLE);
	GLint bufs;
	GLint samples;
	glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
	glGetIntegerv(GL_SAMPLES, &samples);
    qglClearColor(this->palette().color(QPalette::Window));
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    vector<Point> tempVector1;

    Point* PointPointer1 = new Point(5, 5, 5);
    Point* PointPointer2 = new Point(5, -5, 5);
    Point* PointPointer3 = new Point(-5, -5, 5);
    Point* PointPointer4 = new Point(-5, 5, 5);

    tempVector1.push_back(*PointPointer1);
    tempVector1.push_back(*PointPointer2);
    tempVector1.push_back(*PointPointer3);
    tempVector1.push_back(*PointPointer4);
    CPolygon	polygon1(tempVector1);
    //polygon1.draw();

    vector<Point> tempVector2;

    PointPointer1 = new Point(5, 5, 5);
    PointPointer2 = new Point(5, 5, -5);
    PointPointer3 = new Point(5, -5, -5);
    PointPointer4 = new Point(5, -5, 5);

    tempVector2.push_back(*PointPointer1);
    tempVector2.push_back(*PointPointer2);
    tempVector2.push_back(*PointPointer3);
    tempVector2.push_back(*PointPointer4);
    CPolygon	polygon2(tempVector2);
    //polygon2.draw();

    vector<Point> tempVector3;

    PointPointer1 = new Point(5, 5, 5);
    PointPointer2 = new Point(5, 5, -5);
    PointPointer3 = new Point(-5, 5, -5);
    PointPointer4 = new Point(-5, 5, 5);

    tempVector3.push_back(*PointPointer1);
    tempVector3.push_back(*PointPointer2);
    tempVector3.push_back(*PointPointer3);
    tempVector3.push_back(*PointPointer4);
    CPolygon	polygon3(tempVector3);
    //polygon3.draw();

    vector<Point> tempVector4;

    PointPointer1 = new Point(-5, -5, -5);
    PointPointer2 = new Point(-5, 5, -5);
    PointPointer3 = new Point(5, 5, -5);
    PointPointer4 = new Point(5, -5, -5);

    tempVector4.push_back(*PointPointer1);
    tempVector4.push_back(*PointPointer2);
    tempVector4.push_back(*PointPointer3);
    tempVector4.push_back(*PointPointer4);
    CPolygon	polygon4(tempVector4);
    //polygon4.draw();

    vector<Point> tempVector5;

    PointPointer1 = new Point(-5, -5, -5);
    PointPointer2 = new Point(-5, -5, 5);
    PointPointer3 = new Point(5, -5, 5);
    PointPointer4 = new Point(5, -5, -5);

    tempVector5.push_back(*PointPointer1);
    tempVector5.push_back(*PointPointer2);
    tempVector5.push_back(*PointPointer3);
    tempVector5.push_back(*PointPointer4);
    CPolygon	polygon5(tempVector5);
    //polygon5.draw();

    vector<Point> tempVector6;

    PointPointer1 = new Point(-5, -5, -5);
    PointPointer2 = new Point(-5, -5, 5);
    PointPointer3 = new Point(-5, 5, 5);
    PointPointer4 = new Point(-5, 5, -5);

    tempVector6.push_back(*PointPointer1);
    tempVector6.push_back(*PointPointer2);
    tempVector6.push_back(*PointPointer3);
    tempVector6.push_back(*PointPointer4);
    CPolygon	polygon6(tempVector6);
    //polygon6.draw();

    // Для особо одарённых

    // Создаём вектор полигонов
    //vector<CPolygon> polygons;

    // Запихиваем в него полигоны
    polygons_.push_back(polygon1);
    polygons_.push_back(polygon2);
    polygons_.push_back(polygon3);
    polygons_.push_back(polygon4);
    polygons_.push_back(polygon5);
    polygons_.push_back(polygon6);
    //Создаём полигедрон из полигонов
    polyhedron_ = new Polyhedron();
    polyhedron_->addPolygonsList(polygons_);
    previous_.append(*polyhedron_);
}

void Scene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

    if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
    else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(nSca, nSca, nSca);
    glTranslatef(0.0f, zTra, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);

    if(plane_ != nullptr)
        polyhedron_->polyhedronGroupSection(*plane_, true, polyhedron_, 0, getGLColor(color_));
    polyhedron_->draw();
}

void Scene::clipping(array<int, 3> &arr, double eq, const QColor &color)
{
    if(plane_ != nullptr) delete plane_;
    plane_ = new Plane(arr[0], arr[1], arr[2], eq);
    color_ = color;
    this->updateGL();
    previous_.append(*polyhedron_);
    emit clipChanged(previous_.size()-1);
}

void Scene::clearAll()
{
    polyhedron_->clear();
    polyhedron_->addPolygonsList(polygons_);
    previous_.clear();
    previous_.append(*polyhedron_);
    emit clipChanged(0);
    delete plane_;
    plane_ = nullptr;
    updateGL();
}

void Scene::undo()
{
    *polyhedron_ = previous_[previous_.size()-2];
    previous_.remove(previous_.size() - 1);
    emit clipChanged(previous_.size()-1);
    delete plane_;
    plane_ = nullptr;
    updateGL();
}

void Scene::showScene(int value)
{
    qDebug() << "value set:" << value;
    if(value >= previous_.size()) return;
    *polyhedron_ = previous_[value];
    delete plane_;
    plane_ = nullptr;
    updateGL();
}

void Scene::mousePressEvent(QMouseEvent* pe)
{
    ptrMousePosition = pe->pos();
}

void Scene::mouseReleaseEvent(QMouseEvent* pe)
{

}

void Scene::mouseMoveEvent(QMouseEvent* pe)
{
    xRot += (180/nSca/5)*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
    zRot += (180/nSca/5)*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
    updateGL();

    ptrMousePosition = pe->pos();
}

void Scene::wheelEvent(QWheelEvent* pe)
{
    if ((pe->delta())>0) scale_plus(); else if ((pe->delta())<0) scale_minus();

    updateGL();
}

void Scene::keyPressEvent(QKeyEvent* pe)
{
    switch (pe->key())
    {
      case Qt::Key_Plus:
         scale_plus();
      break;

      case Qt::Key_Equal:
         scale_plus();
      break;

      case Qt::Key_Minus:
         scale_minus();
      break;

      case Qt::Key_Up:
         rotate_up();
      break;

      case Qt::Key_Down:
         rotate_down();
      break;

      case Qt::Key_Left:
        rotate_left();
      break;

      case Qt::Key_Right:
         rotate_right();
      break;

      case Qt::Key_Z:
         translate_down();
      break;

      case Qt::Key_X:
         translate_up();
      break;

      case Qt::Key_Space:
         defaultScene();
      break;

      case Qt::Key_Escape:
         this->close();
      break;
    }

    updateGL();
}

void Scene::scale_plus()
{
    nSca = nSca*1.5;
}

void Scene::scale_minus()
{
    nSca = nSca/1.5;
}

void Scene::rotate_up()
{
    xRot +=1;
}

void Scene::rotate_down()
{
    xRot -= 1;
}

void Scene::rotate_left()
{
    zRot += 1;
}

void Scene::rotate_right()
{
    zRot -= 1;
}

void Scene::translate_down()
{
    zTra -= 0.05;
}

void Scene::translate_up()
{
    zTra += 0.05;
}

void Scene::defaultScene()
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene::drawAxis()
{
    glLineWidth(3.0f);

    glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
    glBegin(GL_LINES);
      glVertex3f( 1.0f,  0.0f,  0.0f);
      glVertex3f(-1.0f,  0.0f,  0.0f);
    glEnd();

    QColor halfGreen(0, 128, 0, 255);
    qglColor(halfGreen);
    glBegin(GL_LINES);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
    glEnd();
}



void Scene::drawFigure()
{
    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
    glColorPointer(3, GL_FLOAT, 0, ColorArray);
    GLdouble eq[4];
    eq[0] = 0.0d;
    eq[1] = 1.0d;
    eq[2] = 0.0d;
    eq[3] = 0.3d;

    GLdouble ep[4];
    ep[0] = 1.0d;
    ep[1] = 0.0d;
    ep[2] = 0.0d;
    ep[3] = 0.2d;

    glClipPlane(GL_CLIP_PLANE0, eq);
    glEnable(GL_CLIP_PLANE0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 20, GL_UNSIGNED_BYTE, IndexArray);
}

array<double, 4> Scene::getGLColor(const QColor &color)
{
    //array<double, 4> color = {color_.red()/255.0, color_.green()/255.0, color_.blue()/255.0, 0.5f };
    return array<double, 4>({color.red()/255.0, color.green()/255.0, color.blue()/255.0, 0.5f });
}
