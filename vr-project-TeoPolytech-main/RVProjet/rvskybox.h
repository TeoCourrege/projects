#ifndef RVSKYBOX_H
#define RVSKYBOX_H

#include "rvbody.h"


class RVSkyBox : public RVBody
{
public:
    RVSkyBox();
    void initializeBuffer() override;
    void initializeVAO() override;
    void draw() override;
    void setCubeTexture(QString leftImage, QString rightImage,
                            QString frontImage, QString backImage,
                            QString topImage, QString bottomImage);


};

#endif // RVSKYBOX_H
