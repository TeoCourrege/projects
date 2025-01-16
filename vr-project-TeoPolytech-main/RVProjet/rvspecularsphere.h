#ifndef RVSPECULARSPHERE_H
#define RVSPECULARSPHERE_H

#include "rvsphere.h"

class RVSpecularSphere : public RVSphere
{
public:
    RVSpecularSphere();
    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;

};

#endif // RVSPECULARSPHERE_H
