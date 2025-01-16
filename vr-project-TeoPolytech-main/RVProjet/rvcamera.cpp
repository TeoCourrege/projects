#include "rvcamera.h"

#include <iostream>
using namespace std;

RVCamera::RVCamera()
{
    position = QVector3D(0, 0, 0);
    target = QVector3D(0, 0, -1);
    up = QVector3D(0, 1, 0);

    aspect = 1.33f;
    zMax = 100.0f;
    zMin  = 0.1f;
    fov = 90.0f;

    orthogonal = false;
}

RVCamera::~RVCamera()
{
}

QMatrix4x4 RVCamera::viewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(position, target, up);
    return view;
}

QMatrix4x4 RVCamera::projectionMatrix()
{
    QMatrix4x4 proj;
    if (!orthogonal)
        proj.perspective(fov, aspect, zMin, zMax);
    else
    {
        float bottom = -fov/2;
        float top = fov/2;
        float left = bottom * aspect;
        float right = top * aspect;
        proj.ortho(left, right, bottom, top, 0.0f, zMax);
    }
    return proj;
}

QVector3D RVCamera::getPosition() const
{
    return position;
}

void RVCamera::setPosition(const QVector3D &position)
{
    this->position = position;
}

QVector3D RVCamera::getTarget() const
{
    return target;
}

void RVCamera::setTarget(const QVector3D &target)
{
    this->target = target;
}

QVector3D RVCamera::getUp() const
{
    return up;
}

void RVCamera::setUp(const QVector3D &up)
{
    this->up = up;
}

float RVCamera::getFov() const
{
    return fov;
}

void RVCamera::setFov(float fov)
{
    this->fov = fov;
}

float RVCamera::getAspect() const
{
    return aspect;
}

void RVCamera::setAspect(float aspect)
{
    this->aspect = aspect;
}

float RVCamera::getZMin() const
{
    return zMin;
}

void RVCamera::setZMin(float zMin)
{
    this->zMin = zMin;
}

float RVCamera::getZMax() const
{
    return zMax;
}

void RVCamera::setZMax(float zMax)
{
    this->zMax = zMax;
}

bool RVCamera::isOrthogonal() const
{
    return orthogonal;
}

void RVCamera::setOrthogonal(bool newOrthogonal)
{
    orthogonal = newOrthogonal;
}

