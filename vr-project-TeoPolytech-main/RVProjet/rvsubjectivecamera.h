#ifndef RVSUBJECTIVECAMERA_H
#define RVSUBJECTIVECAMERA_H

#include "rvstereocamera.h"

class RVSubjectiveCamera : public RVStereoCamera
{
public:
    RVSubjectiveCamera();

    float getYaw() const;
    void setYaw(float newYaw);

    float getPitch() const;
    void setPitch(float newPitch);

    void move(float d);
    void lateral(float d);
    void crouch(float yMin);
    void getUp(float yMax);
    bool jump(float yMin, float yMax, bool up);

    void turn(float angle);
    void tilt(float angle);

    void setPosition(const QVector3D &position) override;

private :
    float yaw;
    float pitch;

    void updateTarget();
};

#endif // RVSUBJECTIVECAMERA_H
