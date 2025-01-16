#include "rvpyramid.h"

RVPyramid::RVPyramid()
    :RVBody()
{
    //Je définis ici les shaders à utiliser dans RVPyramid
    VSFileName = ":/shaders/VS_simple.vsh";
    FSFileName = ":/shaders/FS_simple.fsh";
}

void RVPyramid::draw()
{
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program.bind();
    vao.bind();

    //Définition de la variable uniforme
    QMatrix4x4 matrix;
    matrix = camera->projectionMatrix() * camera->viewMatrix() * this->modelMatrix();
    program.setUniformValue("u_ModelViewProjectionMatrix", matrix);

    //Commande de rendu (indexé)
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

    vao.release();
    program.release();
}

void RVPyramid::initializeBuffer()
{
    //Définition de 4 points
    QVector3D A(0, 0, 1);
    QVector3D B(0.85f, 0, -0.5f);
    QVector3D C(-0.85f, 0, -0.5f);
    QVector3D D(0, 1, 0);

    //Définition de 4 couleurs
    QVector3D rouge(1, 0, 0);
    QVector3D vert(0, 1, 0);
    QVector3D bleu(0, 0, 1);
    QVector3D blanc(1, 1, 1);

    //Initialisation du Vertex Buffer Object
    //On prépare le tableau des données
    QVector3D vertexData[] = {
        A, B, C, D,
        rouge, vert, bleu, blanc
    };
    //Lien du VBO avec le contexte de rendu OpenG
    vbo.bind();
    //Allocation des données dans le VBO
    vbo.allocate(vertexData, sizeof (vertexData));
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    vbo.release();

    //Initialisation de l'Index Buffer Object
    uint indexData[] = {
        0, 1, 3,
        0, 3, 2,
        0, 2, 1,
        1, 2, 3
    };

    //Lien du IBO avec le contexte de rendu OpenG
    ibo.bind();
    //Allocation des données dans le IBO
    ibo.allocate(indexData, sizeof (indexData));
    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    //Libération du VBO
    ibo.release();


    numVertices = 4;
    numTriangles = 4;
    numIndices = 12;
}

void RVPyramid::initializeVAO()
{
    //Initialisation du Vertex Array Object
    program.bind();
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition des attributs
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3);
    program.enableAttributeArray("rv_Position");

    program.setAttributeBuffer("rv_Color", GL_FLOAT, sizeof(QVector3D)*numVertices, 3);
    program.enableAttributeArray("rv_Color");

    //Libération
    vao.release();
    program.release();
}
