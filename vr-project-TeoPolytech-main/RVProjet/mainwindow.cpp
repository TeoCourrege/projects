#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::createBody()
{

    float x = ui->valeurX->value();
    float y = ui->valeurY->value();
    float z = ui->valeurZ->value();

    float tangage = ui->valeurTangage->value();
    float lacet = ui->valeurLacet->value();
    float roulis = ui->valeurRoulis->value();
    QVector3D position = QVector3D(x,y,z);
    QQuaternion orientation = QQuaternion::fromEulerAngles(tangage, lacet, roulis);

    ui->widgetRV->addBody(position,orientation);
}




void MainWindow::changeAmbientLight()
{
    RVLight* lumiere = ui->widgetRV->getLight();
    QColor col = QColorDialog::getColor(lumiere->getAmbient(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->ambientButton->setStyleSheet(qss);
        lumiere->setAmbient(col);
    }
}

void MainWindow::changeDiffuseLight()
{
    RVLight* lumiere = ui->widgetRV->getLight();
    QColor col = QColorDialog::getColor(lumiere->getDiffuse(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->diffuseButton->setStyleSheet(qss);
        lumiere->setDiffuse(col);
    }
}

void MainWindow::changeSpecularLight()
{
    RVLight* lumiere = ui->widgetRV->getLight();
    QColor col = QColorDialog::getColor(lumiere->getSpecular(), this);
    if (col.isValid()) {
        QString qss = QString("background-color: %1;\n border: 1px solid black;\n border-radius: 5px;").arg(col.name());
        ui->specularButton->setStyleSheet(qss);
        lumiere->setSpecular(col);
    }
}

void MainWindow::takePicture()
{
    QPixmap img = ui->widgetRV->getImage();
    ui->image->clear();
    ui->image->setPixmap(img);

}



