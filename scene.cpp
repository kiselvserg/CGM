#include <QtGui>
#include <math.h>

#include "Scene.h"

const static double pi=3.141593, k=pi/180;

GLfloat VertexArray[12][3];
GLfloat ColorArray[12][3];
GLubyte IndexArray[20][3];

Scene::Scene(QWidget* parent) : QGLWidget(parent), plane(nullptr)
{
    xRot=-90; yRot=0; zRot=0; zTra=0; nSca=0.1;
    colors << QColor("#FFFF00") << QColor("#FFCCDE") << QColor("#808080") << QColor("#1853C3");
}

void Scene::initializeGL()
{
    qglClearColor(this->palette().color(QPalette::Window));
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    getVertexArray();
    getColorArray();
    getIndexArray();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    vector<Point> vertexes;
    vertexes.resize(3);
    vertexes[0][0] = 1.0f;
    vertexes[0][1] = 0.0f;
    vertexes[0][2] = 0.0f;
    vertexes[1][0] = 0.0f;
    vertexes[1][1] = 1.0f;
    vertexes[1][2] = 0.0f;
    vertexes[2][0] = 0.0f;
    vertexes[2][1] = 0.0f;
    vertexes[2][2] = 1.0f;

    vertexes[1][0] = 1.0f;
    vertexes[1][1] = 0.0f;

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
    polygons.push_back(polygon1);
    polygons.push_back(polygon2);
    polygons.push_back(polygon3);
    polygons.push_back(polygon4);
    polygons.push_back(polygon5);
    polygons.push_back(polygon6);
    //Создаём полигедрон из полигонов
    polyhedron = new Polyhedron(polygons);
    previous.append(*polyhedron);
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

    if(plane != nullptr)
    {
        polyhedron->polyhedronGroupSection(*plane, true, polyhedron, 0, getGLColor(color));
    }
    polyhedron->draw();
}

void Scene::clipping(array<int, 3> arr, double eq, QColor clr)
{
    if(plane != nullptr) delete plane;
    plane = new Plane(arr[0], arr[1], arr[2], eq);
    color = clr;
    qDebug() << "coef:" << arr[0] << arr[1] << arr[2] << eq;
    qDebug() << "color" << color.toRgb();
    this->updateGL();
    previous.append(*polyhedron);
    emit clipChanged(previous.size()-1);
}

void Scene::clearAll()
{
    polyhedron->clear();
    polyhedron->setPolygons(polygons);
    previous.clear();
    previous.append(*polyhedron);
    emit clipChanged(0);
    delete plane;
    plane = nullptr;
    updateGL();
}

void Scene::undo()
{
    *polyhedron = previous[previous.size()-2];
    previous.remove(previous.size() - 1);
    emit clipChanged(previous.size()-1);
    delete plane;
    plane = nullptr;
    updateGL();
}

void Scene::showScene(int value)
{
    qDebug() << "value set:" << value;
    if(value >= previous.size()) return;
    *polyhedron = previous[value];
    delete plane;
    plane = nullptr;
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

void Scene::getVertexArray()
{
    GLfloat R=0.75;

    GLfloat a=4*R/sqrt(10+2*sqrt(5));
    GLfloat alpha=acos((1-a*a/2/R/R));

    VertexArray[0][0]=0;
    VertexArray[0][1]=0;
    VertexArray[0][2]=R;

    VertexArray[1][0]=R*sin(alpha)*sin(0);
    VertexArray[1][1]=R*sin(alpha)*cos(0);
    VertexArray[1][2]=R*cos(alpha);

    VertexArray[2][0]=R*sin(alpha)*sin(72*k);
    VertexArray[2][1]=R*sin(alpha)*cos(72*k);
    VertexArray[2][2]=R*cos(alpha);

    VertexArray[3][0]=R*sin(alpha)*sin(2*72*k);
    VertexArray[3][1]=R*sin(alpha)*cos(2*72*k);
    VertexArray[3][2]=R*cos(alpha);

    VertexArray[4][0]=R*sin(alpha)*sin(3*72*k);
    VertexArray[4][1]=R*sin(alpha)*cos(3*72*k);
    VertexArray[4][2]=R*cos(alpha);

    VertexArray[5][0]=R*sin(alpha)*sin(4*72*k);
    VertexArray[5][1]=R*sin(alpha)*cos(4*72*k);
    VertexArray[5][2]=R*cos(alpha);

    VertexArray[6][0]=R*sin(pi-alpha)*sin(-36*k);
    VertexArray[6][1]=R*sin(pi-alpha)*cos(-36*k);
    VertexArray[6][2]=R*cos(pi-alpha);

    VertexArray[7][0]=R*sin(pi-alpha)*sin(36*k);
    VertexArray[7][1]=R*sin(pi-alpha)*cos(36*k);
    VertexArray[7][2]=R*cos(pi-alpha);

    VertexArray[8][0]=R*sin(pi-alpha)*sin((36+72)*k);
    VertexArray[8][1]=R*sin(pi-alpha)*cos((36+72)*k);
    VertexArray[8][2]=R*cos(pi-alpha);

    VertexArray[9][0]=R*sin(pi-alpha)*sin((36+2*72)*k);
    VertexArray[9][1]=R*sin(pi-alpha)*cos((36+2*72)*k);
    VertexArray[9][2]=R*cos(pi-alpha);

    VertexArray[10][0]=R*sin(pi-alpha)*sin((36+3*72)*k);
    VertexArray[10][1]=R*sin(pi-alpha)*cos((36+3*72)*k);
    VertexArray[10][2]=R*cos(pi-alpha);

    VertexArray[11][0]=0;
    VertexArray[11][1]=0;
    VertexArray[11][2]=-R;
}

void Scene::getColorArray()
{
    for (int i=0; i<12; i++)
    {
      ColorArray[i][0]=0.1f*(qrand()%11);
      ColorArray[i][1]=0.1f*(qrand()%11);
      ColorArray[i][2]=0.1f*(qrand()%11);
    }
}

void Scene::getIndexArray()
{
    IndexArray[0][0]=0;
    IndexArray[0][1]=2;
    IndexArray[0][2]=1;

    IndexArray[1][0]=0;
    IndexArray[1][1]=3;
    IndexArray[1][2]=2;

    IndexArray[2][0]=0;
    IndexArray[2][1]=4;
    IndexArray[2][2]=3;

    IndexArray[3][0]=0;
    IndexArray[3][1]=5;
    IndexArray[3][2]=4;

    IndexArray[4][0]=0;
    IndexArray[4][1]=1;
    IndexArray[4][2]=5;

    IndexArray[5][0]=6;
    IndexArray[5][1]=1;
    IndexArray[5][2]=7;

    IndexArray[6][0]=7;
    IndexArray[6][1]=1;
    IndexArray[6][2]=2;

    IndexArray[7][0]=7;
    IndexArray[7][1]=2;
    IndexArray[7][2]=8;

    IndexArray[8][0]=8;
    IndexArray[8][1]=2;
    IndexArray[8][2]=3;

    IndexArray[9][0]=8;
    IndexArray[9][1]=3;
    IndexArray[9][2]=9;

    IndexArray[10][0]=9;
    IndexArray[10][1]=3;
    IndexArray[10][2]=4;

    IndexArray[11][0]=9;
    IndexArray[11][1]=4;
    IndexArray[11][2]=10;

    IndexArray[12][0]=10;
    IndexArray[12][1]=4;
    IndexArray[12][2]=5;

    IndexArray[13][0]=10;
    IndexArray[13][1]=5;
    IndexArray[13][2]=6;

    IndexArray[14][0]=6;
    IndexArray[14][1]=5;
    IndexArray[14][2]=1;

    IndexArray[15][0]=7;
    IndexArray[15][1]=11;
    IndexArray[15][2]=6;

    IndexArray[16][0]=8;
    IndexArray[16][1]=11;
    IndexArray[16][2]=7;

    IndexArray[17][0]=9;
    IndexArray[17][1]=11;
    IndexArray[17][2]=8;

    IndexArray[18][0]=10;
    IndexArray[18][1]=11;
    IndexArray[18][2]=9;

    IndexArray[19][0]=6;
    IndexArray[19][1]=11;
    IndexArray[19][2]=10;
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

array<double, 4> Scene::getGLColor(const QColor &color_)
{
    //array<double, 4> color = {color_.red()/255.0, color_.green()/255.0, color_.blue()/255.0, 0.5f };
    return array<double, 4>({color_.red()/255.0, color_.green()/255.0, color_.blue()/255.0, 0.5f });
}
