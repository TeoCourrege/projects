#ifndef RVTERRAIN_H
#define RVTERRAIN_H

#include "rvsurface.h"

class RVTerrain : public RVSurface
{
public:
    RVTerrain(double width);
    void draw() override;
    void setHeightmap(QString textureFilename);

    float getHeightFactor() const;
    void setHeightFactor(float newHeightFactor);

protected :
    QOpenGLTexture *heightmap;
    float heightFactor;
    float x(double s, double t) override;
    float y(double s, double t) override;
    float z(double s, double t) override;
};

#endif // RVTERRAIN_H
