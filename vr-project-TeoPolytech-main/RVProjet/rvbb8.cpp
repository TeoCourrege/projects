#include "rvbb8.h"


#include<iostream>
using namespace std;

RVBB8::RVBB8() : RVModel("../RVProjet/Model/BB8/bb8.obj")
{
    meshes[0]->setTexture("../RVProjet/Model/BB8/HEAD_diff_MAP.jpg"); // tete
    meshes[1]->setTexture("../RVProjet/Model/BB8/white_dirt_map.jpg"); // bas grande antenne
    meshes[2]->setTexture("../RVProjet/Model/BB8/white_dirt_map.jpg"); // haut grande antenne
    meshes[3]->setTexture("../RVProjet/Model/BB8/BODY_self_ill_MAP.jpg");
    meshes[4]->setTexture("../RVProjet/Model/BB8/BODY_self_ill_MAP.jpg"); // petite antenne
    meshes[5]->setTexture("../RVProjet/Model/BB8/HEAD_diff_MAP.jpg"); // anneau sous la tete
    meshes[6]->setTexture("../RVProjet/Model/BB8/Body_diff_MAP.jpg"); // corps
}


void RVBB8::draw()
{
    foreach (RVMesh* mesh, meshes) {
        mesh->draw();
    }
}

void RVBB8::move(float d, QVector3D orientAct, QVector3D direction, QVector3D perp)
{
    translate(d * direction);
    QVector3D v1 = orientAct;
    QVector3D v2 = direction;
    float theta = qRadiansToDegrees(qAcos(QVector3D::dotProduct(v1,v2)));
    QVector3D rot = QVector3D(0,1,0);
    if (QVector3D::dotProduct(v1,v2) == 0){
        rot = QVector3D::crossProduct(v1,v2);
    }
    for (int i=0; i<=6; i++){
        meshes[i]->rotate(theta, rot);
    }
    if (direction == QVector3D(0,0,1) || direction == QVector3D(1,0,0)){
        meshes[6]->rotate(-d*3, perp);
    }
    else {
        meshes[6]->rotate(d*3, perp);
    }
}

