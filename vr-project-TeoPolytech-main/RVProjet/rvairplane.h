#ifndef RVAIRPLANE_H
#define RVAIRPLANE_H

#include "rvmodel.h"

class RVAirplane : public RVModel
{
public:
    RVAirplane();

    float getVelocity() const;
    void setVelocity(float newVelocity);

    float getAcceleration() const;
    void setAcceleration(float newAcceleration);

    void update(float time, bool relative = true);

private:
    float velocity;
    float acceleration;
};

#endif // RVAIRPLANE_H
