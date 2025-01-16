#ifndef RVSCENE_H
#define RVSCENE_H

#include <QList>
#include "rvbody.h"
#include "rvlight.h"

class RVScene : public QList<RVBody*>
{
public:
    RVScene();
    void setCamera(RVCamera* pCamera);
    void translate(QVector3D vec);
    void rotate(float angle, QVector3D axis);
    void draw();

    RVLight *getLight() const;
    void setLight(RVLight *newLight);

    float getSpecStrength() const;
    void setSpecStrength(float newSpecStrength);

    QVector3D getPosition() const;
    void setPosition(const QVector3D &newPosition);

    void update(float t, bool relative);

protected:
    RVCamera* camera;
    RVLight* light;
    float specStrength;
    QVector3D position;
};

#endif // RVSCENE_H
