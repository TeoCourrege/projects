#ifndef RVCUBE_H
#define RVCUBE_H

#include "rvbody.h"

class RVCube : public RVBody
{
public:
    RVCube();

    // RVBody interface
public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // RVCUBE_H
