#include "rvbody.h"

RVBody::RVBody()
    :QOpenGLFunctions(),
    vao(), program(),
    position(), orientation(),
    texture()
{
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    vbo.create();
    ibo.create();
    vao.create();
    program.create();

    numVertices = 0;
    numTriangles = 0;
    numIndices = 0;

    opacity = 1.0f;
    wireframe = false;
    culling = true;
    scale = 1.0f;
    globalColor = QColor(255, 255, 255);

    VSFileName = ":/shaders/VS_simple_texture.vsh";
    FSFileName = ":/shaders/FS_simple_texture.fsh";

    specStrength = 10;
    origin = QVector3D(0,0,0);
}

RVBody::~RVBody()
{
    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    vao.destroy();
    ibo.destroy();
    vbo.destroy();
    if (texture)
        delete texture;
}

void RVBody::initialize()
{
    initializeShader();
    initializeBuffer();		//à écrire dans la classe fille
    initializeVAO();
}

void RVBody::initializeShader()
{
    initializeOpenGLFunctions();

    if (program.hasOpenGLShaderPrograms())
        program.removeAllShaders();
    bool resultat;

    program.bind();
    //Vertex Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Vertex, VSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Vertex shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Fragment Shader
    resultat = program.addShaderFromSourceFile(QOpenGLShader::Fragment, FSFileName);
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Fragment shader");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Link
    resultat = program.link();
    if (!resultat)     {
        QMessageBox msg;
        msg.setWindowTitle("Link du shader program");
        msg.setText(program.log());
        msg.exec();
        exit(EXIT_FAILURE);
    }

    //Libération
    program.release();
}

void RVBody::initializeVAO()
{
    //Initialisation du VAO
    vao.bind();
    vbo.bind();
    ibo.bind();

    //Définition de l'attribut position
    program.setAttributeBuffer("rv_Position", GL_FLOAT, 0, 3, sizeof(RVVertex));
    program.enableAttributeArray("rv_Position");

    //Définition de l'attribut de coordonnée texture
    program.setAttributeBuffer("rv_TexCoord", GL_FLOAT, sizeof(RVVertex::position), 2, sizeof(RVVertex));
    program.enableAttributeArray("rv_TexCoord");

    //Définition de l'attribut de vecteur normal
    program.setAttributeBuffer("rv_Normal", GL_FLOAT, sizeof(RVVertex::position)+sizeof (RVVertex::texCoord), 3, sizeof(RVVertex));
    program.enableAttributeArray("rv_Normal");

    //Libération
    vao.release();
    program.release();
}

void RVBody::update(float time, bool relative)
{}

void RVBody::rotate(float angle, QVector3D axis)
{
    orientation =  QQuaternion::fromAxisAndAngle(axis, angle) * orientation ;
}

void RVBody::translate(QVector3D position)
{
    this->position += position;
}

void RVBody::setOrientation(float yaw, float pitch, float roll)
{
    orientation = QQuaternion::fromEulerAngles(pitch, yaw, roll);
}

QMatrix4x4 RVBody::modelMatrix()
{
    QMatrix4x4 model;
    model.translate(position);
    model.rotate(orientation);
    model.scale(scale);
    model.translate(-origin);
    return model;
}

RVCamera *RVBody::getCamera() const
{
    return camera;
}

void RVBody::setCamera(RVCamera *newCamera)
{
    camera = newCamera;
}

const QVector3D &RVBody::getPosition() const
{
    return position;
}

void RVBody::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}

const QQuaternion &RVBody::getOrientation() const
{
    return orientation;
}

void RVBody::setOrientation(const QQuaternion &newOrientation)
{
    orientation = newOrientation;
}

int RVBody::getNumVertices() const
{
    return numVertices;
}

int RVBody::getNumTriangles() const
{
    return numTriangles;
}

int RVBody::getNumIndices() const
{
    return numIndices;
}

const QString &RVBody::getVSFileName() const
{
    return VSFileName;
}

void RVBody::setVSFileName(const QString &newVSFileName)
{
    VSFileName = newVSFileName;
}

const QString &RVBody::getFSFileName() const
{
    return FSFileName;
}

void RVBody::setFSFileName(const QString &newFSFileName)
{
    FSFileName = newFSFileName;
}

float RVBody::getOpacity() const
{
    return opacity;
}

void RVBody::setOpacity(float newOpacity)
{
    opacity = newOpacity;
}

bool RVBody::getWireframe() const
{
    return wireframe;
}

void RVBody::setWireframe(bool newWireframe)
{
    wireframe = newWireframe;
}

bool RVBody::getCulling() const
{
    return culling;
}

void RVBody::setCulling(bool newCulling)
{
    culling = newCulling;
}

float RVBody::getScale() const
{
    return scale;
}

void RVBody::setScale(float newScale)
{
    scale = newScale;
}

const QColor &RVBody::getGlobalColor() const
{
    return globalColor;
}

void RVBody::setGlobalColor(const QColor &newGlobalColor)
{
    globalColor = newGlobalColor;
}

void RVBody::setTexture(QString textureFilename, bool hMirror, bool vMirror)
{
    if (texture)
        delete texture;
    texture = new QOpenGLTexture(QImage(textureFilename).mirrored(hMirror, vMirror));
}

RVLight *RVBody::getLight() const
{
    return light;
}

void RVBody::setLight(RVLight *newLight)
{
    light = newLight;
}

float RVBody::getSpecStrength() const
{
    return specStrength;
}

void RVBody::setSpecStrength(float newSpecStrength)
{
    specStrength = newSpecStrength;
}

void RVBody::setOrigin(QVector3D pos)
{
    origin = pos;
}
