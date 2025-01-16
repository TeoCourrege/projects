#ifndef RVTORUS_H
#define RVTORUS_H

/*!
  \file rvtorus.h
  \brief Déclaration de la classe RVTorus
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise la classe RVSurface avec une représentation paramètrique du tore
*/

#include "rvsurface.h"

class RVTorus : public RVSurface
{
public:
    RVTorus(double smallRadius = 1.0, double bigRadius = 4.0);

    double getBigRadius() const;
    void setBigRadius(double R);

    double getSmallRadius() const;
    void setSmallRadius(double R);


protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double bigRadius;
    double smallRadius;
};

#endif // RVTORUS_H
