#ifndef RVSPHERE_H
#define RVSPHERE_H

/*!
  \file rvsphere.h
  \brief Déclaration de la classe RVSphere.
  \author  Leo Donati
  \date    01/02/2022
  \version 2

  Cours de Réalité Virtuelle
  Polytech'Nice Sophia

  Utilise RVsurface avec l'équation paramétrée utilisant les coordonnées sphériques
*/

#include "rvsurface.h"

class RVSphere : public RVSurface
{
public:
    RVSphere(double radius = 1.0);

    double getRadius() const;
    void setRadius(double newRadius);


protected:
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;

    double radius;
};

#endif // RVSPHERE_H
