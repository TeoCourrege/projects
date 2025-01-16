#ifndef RVBODY_H
#define RVBODY_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QColor>

#include "rvcamera.h"
#include "rvlight.h"

///
/// \brief The RVBody class
/// @version 5
/// @author Leo Donati
/// Use texture and lights
class RVBody : public QOpenGLFunctions
{
public:
    RVBody();
    virtual ~RVBody();

    virtual void draw() = 0;
    virtual QMatrix4x4 modelMatrix();

    void initialize();
    void initializeShader();
    virtual void initializeBuffer() = 0;
    virtual void initializeVAO();

    virtual void update(float time, bool relative = true);

    // pour bouger l'objet
    virtual void rotate(float angle, QVector3D axis);
    virtual void translate(QVector3D position);
    virtual void setOrientation(float yaw, float pitch, float roll);

    // accesseurs et mutateurs .....
    RVCamera *getCamera() const;
    virtual void setCamera(RVCamera *newCamera);

    const QVector3D &getPosition() const;
    virtual void setPosition(const QVector3D &newPosition);

    const QQuaternion &getOrientation() const;
    virtual void setOrientation(const QQuaternion &newOrientation);

    int getNumVertices() const;

    int getNumTriangles() const;

    int getNumIndices() const;

    const QString &getVSFileName() const;
    void setVSFileName(const QString &newVSFileName);

    const QString &getFSFileName() const;
    void setFSFileName(const QString &newFSFileName);

    float getOpacity() const;
    void setOpacity(float newOpacity);

    bool getWireframe() const;
    void setWireframe(bool newWireframe);

    bool getCulling() const;
    void setCulling(bool newCulling);

    float getScale() const;
    virtual void setScale(float newScale);

    const QColor &getGlobalColor() const;
    void setGlobalColor(const QColor &newGlobalColor);

    void setTexture(QString textureFilename, bool hMirror = true, bool vMirror = true);

    RVLight *getLight() const;
    virtual void setLight(RVLight *newLight);
    float getSpecStrength() const;
    void setSpecStrength(float newSpecStrength);

    virtual void setOrigin(QVector3D pos);

protected:
    QString VSFileName;               //! : nom du fichier qui contient le vertex shader
    QString FSFileName;               //! : nom du fichier qui contient le fragment shader
    QOpenGLBuffer vbo;                //! : vertex buffer qui stocke les sommets du maillage
    QOpenGLBuffer ibo;                //! : index buffer (optionnel) qui stocke les index à utiliser pour le rendu
    QOpenGLVertexArrayObject vao;     //! : vertex array object (obligatoire)
    QOpenGLShaderProgram program;     //! : shader program (obligatoire)

    QVector3D position;               //! : position de l'objet dans la scène
    QQuaternion orientation;          //! : attitude de l'objet dans la scène
    QVector3D origin;

    int numVertices;                  //! : nombre de sommets de l'objet (lecture seule)
    int numTriangles;                 //! : nombre de triangles de l'objet (lecture seule)
    int numIndices;                   //! : nombre d'index (0 si on n'utilise pas l'ibo)

    float opacity;                    //! : valeur de l'opacité (1 par défaut)
    bool wireframe;                   //! : pour activer le mode fil-de-fer (false par défaut)
    bool culling;                     //! : pour activer le culling (true par défaut)
    float scale;                      //! : facteur d'échelle (1.0 par défaut)
    QColor globalColor;               //! : couleur globale de l'objet (initialisée à blanc)

    RVCamera *camera;                 //! : pointeur sur la caméra utilisée pour le rendu.
    QOpenGLTexture* texture;          //! : pointeur sur la texture à utiliser

    RVLight* light;                   //! : encapsule position et couleurs de la source lumineuse
    float specStrength;               //! : coefficient de réflection spoéculaire de l'objet

    struct RVVertex {
        QVector3D position;         //! : position du sommet
        QVector2D texCoord;         //! : coordonnées texture
        QVector3D normal;           //! : vecteur normal à la face (unitaire)

        RVVertex(QVector3D pos = QVector3D(), QVector2D tex = QVector2D(), QVector3D normalVector = QVector3D())
        {
            position = pos;
            texCoord = tex;
            normal = normalVector;
        }
    };
};

#endif // RVBODY_H
