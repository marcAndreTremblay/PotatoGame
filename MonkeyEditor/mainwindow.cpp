#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CustomWidget/gameobjecteditorWidget.h"
#include "CustomWidget/gameobjectpickerWidget.h"
#include "CustomWidget/meditortabwidget.h"
#include "CustomWidget/peditorbasetabwidget.h"
#include "ModelData/assetmanager.h"
#include "CustomWidget/custumopenglwidget.h"
#include "CustomWidget/gameobjecteditorWidget.h"

#include <QtWidgets>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    this->setMinimumHeight(800);
    this->setMinimumWidth(1200);

    MEditorTabWidget* main_tab_widget = new MEditorTabWidget();
      main_tab_widget->insertTab(0,new CustumOpenGlWidget(),QString("OpenGl widget"));
      main_tab_widget->insertTab(1,new GameObjectEditor(),QString("Editor widget"));
    GameObjectPickerWidget* seach_widget = new GameObjectPickerWidget();

    QGroupBox *MainLayout = new  QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout();

    MainLayout->setLayout(layout);

    layout->addWidget(seach_widget);
    layout->addWidget(main_tab_widget);


    setCentralWidget(MainLayout);
}

MainWindow::~MainWindow()
{

}
