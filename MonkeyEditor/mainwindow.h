#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CustomWidget/gameobjecteditorWidget.h"
#include "CustomWidget/gameobjectpickerWidget.h"

#include <QMainWindow>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

};


#endif // MAINWINDOW_H
