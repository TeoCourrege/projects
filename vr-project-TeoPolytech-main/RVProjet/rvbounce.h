#ifndef RVBOUNCE_H
#define RVBOUNCE_H

#include "rvcurve.h"
#include <math.h>

class RVBounce : public RVCurve
{
public:
    RVBounce(float hMax = 5,float tMax = 1);
    float getHmax();
    void setHmax(float newHmax);

    float getTmax();
    void setTmax(float newTmax);

    float x(double t) override;
    float y(double t) override;
    float z(double t) override;

private:
    float hmax;
    float tmax;
};

#endif // RVBOUNCE_H
