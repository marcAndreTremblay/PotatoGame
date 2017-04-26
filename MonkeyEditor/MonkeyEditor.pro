#-------------------------------------------------
#
# Project created by QtCreator 2017-04-17T17:19:58
#
#-------------------------------------------------

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonkeyEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp\
        mainwindow.cpp  \
    CustomWidget/gameobjecteditorWidget.cpp \
    CustomWidget/gameobjectpickerWidget.cpp \
    CustomWidget/meditortabwidget.cpp \
    CustomWidget/peditorbasetabwidget.cpp \
    CustomWidget/CustumTreeItemWidget/gameobjecttreeitem.cpp \
    ModelData/assetmanager.cpp \
    CustomWidget/custumopenglwidget.cpp \
    pshaderprogram.cpp \
    pbasemesh.cpp \
    pmodelshaderprogram.cpp \
    p3dmodeldata.cpp \
    plight.cpp \
    pmodelvao.cpp \
    pcamera.cpp \
    plineshaderprogram.cpp \
    plinevao.cpp \
    CustomWidget/itemviewwidget.cpp

HEADERS += mainwindow.h \
    CustomWidget/gameobjecteditorWidget.h \
    CustomWidget/gameobjectpickerWidget.h \
    CustomWidget/meditortabwidget.h \
    CustomWidget/peditorbasetabwidget.h \
    CustomWidget/CustumTreeItemWidget/gameobjecttreeitem.h \
    ModelData/assetmanager.h \
    CustomWidget/custumopenglwidget.h \
    pshaderprogram.h \
    pbasemesh.h \
    pmodelshaderprogram.h \
    p3dmodeldata.h \
    plight.h \
    pmodelvao.h \
    pcamera.h \
    plineshaderprogram.h \
    plinevao.h \
    CustomWidget/itemviewwidget.h

FORMS += mainwindow.ui


RC_FILE += myapp.rc
