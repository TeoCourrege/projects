#ifndef RVDICE_H
#define RVDICE_H

#include "rvbody.h"

class RVDice : public RVBody
{
public:
    RVDice();

public:
    void draw() override;
    QMatrix4x4 modelMatrix() override;
    void initializeBuffer() override;
    void initializeVAO() override;
    void update(float t, bool relative) override;

};

#endif // RVDICE_H
