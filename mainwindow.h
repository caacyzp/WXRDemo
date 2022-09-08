#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qevent.h>

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
};
#endif // MAINWINDOW_H
