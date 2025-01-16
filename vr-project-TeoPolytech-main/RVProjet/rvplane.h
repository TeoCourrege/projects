#ifndef RVPLANE_H
#define RVPLANE_H

#include "rvbody.h"

class RVPlane : public RVBody
{
public:
    RVPlane(float length = 10.0f, float width = 10.0f);

    // RVBody interface
public:
    void draw() override;
    void initializeBuffer() override;

    float getLength() const;
    void setLength(float newLength);

    float getWidth() const;
    void setWidth(float newWidth);


private:
    float length;
    float width;
};

#endif // RVPLANE_H
