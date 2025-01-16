#include "rvsubjectivecamera.h"

RVSubjectiveCamera::RVSubjectiveCamera() : RVStereoCamera()
{
    yaw = 0.0f;
    pitch = 0.0f;
}

float RVSubjectiveCamera::getYaw() const
{
    return yaw;
}

void RVSubjectiveCamera::setYaw(float newYaw)
{
    yaw = newYaw;
    this->updateTarget();
}

float RVSubjectiveCamera::getPitch() const
{
    return pitch;
}

void RVSubjectiveCamera::setPitch(float newPitch)
{
    pitch = newPitch;
    this->updateTarget();
}

void RVSubjectiveCamera::move(float d)
{
    float y = position.y();
    position += d*(target - position);
    position.setY(y);
    updateTarget();
}

void RVSubjectiveCamera::lateral(float d)
{
    float y = position.y();
    position += d * QQuaternion::fromEulerAngles(0,-90,0).rotatedVector(target-position);
    position.setY(y);
    updateTarget();
}

void RVSubjectiveCamera::crouch(float yMin)
{
    if (yMin < position.y()) {
        position.setY(position.y() - 1);
    }
    updateTarget();
}

void RVSubjectiveCamera::getUp(float yMax)
{
    if (yMax > position.y()) {
        position.setY(position.y() + 1);
    }
    updateTarget();
}

bool RVSubjectiveCamera::jump(float yMin, float yMax, bool up)
{
    if(up){
        if (yMax > position.y()) {
            position.setY(position.y() + 1);
            //move(0.5);
        }
    }
    else{
        if (yMin < position.y()) {
            position.setY(position.y() - 1);
            //move(0.5);
        }
    }
    updateTarget();
    // Si on arrive à la fin de l'acsension
    if (position.y()==yMax and up==true){
        return false;
    }
    // Si on est dans la descente
    if (up == false){
        return false;
    }
    // Si on est dans l'acension
    return true;
}


void RVSubjectiveCamera::turn(float angle)
{
    setYaw(yaw+angle);
}

void RVSubjectiveCamera::tilt(float angle)
{
    setPitch(pitch+angle);
}

void RVSubjectiveCamera::setPosition(const QVector3D &position)
{
    this->position = position;
    this->updateTarget();
}

void RVSubjectiveCamera::updateTarget()
{
    float x = qCos(pitch) * qCos(yaw);
    float y = qSin(pitch);
    float z = - qCos(pitch) * qSin(yaw);
    this->setTarget(position + QVector3D(x,y,z));
}
