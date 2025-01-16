#ifndef RVSTEREOCAMERA_H
#define RVSTEREOCAMERA_H

#define RV_CAMERA_MONO 0
#define RV_CAMERA_LEFT 1
#define RV_CAMERA_RIGHT 2

#include "rvcamera.h"

class RVStereoCamera : public RVCamera
{
public:
    RVStereoCamera();

    float getEyeDistance() const;
    void setEyeDistance(float newEyeDistance);

    float getFocalDistance() const;
    void setFocalDistance(float newFocalDistance);

    QMatrix4x4 viewMatrix();
    QMatrix4x4 projectionMatrix();

    int getCameraType() const;
    void setCameraType(int newCameraType);

protected :
    QMatrix4x4 leftViewMatrix();
    QMatrix4x4 leftProjectionMatrix();
    QMatrix4x4 rightViewMatrix();
    QMatrix4x4 rightProjectionMatrix();

private:
    float eyeDistance;
    float focalDistance;
    int cameraType;
};
#endif // RVSTEREOCAMERA_H
