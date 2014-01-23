#include "polygon.h"

sectionFuncReturn::sectionFuncReturn(vector<point> newPoints,
									 vector<ushort> morePoints,
									 vector<ushort> lessPoints,
									 vector<ushort> onPoints)
{
	newPoints_ = newPoints;
	morePoints_ = morePoints;
	lessPoints_ = lessPoints;
	onPoints_ = onPoints;
}

GLfloat& point::operator [](unsigned int index)
{
	return point_[index];
}

MyPolygon::MyPolygon()
{
}

MyPolygon::MyPolygon(vector<point> vertexes)
{
	if(vertexes.size() > 2)
		vertexes_ = vertexes;
}

MyPolygon& MyPolygon::operator = (MyPolygon const & MyPolygon)
{
    vertexes_ = MyPolygon.vertexes_;
	return *this;
}

void MyPolygon::addVertex(const point &vertex)
{
	vertexes_.push_back(vertex);
}

void MyPolygon::drawMyPolygon()
{

    //glMyPolygonMode();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_POLYGON);

	glColor4f(0.20f, 0.20f, 1.00f, 0.5f);
	for(ushort i=0; i<vertexes_.size(); ++i)
		glVertex3f(vertexes_[i][0], vertexes_[i][1], vertexes_[i][2]);
	glEnd();
	/*
    glMyPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_MyPolygon);
	glLineWidth(3);

	glColor4f(0.00f, 0.00f, 0.00f, 1.0f);
	for(ushort i=0; i<this->vertexCount_; ++i)
		glVertex3f(vertexes_[i][0], vertexes_[i][1], vertexes_[i][2]);
	glEnd();

*/
	glLineWidth(3);
	glColor4f(0.00f, 0.00f, 0.00f, 0.0f);
	for(ushort i=0; i<vertexes_.size()-1; ++i)
	{
		glBegin(GL_LINES);
		glVertex3f(vertexes_[i][0], vertexes_[i][1], vertexes_[i][2]);
		glVertex3f(vertexes_[i+1][0], vertexes_[i+1][1], vertexes_[i+1][2]);
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex3f(vertexes_[vertexes_.size()-1][0], vertexes_[vertexes_.size()-1][1], vertexes_[vertexes_.size()-1][2]);
	glVertex3f(vertexes_[0][0], vertexes_[0][1], vertexes_[0][2]);
	glEnd();


}

sectionFuncReturn MyPolygon::MyPolygonSection(vector<GLfloat> plane, MyPolygon*& MyPolygonPointer1, MyPolygon*& MyPolygonPointer2)
{
    if(MyPolygonPointer1 != 0 || MyPolygonPointer2 != 0 || plane.size()<4)
		;//break;  // Ошибку сделать надо

	GLfloat buf = 0, bufPrevious = 0;
	// Если эта штука фолс, тогда меняем местами указатели на полигоны в конце.
    bool relativeProvisionOfMyPolygons = true;

	vector<ushort> more, less, on;
	vector<point> newVertexes;
	vector<ushort> sectionLines;

	// Подставляем точки в уравнение плоскости
	/*
	 * В этом цикле у нас есть два buf: bufPrevious хранит предыдущю по списку (списку вершин полигона)
	 * вершину, подставленную в уравнение плоскости, а buf - текущую. Выясняем когда плоскость пересекает
	 * полигон сравнивая их произведение с нулём.
	 */
	bufPrevious = vertexes_[vertexes_.size()-1][0]*plane[0]
			+ vertexes_[vertexes_.size()-1][1]*plane[1]
			+ vertexes_[vertexes_.size()-1][2]*plane[2]
			+ plane[3];
	for(ushort i=0; i<vertexes_.size(); ++i)
	{
		buf = vertexes_[i][0]*plane[0] + vertexes_[i][1]*plane[1] + vertexes_[i][2]*plane[2]
				+ plane[3];
		if(buf * bufPrevious < 0)
		{
			sectionLines.push_back(i);
			if(buf < 0)
                relativeProvisionOfMyPolygons = false;
		}


		if(buf > 0)
			more.push_back(i);
		else if(buf < 0)
			less.push_back(i);
		else
		{
			on.push_back(i);
			if(bufPrevious > 0)
                relativeProvisionOfMyPolygons = false;
		}
		bufPrevious = buf;
		buf = 0;
	}

	GLfloat alpha = 0, beta = 0;
	point bufPoint;
	for(ushort i=0; i<sectionLines.size(); ++i)
	{

		bufPoint[0] = vertexes_[sectionLines[i]][0] - vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][0];
		bufPoint[1] = vertexes_[sectionLines[i]][1] - vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][1];
		bufPoint[2] = vertexes_[sectionLines[i]][2] - vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][2];
		beta = plane[0]*bufPoint[0] + plane[1]*bufPoint[1] + plane[2]*bufPoint[2];
		if(beta != 0)
		{
			alpha = fabs(-plane[3]/beta);
			bufPoint[0] *= alpha;
			bufPoint[0] += vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][0];
			bufPoint[1] *= alpha;
			bufPoint[1] += vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][1];
			bufPoint[2] *= alpha;
			bufPoint[2] += vertexes_[(sectionLines[i]+vertexes_.size()-1)%vertexes_.size()][2];
			newVertexes.push_back(bufPoint);
		}

		bufPoint[0] = 0;
		bufPoint[1] = 0;
		bufPoint[2] = 0;
	}

	ushort i=0;
	if(newVertexes.size() == 2) // Если сечение образует две новых вершины, то делаем два новых полигона
	{
        MyPolygonPointer1 = new MyPolygon();
        MyPolygonPointer2 = new MyPolygon();
		for(i=0; i<vertexes_.size(); ++i) // Проходим по вершинам
		{
			// Если текущая вершина не является концом рассекаемого ребра,
			// то просто добавляем вершину в новый полигон
			if(i != sectionLines[0])
                MyPolygonPointer1->addVertex(vertexes_[i]);

			// Иначе добавляем "новые" (newVertexes) вершины и продолжаем обход уже с другого рассекаемого
			// ребра.
			else
			{
                MyPolygonPointer1->addVertex(newVertexes[0]);
                MyPolygonPointer1->addVertex(newVertexes[1]);
				for(ushort j=sectionLines[1]; j<vertexes_.size(); ++j)
                    MyPolygonPointer1->addVertex(vertexes_[j]);
				break;
			}
		}
		// Дорисовываем второй полигон по схоже схеме
        MyPolygonPointer2->addVertex(newVertexes[0]);
		for(; i<sectionLines[1]; ++i)
            MyPolygonPointer2->addVertex(vertexes_[i]);
        MyPolygonPointer2->addVertex(newVertexes[1]);
	}

	else if(on.size() == 2 && (on[1]-on[0] != (1 || vertexes_.size()-1))) // Если у нас сечение проходит через две существующие вершины
	{

        MyPolygonPointer1 = new MyPolygon();
        MyPolygonPointer2 = new MyPolygon();
		for(i=0; i<vertexes_.size(); ++i) // Проходим по вершинам
		{
			// Если текущая вершина не лежит на секущей плоскости,
			// то просто добавляем вершину в новый полигон
			if(i != on[0])
                MyPolygonPointer1->addVertex(vertexes_[i]);

			// Иначе добавляем "лежащие" вершины и продолжаем обход уже с другой стороны
			else
			{
                MyPolygonPointer1->addVertex(vertexes_[on[0]]);
                MyPolygonPointer1->addVertex(vertexes_[on[1]]);
				for(ushort j=on[1]+1; j<vertexes_.size(); ++j)
                    MyPolygonPointer1->addVertex(vertexes_[j]);
				break;
			}
		}
		// Дорисовываем второй полигон по схоже схеме
        MyPolygonPointer2->addVertex(vertexes_[on[0]]);
		for(; i<on[1]; ++i)
            MyPolygonPointer2->addVertex(vertexes_[i]);
        MyPolygonPointer2->addVertex(vertexes_[on[1]]);

	}
	else if(newVertexes.size() == 1 && on.size() == 1) // Тут смесь первого и второго случаев
	{
        MyPolygonPointer1 = new MyPolygon();
        MyPolygonPointer2 = new MyPolygon();
		for(i=0; i<vertexes_.size(); ++i) // Проходим по вершинам
		{
			if(i != (on[0] && sectionLines[0]))
                MyPolygonPointer1->addVertex(vertexes_[i]);
			else if(i == on[0])
			{
                MyPolygonPointer1->addVertex(vertexes_[on[0]]);
                MyPolygonPointer1->addVertex(newVertexes[0]);
				for(ushort j=sectionLines[0]; j<vertexes_.size(); ++j)
                    MyPolygonPointer1->addVertex(vertexes_[j]);
                MyPolygonPointer2->addVertex(vertexes_[on[0]]);
				for(; i<sectionLines[0]; ++i)
                    MyPolygonPointer2->addVertex(vertexes_[i]);
                MyPolygonPointer2->addVertex(newVertexes[0]);
				break;
			}
			else
			{
                MyPolygonPointer1->addVertex(newVertexes[0]);
                MyPolygonPointer1->addVertex(vertexes_[on[0]]);
				for(ushort j=on[0]+1; j<vertexes_.size(); ++j)
                    MyPolygonPointer1->addVertex(vertexes_[j]);
                MyPolygonPointer2->addVertex(newVertexes[0]);
				for(; i<on[0]; ++i)
                    MyPolygonPointer2->addVertex(vertexes_[i]);
                MyPolygonPointer2->addVertex(vertexes_[on[0]]);
				break;
			}
		}

	}
	else
	{
        MyPolygonPointer1 = 0;
        MyPolygonPointer2 = 0;
	}

    if(relativeProvisionOfMyPolygons == false && MyPolygonPointer1 != 0)
	{
        MyPolygon* tempMyPolygonPointer = MyPolygonPointer2;
        MyPolygonPointer2 = MyPolygonPointer1;
        MyPolygonPointer1 = tempMyPolygonPointer;
	}
	return sectionFuncReturn(newVertexes, more, less, on);
}
