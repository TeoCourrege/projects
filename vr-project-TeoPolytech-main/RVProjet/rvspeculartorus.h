#ifndef RVSPECULARTORUS_H
#define RVSPECULARTORUS_H

#include "rvtorus.h"


class RVSpecularTorus : public RVTorus
{
public:
    RVSpecularTorus();
    void setCubeTexture(QString leftImage, QString rightImage,
                        QString frontImage, QString backImage,
                        QString topImage, QString bottomImage);
    void draw() override;

};

#endif // RVSPECULARTORUS_H
