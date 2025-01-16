#ifndef RVPLANET_H
#define RVPLANET_H

#include "rvsphere.h"

class RVPlanet : public RVSphere
{
public:
    RVPlanet(double r = 1.0);

    void setNightTexture(QString filename, bool hMirror = true, bool vMirror = true);
    void draw() override;



private:
    QOpenGLTexture *nightTexture;
    float time = 0.0f;
};

#endif // RVPLANET_H
