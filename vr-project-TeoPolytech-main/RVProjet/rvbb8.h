#ifndef RVBB8_H
#define RVBB8_H

#include "rvmodel.h"

class RVBB8 : public RVModel
{
public:
    RVBB8();
    void draw() override;
    void move(float d, QVector3D orientAct, QVector3D direction, QVector3D perp);
};

#endif // RVBB8_H
