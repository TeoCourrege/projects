#include "rvhelix.h"

RVHelix::RVHelix(double radius, double pitch)
    :RVCurve()
{
    numWindings = 3;
    this->radius = radius;
    frequency = 1;
    this->pitch = pitch;
    maxT = M_PI * 2  * numWindings;

    FSFileName = ":/shaders/FS_simple.fsh";
    VSFileName = ":/shaders/VS_simpler.vsh";
}

double RVHelix::getRadius() const
{
    return radius;
}

void RVHelix::setRadius(double radius)
{
    this->radius = radius;
}

double RVHelix::getFrequency() const
{
    return frequency;
}

void RVHelix::setFrequency(double frequency)
{
    this->frequency = frequency;
}

double RVHelix::getPitch() const
{
    return pitch;
}

void RVHelix::setPitch(double pitch)
{
    this->pitch = pitch;
}

float RVHelix::x(double t)
{
    return float(radius*qCos(frequency*t));
}

float RVHelix::y(double t)
{
    return float(pitch * frequency * t / 2 * M_PI);
}

float RVHelix::z(double t)
{
    return float(radius*qSin(frequency*t));
}

double RVHelix::getNumWindings() const
{
    return numWindings;
}

void RVHelix::setNumWindings(double numWindings)
{
    this->numWindings = numWindings;
}
