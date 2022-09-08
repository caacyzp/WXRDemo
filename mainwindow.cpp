#include "mainwindow.h"
#include "weatherobject.h"

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(50,50, 1200, 1200);
    WeatherObject* WXRObj = new WeatherObject(this);

}

mainWindow::~mainWindow()
{
}

