#include "rvcurve.h"

RVCurve::RVCurve()
    :RVBody()
{
    minT = 0;
    maxT = 1;
    numSeg = 100;
    lineWidth = 2;
}

void RVCurve::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(lineWidth);
    //glLineStipple() //à regarder comment ça fonctionne ?
    glDisable(GL_CULL_FACE);

    program.bind();
    vao.bind();

    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);
    program.setUniformValue("u_Opacity", opacity);
    program.setUniformValue("u_Color", globalColor);

    glDrawArrays(GL_LINE_STRIP, 0, numSeg+1);

    vao.release();
    program.release();
}

void RVCurve::initializeBuffer()
{
    numVertices = numSeg + 1;

    QVector3D* vertexData = new QVector3D[numVertices];
    double t = minT;
    double deltaT = (maxT - minT)/numSeg;
    for (int i = 0; i <= numSeg; i++, t += deltaT) {
        vertexData[i] = pos(t);
    }

    //remplissage du Vertex Buffer Object
    vbo.bind();
    vbo.allocate(vertexData, numVertices * int(sizeof(QVector3D)));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo.release();
}

void RVCurve::initializeVAO()
{
    //Initialisation du VAO
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition du seul attribut position (la couleur est uniforme avec le VS_simpler)
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    //Libération
    vao.release();
    program.release();
}

float RVCurve::getLineWidth() const
{
    return lineWidth;
}

void RVCurve::setLineWidth(float lineWidth)
{
    this->lineWidth = lineWidth;
}

int RVCurve::getNumSeg() const
{
    return numSeg;
}

void RVCurve::setNumSeg(int numSeg)
{
    this->numSeg = numSeg;
}


double RVCurve::getMinT() const
{
    return minT;
}

void RVCurve::setMinT(double minT)
{
    this->minT = minT;
}

double RVCurve::getMaxT() const
{
    return maxT;
}

void RVCurve::setMaxT(double maxT)
{
    this->maxT = maxT;
}

