#include "rvscene.h"

RVScene::RVScene()
{

}



void RVScene::update(float t, bool relative)
{
    foreach (RVBody* body, *this) {
        body->update(t, relative);
    }
}

void RVScene::setCamera(RVCamera *pCamera)
{
    camera = pCamera;
    foreach (RVBody* body, *this) {
        body->setCamera(pCamera);
    }

}

void RVScene::translate(QVector3D vec)
{
    foreach (RVBody* body, *this) {
        body->translate(vec);
    }
}

void RVScene::rotate(float angle, QVector3D axis)
{
    foreach (RVBody* body, *this) {
        body->rotate(angle, axis);
    }
}

void RVScene::draw()
{
    foreach (RVBody* body, *this) {
        body->draw();
    }
}

RVLight *RVScene::getLight() const
{
    return light;
}

void RVScene::setLight(RVLight *newLight)
{
    light = newLight;
    foreach (RVBody* body, *this) {
        body->setLight(newLight);
    }
}

float RVScene::getSpecStrength() const
{
    return specStrength;
}

void RVScene::setSpecStrength(float newSpecStrength)
{
    specStrength = newSpecStrength;
    foreach (RVBody* body, *this) {
        body->setSpecStrength(newSpecStrength);
    }
}

QVector3D RVScene::getPosition() const
{
    return position;
}

void RVScene::setPosition(const QVector3D &newPosition)
{
    position = newPosition;
}




