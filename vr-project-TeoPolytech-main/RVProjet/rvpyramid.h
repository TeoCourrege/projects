#ifndef RVPYRAMID_H
#define RVPYRAMID_H

#include "rvbody.h"

class RVPyramid : public RVBody
{
public:
    RVPyramid();
    void draw() override;


protected:
    void initializeBuffer() override;
    void initializeVAO() override;
};

#endif // RVPYRAMID_H
