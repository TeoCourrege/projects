/*!
  \file rvsphere.cpp
  \brief Définition de la classe RVSphere.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvsphere.h"

RVSphere::RVSphere(double r)
    :RVSurface()
{
    radius = r;
    minS = 0;
    maxS = 2*M_PI;
    minT = - M_PI_2;
    maxT = + M_PI_2;
}



float RVSphere::x(double s, double t)
{
    return float(radius*qCos(t)*qCos(s)) ;
}

float RVSphere::y(double s, double t)
{
    return float(radius*qSin(t));
}

float RVSphere::z(double s, double t)
{
    return float(radius* qCos(t)*qSin(s));
}

double RVSphere::getRadius() const
{
    return radius;
}

void RVSphere::setRadius(double newRadius)
{
    radius = newRadius;
}

