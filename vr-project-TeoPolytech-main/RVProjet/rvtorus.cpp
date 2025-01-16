/*!
  \file rvtorus.cpp
  \brief Définition de la classe RVTorus.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia
*/

#include "rvtorus.h"

RVTorus::RVTorus(double R1, double R2)
    :RVSurface()
{
    smallRadius = R1;
    bigRadius = R2;
    minS = - M_PI;
    maxS =  M_PI;
    minT = - M_PI;
    maxT =  M_PI;

    FSFileName = ":/shaders/FS_lit_checker.fsh";
}



float RVTorus::x(double s, double t)
{
    return float((bigRadius + smallRadius * qCos(t)) * qCos(s));
}

float RVTorus::y(double s, double t)
{
    return float(smallRadius * qSin(t));
}

float RVTorus::z(double s, double t)
{
    return float((bigRadius + smallRadius * qCos(t)) * qSin(s));
}

double RVTorus::getBigRadius() const
{
    return bigRadius;
}

void RVTorus::setBigRadius(double R)
{
    bigRadius = R;
}

double RVTorus::getSmallRadius() const
{
    return smallRadius;
}

void RVTorus::setSmallRadius(double r)
{
    smallRadius = r;
}
