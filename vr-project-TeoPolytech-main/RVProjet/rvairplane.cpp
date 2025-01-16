#include "rvairplane.h"

RVAirplane::RVAirplane():RVModel("../RVProjet/Model/GeeBee2.x")
{
    velocity = 1;
    acceleration = 1;
}

float RVAirplane::getVelocity() const
{
    return velocity;
}

void RVAirplane::setVelocity(float newVelocity)
{
    velocity = newVelocity;
}

float RVAirplane::getAcceleration() const
{
    return acceleration;
}

void RVAirplane::setAcceleration(float newAcceleration)
{
    acceleration = newAcceleration;
}

void RVAirplane::update(float time, bool relative)
{
    if (relative){
        // Corps de l'avion
        float v = velocity * time * 0.001;
        float s = acceleration * pow(time*0.001,2) / 2;
        this->translate((v+s)*orientation.rotatedVector(QVector3D(0,0,-1)));

        // Hélice
        QVector3D dir_helix = meshes[2]->getOrientation().rotatedVector(QVector3D(0,0,-1));
        meshes[2]->rotate(v*80, dir_helix);

        if (velocity <= 30) {
            this->setVelocity(velocity + acceleration * time * 0.001);
        }
    }
    else{
        // Corps de l'avion
        float v = velocity * 0.1;
        float s = acceleration * pow(0.1,2) / 2;
        this->translate((v+s)*orientation.rotatedVector(QVector3D(0,0,-1)));

        // Hélice
        QVector3D dir_helix = meshes[2]->getOrientation().rotatedVector(QVector3D(0,0,-1));
        meshes[2]->rotate(v*80, dir_helix);

        if (velocity <= 30) {
            this->setVelocity(velocity + acceleration * 0.1);
        }
    }
    if (orientation.z() != 0 && orientation.y() < 180 && orientation.z() > -180) {
        rotate(orientation.toEulerAngles().z()/45, QVector3D(0,1,0));
    }
}
