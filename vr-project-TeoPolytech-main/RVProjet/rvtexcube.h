#ifndef RVTEXCUBE_H
#define RVTEXCUBE_H

#include "rvbody.h"

class RVTexCube : public RVBody
{
public:
    RVTexCube();

    // RVBody interface
public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // RVTEXCUBE_H
