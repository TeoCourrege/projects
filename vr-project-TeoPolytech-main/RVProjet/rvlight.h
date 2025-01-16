#ifndef RVLIGHT_H
#define RVLIGHT_H
#include <QVector3D>
#include <QColor>



class RVLight
{
public:
    RVLight();
    QColor getAmbient() const;
    void setAmbient(const QColor &newAmbient);

    QColor getDiffuse() const;
    void setDiffuse(const QColor &newDiffuse);

    QColor getSpecular() const;
    void setSpecular(const QColor &newSpecular);

    QVector3D getPositionLight() const;
    void setPositionLight(const QVector3D &newPosition);



private:
    QVector3D position;
    QColor ambient;
    QColor diffuse;
    QColor specular;
};

#endif // RVLIGHT_H
