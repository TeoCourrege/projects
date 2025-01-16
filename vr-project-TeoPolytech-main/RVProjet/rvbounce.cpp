#include "rvbounce.h"

RVBounce::RVBounce(float hMax, float tMax):RVCurve()
{
    hmax = hMax;
    tmax = tMax;


    FSFileName = ":/shaders/FS_simple.fsh";
    VSFileName = ":/shaders/VS_simpler.vsh";
}

float RVBounce::getHmax()
{
    return hmax;
}

float RVBounce::getTmax()
{
    return tmax;
}

void RVBounce::setHmax(float newHmax){

    hmax=newHmax;

}
void RVBounce::setTmax(float newTmax){

    tmax=newTmax;
}

float RVBounce::x(double t)
{
    return 0;
}

float RVBounce::y(double t)
{
    float a=-hmax/pow(tmax,2);
    float b=2*hmax/tmax;
    float c = fmod(t, 2*tmax);
    return a*pow(c,2)+b*c;
}

float RVBounce::z(double t)
{
    return 0;
}


