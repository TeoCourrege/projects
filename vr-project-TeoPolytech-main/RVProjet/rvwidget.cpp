#include <iostream>
#include "rvwidget.h"
using namespace std;

RVWidget::RVWidget(QWidget *parent)
    : QOpenGLWidget(parent), QOpenGLFunctions()
{
    timer = new QTimer();
    angleY = 5;

    lastTime = QTime::currentTime();
    startTime = QTime::currentTime();
    grabKeyboard();

    action = QVector3D(-1,0,0);
}

RVWidget::~RVWidget()
{
}

RVLight *RVWidget::getLight() const
{
    return light;
}

RVScene *RVWidget::getScene() const
{
    return scene;
}

void RVWidget::update()
{


    QTime currentTime = QTime::currentTime();
    float t = lastTime.msecsTo(currentTime);
    lastTime = currentTime;
    float t2 = startTime.msecsTo(currentTime);

    if (animationOnLight){
        this->rotateLight(0.01);
    }


    if (animationOn) {
        scene->update(t, true);
        //specCube->setPosition(trajectory->pos(t2*0.001)+QVector3D(0,0,-8));
        world->setPosition(trajectory->pos(t2*0.001));
    }


    if(isFollowing){
        this->FollowObject();
    }

    if (changingCam == true){
        if (camId ==0)
        {
            scene->setCamera(camera2);
            QOpenGLWidget::update();
        }
        else if (camId == 1)
        {
            scene->setCamera(camera);
            dynamic_cast<RVSphericalCamera*>(camera)->setPosition(bb8->getPosition() + QVector3D(0,35,20));
            camera->setTarget(bb8->getPosition()+ QVector3D(0,35,0));
            QOpenGLWidget::update();
        }
        else if (camId == 2)
        {

            scene->setCamera(camera3);
            QVector3D pos_avion = avion->getPosition();
            QQuaternion or_avion = avion->getOrientation();
            camera->setPosition(pos_avion - 20*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0)));
            camera->setTarget(pos_avion);
            QOpenGLWidget::update();
        }
        changingCam = false;
    }

    if (changingCam == false){
        if (camId ==0)
        {
            if (isJumping && !isCrouched){
                up = camera2->jump(-10,20,up);
                if ((camera2->getPosition()).y() == 40){
                    isJumping = false;
                }
            }

            if (isCrouching){
                camera2->crouch(-25);
            }
            if (isGettingUp){
                camera2->getUp(-10);
            }
        }
        else if (camId == 1){
            camera->setRho(camrho);
        }
        else if (camId == 2)
        {
            QVector3D pos_avion = avion->getPosition();
            QQuaternion or_avion = avion->getOrientation();
            camera3->setPosition(pos_avion - 20*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0)));
            camera3->setTarget(pos_avion);
        }
        QOpenGLWidget::update();
    }



    if (animationCamera){

        QVector3D center = scene->getPosition();
        QVector3D pos = camera->getPosition();
        float x_new = (pos.x()-center.x())*cos(-0.01)+(pos.z()-center.z())*sin(-0.01);
        float z_new = -(pos.x()-center.x())*sin(-0.01)+(pos.z()-center.z())*cos(-0.01);
        camera->setPosition(QVector3D(x_new,pos.y(),z_new));
    }

    emit displayVelocity((double) 0.01f * ((int)(avion->getVelocity()/0.1f)));
    emit displayAltitude(17.5f+(double)0.01f*((int)((avion->getPosition().y())*10+350)/0.1f));


    QOpenGLWidget::update();
}




void RVWidget::changeFov(int fov)
{
    camera->setFov(fov);
    camera2->setFov(fov);
    camera3->setFov(fov);
    QOpenGLWidget::update();
}

void RVWidget::startAnimation()
{
    animationOn = !animationOn;
    //startTime = QTime::currentTime();
    lastTime = QTime::currentTime();


}


void RVWidget::startFollowObject()
{
    isFollowing = !isFollowing;

}

void RVWidget::startAnimationCamera()
{
    animationCamera = !animationCamera;
    this->update();
}

void RVWidget::startAnimationLight()
{
    animationOnLight = !animationOnLight;
}

void RVWidget::changeOpacity(int val)
{
    //body->setOpacity(val * 0.01f);
    plane->setOpacity(val * 0.01f);
    QOpenGLWidget::update();
}

void RVWidget::changeSize(int value)
{
    body->setScale(value*0.1f);
    QOpenGLWidget::update();
}

void RVWidget::changeSaturation(int value)
{
    int gris = (int)(2.55f * value);
    body->setGlobalColor(QColor(gris, gris, gris));
    QOpenGLWidget::update();
}

void RVWidget::changeCulling()
{
    bool culling = !body->getCulling();
    body->setCulling(culling);
    QOpenGLWidget::update();
}

void RVWidget::changeWireframe()
{
    bool wireframe = !world->getWireframe();
    world->setWireframe(wireframe);
    QOpenGLWidget::update();
}

void RVWidget::changeStereo()
{
    stereo = !stereo;
}


void RVWidget::addBody(QVector3D pos, QQuaternion orientation)
{
    this->makeCurrent();

    RVBody* newBody = new RVCube();
    /*
    if (corps == "Dé"){
        newBody = new RVDice();
        newBody->setTexture(":/textures/dice_texture.jpg");
    }
    else if (corps == "Cube texturé"){
        newBody = new RVTexCube();
        newBody->setTexture(":/textures/polytech_logo.jpg");
    }
    else if (corps == "Cube Speculaire"){
        newBody = new RVSpecularCube();
        dynamic_cast<RVSpecularCube*>(newBody)->setCubeTexture(":/textures/left.jpg",
                                                                   ":/textures/right.jpg",
                                                                   ":/textures/front.jpg",
                                                                   ":/textures/back.jpg",
                                                                   ":/textures/top.jpg",
                                                                   ":/textures/bottom.jpg");
    }
    else if (corps == "Tore"){
        newBody = new RVTorus();
        newBody->setFSFileName(":/shaders/FS_lit_checker.fsh");
    }
    else if (corps == "Tore Speculaire"){
        newBody = new RVSpecularTorus();
        dynamic_cast<RVSpecularTorus*>(newBody)->setCubeTexture(":/textures/left.jpg",
                                                                   ":/textures/right.jpg",
                                                                   ":/textures/front.jpg",
                                                                   ":/textures/back.jpg",
                                                                   ":/textures/top.jpg",
                                                                   ":/textures/bottom.jpg");
    }
    else if (corps == "Planete"){
        newBody = new RVPlanet();
        newBody->setTexture(":/textures/2k_earth_daymap.jpg");
        //dynamic_cast<RVPlanet*>(newBody)->setNightTexture(":/textures/2k_earth_nightmap.jpg", true, true);
    }
    else if (corps == "Sphere"){
        newBody = new RVSphere();
    }
    else if (corps == "Sphere Speculaire"){
        newBody = new RVSpecularSphere();
        dynamic_cast<RVSpecularSphere*>(newBody)->setCubeTexture(":/textures/left.jpg",
                                                                   ":/textures/right.jpg",
                                                                   ":/textures/front.jpg",
                                                                   ":/textures/back.jpg",
                                                                   ":/textures/top.jpg",
                                                                   ":/textures/bottom.jpg");
    }
    else if (corps == "Plan"){
        newBody = new RVPlane();
        newBody->setLight(light);
        newBody->setTexture(":/textures/wood.png");
    }
    */

    newBody->setLight(light);
    newBody->setPosition(pos);
    newBody->setOrientation(orientation);
    newBody->initialize();
    newBody->setCamera(camera);
    scene->append(newBody);

}

void RVWidget::setSkyboxImage(QString img)
{
    this->makeCurrent();
    skybox->setCubeTexture(":/textures/"+img+"/left.jpg",
                           ":/textures/"+img+"/right.jpg",
                           ":/textures/"+img+"/front.jpg",
                           ":/textures/"+img+"/back.jpg",
                           ":/textures/"+img+"/top.jpg",
                           ":/textures/"+img+"/bottom.jpg");
    QOpenGLWidget::update();

}

void RVWidget::changeXLight(double newX)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(newX, pos.y(), pos.z()));
    sun->setPosition(QVector3D(newX, pos.y(), pos.z()));
    QOpenGLWidget::update();
}

void RVWidget::changeYLight(double newY)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), newY, pos.z()));
    sun->setPosition(QVector3D(pos.x(), newY, pos.z()));
    QOpenGLWidget::update();
}

void RVWidget::changeZLight(double newZ)
{
    QVector3D pos = light->getPositionLight();
    light->setPositionLight(QVector3D(pos.x(), pos.y(), newZ));
    sun->setPosition(QVector3D(pos.x(), pos.y(), newZ));
    QOpenGLWidget::update();
}

void RVWidget::changeSpecCoeff(int newCoeff)
{
    scene->setSpecStrength(newCoeff);
    QOpenGLWidget::update();
}

void RVWidget::rotateLight(float angle)
{
    QVector3D center = scene->getPosition();
    QVector3D pos = light->getPositionLight();
    float x_new = (pos.x()-center.x())*cos(angle)+(pos.z()-center.z())*sin(angle);
    float z_new = -(pos.x()-center.x())*sin(angle)+(pos.z()-center.z())*cos(angle);
    light->setPositionLight(QVector3D(x_new,pos.y(),z_new));
    sun->setPosition(QVector3D(x_new,pos.y(),z_new));

}


void RVWidget::FollowObject()
{
    /*
    camera->setTheta(camera->getTheta());
    camera->setRho(camera->getRho());
    camera->setPhi(camera->getPhi());
*/

}



void RVWidget::changeTarget(int newTarget){
    changingCam = true;
    camId = newTarget;
}





void RVWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.566f, 0.867f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    camera = new RVSphericalCamera();
    camera->setFov(90.0f);
    camera->setPosition(QVector3D(0, -10, 0));
    camera->setZMin(1);
    camera->setZMax(2000);
    camrho = camera->getRho();


    camera2 = new RVSubjectiveCamera();
    camera2->setZMax(2000);
    camera2->setPosition(QVector3D(0, -10, 20));
    camera2->setFov(45.0f);
    camera2->setZMin(1);
    camera2->setZMax(2000);

    camera3 = new RVSphericalCamera();
    camera3->setFov(60.0f);
    camera3->setZMin(8);
    camera3->setZMax(2000);


    light = new RVLight();
    sun = new RVSphere();
    sun->setPosition(light->getPositionLight());
    sun->setTexture(":/textures/sun_texture.jpg",true,true);
    sun->initialize();

    building = new RVModel("../RVProjet/Model/IUT_INFO.X");
    building->setCamera(camera2);
    building->setCulling(false);
    building->translate(QVector3D(0,-55,150));
    building->initialize();

    bb8 = new RVBB8();
    bb8->setCamera(camera2);
    bb8->setPosition(QVector3D(70, -40, 0)); //QVector3D(70, -40, 0)
    bb8->setOrigin(QVector3D(-11,50,0)); //QVector3D(-11,50,0)
    bb8->setLight(light);
    bb8->setScale(0.3f);
    bb8->initialize();

    body = new RVTexCube();
    body->setPosition(QVector3D(-4, 3, -3));
    body->setCamera(camera2);
    body->setScale(3);
    body->setTexture(":/textures/polytech_logo.jpg");
    body->initialize();

    cube = new RVCube();
    cube->setPosition(QVector3D(0, 3, -3));
    cube->setCamera(camera2);
    cube->setScale(3);
    cube->initialize();

    dice = new RVDice();
    dice->setPosition(QVector3D(4, 3, -3));
    dice->setCamera(camera2);
    dice->setScale(3);
    dice->setTexture(":/textures/dice_texture.jpg");
    dice->initialize();


    plane = new RVTerrain(200);
    plane->setPosition(QVector3D(0, -40, 0));
    plane->setCamera(camera2);
    dynamic_cast<RVTerrain*>(plane)->setHeightFactor(10);
    dynamic_cast<RVTerrain*>(plane)->setHeightmap(":/textures/heightmap.png");
    plane->setTexture(":/textures/terrain.jpg");
    plane->setLight(light);
    plane->setScale(3);
    plane->initialize();

    /*
    world = new RVPlanet(2.5);
    world->setPosition(QVector3D(0, 3, -3));
    world->setTexture(":/textures/2k_earth_daymap.jpg", true, true);
    //dynamic_cast<RVPlanet*>(world)->setNightTexture(":/textures/2k_earth_nightmap.jpg", true, true);
    world->initialize(); 
*/

    world = new RVSpecularSphere();
    world->setPosition(QVector3D(0, 0, 0));
    world->setCamera(camera2);
    dynamic_cast<RVSpecularSphere*>(world)->setCubeTexture(":/textures/left.jpg",
                           ":/textures/right.jpg",
                           ":/textures/front.jpg",
                           ":/textures/back.jpg",
                           ":/textures/top.jpg",
                           ":/textures/bottom.jpg");
    world->initialize();

    /*torus = new RVTorus();
    torus->setPosition(QVector3D(0, 3, -3));
    //torus->setFSFileName(":/shaders/FS_lit_checker.fsh");
    torus->initialize();*/

    torus = new RVSpecularTorus();
    torus->setPosition(QVector3D(0, 0, 0));
    torus->setCamera(camera2);
    dynamic_cast<RVSpecularTorus*>(torus)->setCubeTexture(":/textures/left.jpg",
                           ":/textures/right.jpg",
                           ":/textures/front.jpg",
                           ":/textures/back.jpg",
                           ":/textures/top.jpg",
                           ":/textures/bottom.jpg");
    torus->initialize();

    skybox = new RVSkyBox();
    skybox->setPosition(QVector3D(0,0,0));
    skybox->setCamera(camera2);
    skybox->setScale(1000);
    skybox->setCubeTexture(":/textures/left.jpg",
                           ":/textures/right.jpg",
                           ":/textures/front.jpg",
                           ":/textures/back.jpg",
                           ":/textures/top.jpg",
                           ":/textures/bottom.jpg");
    skybox->initialize();

    specCube = new RVSpecularCube();
    specCube->setPosition(QVector3D(0,0,-8));
    specCube->setCamera(camera2);
    dynamic_cast<RVSpecularCube*>(specCube)->setCubeTexture(":/textures/left.jpg",
                           ":/textures/right.jpg",
                           ":/textures/front.jpg",
                           ":/textures/back.jpg",
                           ":/textures/top.jpg",
                           ":/textures/bottom.jpg");
    specCube->setScale(2);
    specCube->initialize();

    avion = new RVAirplane();
    avion->setCamera(camera2);
    avion->setLight(light);
    avion->initialize();
    avion->translate(QVector3D(0,-10,0));
    avion->setScale(0.5f);



    scene = new RVScene();
    scene->setPosition(QVector3D(0,0,0));
    scene->append(skybox);
    scene->append(building);
    scene->append(body);
    scene->append(dice);
    //scene->append(plane);
    scene->append(world);
    scene->append(torus);
    scene->append(cube);
    scene->append(sun);
    scene->append(specCube);
    scene->setCamera(camera2);
    scene->setLight(light);
    scene->append(avion);
    scene->append(bb8);


    trajectory = new RVBounce();



    //trajectory->setCamera(camera);
    //trajectory->setPosition(QVector3D(0, 0, -8));
    //trajectory->setScale(2);
    //trajectory->initialize();
    //scene->append(trajectory);
    //*/


    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

void RVWidget::resizeGL(int w, int h)
{
    float aspect = ((float)w)/h;
    camera->setAspect(aspect);
    camera2->setAspect(aspect);
    glViewport(0, 0, w, h);
}

void RVWidget::paintGL()
{
    QPainter p(this);

    //début du code OpenGL
    p.beginNativePainting();
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    scene->draw();
    glDisable(GL_DEPTH_TEST);
    p.endNativePainting();
    //fin du code OpenGL

    nbOfPaint ++;

    //Calcul du fps
    if (nbOfPaint > 100)
    {
        QTime currentTime = QTime::currentTime();
        float elapsedTime = startTime.msecsTo(currentTime) * 0.001f;
        fps = nbOfPaint/elapsedTime;
        nbOfPaint = 0;
        startTime = currentTime;
    }
    p.setPen(Qt::yellow);
    p.setFont(QFont("Arial", 12));
    p.drawText(5, 5, width(), height(), Qt::AlignLeft, "Fps = " + QString::number(fps, 'f',2) );

    if (camId == 0){
        p.setPen(Qt::white);
        p.setFont(QFont("Arial", 24));
        p.drawText(0, 0, width(), height(), Qt::AlignCenter, "+");
    }



}

void RVWidget::mousePressEvent(QMouseEvent *event)
{
    oldPos = event->position();
}

void RVWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = (event->position().x() - oldPos.x()) / width();
    float dy = (event->position().y() - oldPos.y()) / height();

    float xAngle = 180 * dy;
    float yAngle = 180 * dx;

    RVSubjectiveCamera* cam2 = (RVSubjectiveCamera*)camera2;
    cam2->turn(dx);
    cam2->tilt(dy);

    camera->setPhi(camera->getPhi() + qDegreesToRadians(xAngle));
    camera->setTheta(camera->getTheta() + qDegreesToRadians(yAngle));

    camera3->setPhi(camera->getPhi() + qDegreesToRadians(xAngle));
    camera3->setTheta(camera->getTheta() + qDegreesToRadians(yAngle));

    //body->rotate(yAngle, QVector3D(0, 1, 0));
    //body->rotate(xAngle, QVector3D(1, 0, 0));
    QOpenGLWidget::update();

    oldPos = event->pos();
}

void RVWidget::keyPressEvent(QKeyEvent *event)
{
    QVector3D camPos = camera->getPosition();
    QVector3D pos_avion = avion->getPosition();
    QQuaternion or_avion = avion->getOrientation();


    float delta = 1.2f;
    switch (event->key())
    {
        case Qt::Key_Left:
            camera2->lateral(-delta);
            break;
        case Qt::Key_Right:
            camera2->lateral(delta);
            break;
        case Qt::Key_Up:
            camera2->move(delta);
            break;
        case Qt::Key_Down:
            camera2->move(-delta);
            break;

        case Qt::Key_Space:{
            if (!isCrouched){
                isJumping = true;
                up = true;
            }
            break;}

        case Qt::Key_C:{
            if (!isCrouched){
                isCrouching = true;
                isGettingUp = false;
            }
            else{
                isCrouching = false;
                isGettingUp = true;
            }
            isCrouched = !isCrouched;
            break;}


            // Accélérer
        case Qt::Key_W:
        {
            avion->setAcceleration(1.01*avion->getAcceleration());
            avion->setVelocity(avion->getVelocity()*1.1);
            break;
        }

            // Deccélérer
        case Qt::Key_X:
        {
            avion->setAcceleration(0.99*avion->getAcceleration());
            avion->setVelocity(avion->getVelocity()/1.1);
            break;
        }

            // Monter
        case Qt::Key_Z:
            if(camId == 1){
                dynamic_cast<RVBB8*>(bb8)->move(delta, action, QVector3D(-1,0,0), QVector3D(0,0,1));
                action = QVector3D(-1,0,0);
                camera->setTarget(bb8->getPosition()+QVector3D(0,35,0));
                dynamic_cast<RVSphericalCamera*>(camera)->setPosition(camera->getPosition() + delta * action);
            }
            if(camId == 2){
                avion->rotate(1,avion->getOrientation().rotatedVector(QVector3D(1,0,0)));
                camPos = (pos_avion +(- 15*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0))));

            }
            break;

            // Descendre
        case Qt::Key_S:
            if(camId == 1){
                dynamic_cast<RVBB8*>(bb8)->move(delta, action, QVector3D(1,0,0), QVector3D(0,0,1));
                action = QVector3D(1,0,0);
                camera->setTarget(bb8->getPosition()+QVector3D(0,35,0));
                dynamic_cast<RVSphericalCamera*>(camera)->setPosition(camera->getPosition() + delta * action);
            }
            if(camId == 2){
                avion->rotate(-1,avion->getOrientation().rotatedVector(QVector3D(1,0,0)));
                camPos = (pos_avion +(- 15*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0))));
            }
            break;

            // Tourner à gauche
        case Qt::Key_Q:
        {
            if(camId == 1){
                dynamic_cast<RVBB8*>(bb8)->move(delta, action, QVector3D(0,0,1), QVector3D(-1,0,0));
                action = QVector3D(0,0,1);
                camera->setTarget(bb8->getPosition()+QVector3D(0,35,0));
                dynamic_cast<RVSphericalCamera*>(camera)->setPosition(camera->getPosition() + delta * action);
            }
            if(camId == 2){
            avion->rotate(0.55f,avion->getOrientation().rotatedVector(QVector3D(0,1,0)));
            avion->rotate(1,avion->getOrientation().rotatedVector(QVector3D(0,0,1)));
            camPos = (pos_avion +(- 15*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0))));
            }
            break;
        }

            // Tourner à droite
        case Qt::Key_D:
        {
            if(camId == 1){
                dynamic_cast<RVBB8*>(bb8)->move(delta, action, QVector3D(0,0,-1), QVector3D(-1,0,0));
                action = QVector3D(0,0,-1);
                camera->setTarget(bb8->getPosition()+QVector3D(0,35,0));
                dynamic_cast<RVSphericalCamera*>(camera)->setPosition(camera->getPosition() + delta * action);
            }
            if(camId == 2){
                avion->rotate(-0.55f,avion->getOrientation().rotatedVector(QVector3D(0,1,0)));
                avion->rotate(-1,avion->getOrientation().rotatedVector(QVector3D(0,0,1)));
                camPos = (pos_avion +(- 15*or_avion.rotatedVector(QVector3D(0,0,-1)) + 4*or_avion.rotatedVector(QVector3D(0,1,0))));
            }
            break;
        }
    }
    camera->setPosition(camPos);
    QOpenGLWidget::update();
}


void RVWidget::wheelEvent(QWheelEvent *event)
{
    QPointF zoom = event->angleDelta();


    camrho = camrho - (zoom.y()/120.0f)*2;

    event->accept();
    QOpenGLWidget::update();
}

QPixmap RVWidget::getImage()
{
    makeCurrent();

    QOpenGLFramebufferObject* fbo = new QOpenGLFramebufferObject(this->width(), this->height());
    fbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    fbo->bind();
    glViewport(0, 0, this->width(), this->height());
    paintGL();
    QImage img(fbo->toImage(true));
    fbo->release();
    return QPixmap::fromImage(img);
}

