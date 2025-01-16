#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

protected:
    bool aleatoire = false;

private slots:
    void createBody();
    void changeAmbientLight();
    void changeDiffuseLight();
    void changeSpecularLight();
    void takePicture();
};

#endif // MAINWINDOW_H
