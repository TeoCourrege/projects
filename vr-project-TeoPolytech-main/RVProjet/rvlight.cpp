#include "rvlight.h"

RVLight::RVLight()
{
    position = QVector3D(10, 0, 10);
    ambient = QColor(100, 100, 100);
    diffuse = QColor(255, 255, 255);
    specular = QColor(255, 255, 255);
}

QColor RVLight::getAmbient() const
{
    return ambient;
}

void RVLight::setAmbient(const QColor &newAmbient)
{
    ambient = newAmbient;
}

QColor RVLight::getDiffuse() const
{
    return diffuse;
}

void RVLight::setDiffuse(const QColor &newDiffuse)
{
    diffuse = newDiffuse;
}

QColor RVLight::getSpecular() const
{
    return specular;
}

void RVLight::setSpecular(const QColor &newSpecular)
{
    specular = newSpecular;
}

QVector3D RVLight::getPositionLight() const
{
    return position;
}

void RVLight::setPositionLight(const QVector3D &newPosition)
{
    position = newPosition;
}

