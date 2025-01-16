#ifndef RVSPECULARCUBE_H
#define RVSPECULARCUBE_H

#include "rvtexcube.h"

class RVSpecularCube : public RVTexCube
{
public:
    RVSpecularCube();

    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;

};

#endif // RVSPECULARCUBE_H
