#ifndef RVCAMERA_H
#define RVCAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class RVCamera
{
public:
    RVCamera();
    virtual ~RVCamera();

    virtual QMatrix4x4 viewMatrix();
    virtual QMatrix4x4 projectionMatrix();

    //Accesseurs
    QVector3D getPosition() const;
    virtual void setPosition(const QVector3D &position);
    QVector3D getTarget() const;
    virtual void setTarget(const QVector3D &target);
    QVector3D getUp() const;
    void setUp(const QVector3D &up);
    float getFov() const;
    void setFov(float fov);
    float getAspect() const;
    void setAspect(float aspect);
    float getZMin() const;
    void setZMin(float zMin);
    float getZMax() const;
    void setZMax(float zMax);

    bool getIsOrthogonal() const;
    void setIsOrthogonal(bool newIsOrthogonal);

    bool isOrthogonal() const;
    void setOrthogonal(bool newOrthogonal);

protected:
    QVector3D position;
    QVector3D target;
    QVector3D up;
    float fov;
    float aspect;
    float zMin;
    float zMax;
    bool orthogonal;
};

#endif // RVCAMERA_H
