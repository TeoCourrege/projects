#include "rvstereocamera.h"

#include <iostream>
using namespace std;

RVStereoCamera::RVStereoCamera(){
    eyeDistance = 1;
    focalDistance = 10;
    cameraType = 1;
}


float RVStereoCamera::getEyeDistance() const
{
    return eyeDistance;
}

void RVStereoCamera::setEyeDistance(float newEyeDistance)
{
    eyeDistance = newEyeDistance;
}

float RVStereoCamera::getFocalDistance() const
{
    return focalDistance;
}

void RVStereoCamera::setFocalDistance(float newFocalDistance)
{
    focalDistance = newFocalDistance;
}


QMatrix4x4 RVStereoCamera::viewMatrix()
{
    if(cameraType==RV_CAMERA_LEFT){
        return RVStereoCamera::leftViewMatrix();
    }
    if(cameraType==RV_CAMERA_RIGHT){
        return RVStereoCamera::rightViewMatrix();
    }
    else{
        return RVCamera::viewMatrix();
    }
}

QMatrix4x4 RVStereoCamera::projectionMatrix()
{
    if(cameraType==RV_CAMERA_LEFT){
        return RVStereoCamera::leftProjectionMatrix();
    }
    if(cameraType==RV_CAMERA_RIGHT){
        return RVStereoCamera::rightProjectionMatrix();
    }
    else{

        return RVCamera::projectionMatrix();
    }
}

QMatrix4x4 RVStereoCamera::leftViewMatrix()
{
    QVector3D v= (QVector3D::crossProduct(target-position,up)).normalized();
    QVector3D posOG=position-(eyeDistance/2)*v;
    QVector3D cibleOG=target-(eyeDistance/2)*v;
    QMatrix4x4 view;
    view.lookAt(posOG,cibleOG,up);
    return view;
}

QMatrix4x4 RVStereoCamera::rightViewMatrix()
{
    QVector3D v= (QVector3D::crossProduct(target-position,up)).normalized();
    QVector3D posOG=position+(eyeDistance/2)*v;
    QVector3D cibleOG=target+(eyeDistance/2)*v;
    QMatrix4x4 view;
    view.lookAt(posOG,cibleOG,up);
    return view;
}

QMatrix4x4 RVStereoCamera::leftProjectionMatrix()
{
    QMatrix4x4 proj;
    float top= zMin*qTan( qDegreesToRadians(fov)/float(2));
    float bottom=-top;
    float a= focalDistance*(top/zMin)*aspect;
    float b=a-eyeDistance/float(2);
    float c=a+eyeDistance/float(2);
    float left=-b*zMin/focalDistance;
    float right=c*zMin/focalDistance;
    proj.frustum(left,right,bottom,top,zMin,zMax);
    return proj;
}
QMatrix4x4 RVStereoCamera::rightProjectionMatrix()
{
    QMatrix4x4 proj;
    float top=zMin*qTan( qDegreesToRadians(fov)/float(2));
    float bot=-top;
    float a= focalDistance*(top/zMin)*aspect;
    float b=a+eyeDistance/float(2);
    float c=a-eyeDistance/float(2);
    float left=-b*zMin/focalDistance;
    float right=c*zMin/focalDistance;
    proj.frustum(left,right,bot,top,zMin,zMax);
    return proj;
}

int RVStereoCamera::getCameraType() const
{
    return cameraType;
}

void RVStereoCamera::setCameraType(int newCameraType)
{
    cameraType = newCameraType;
}
