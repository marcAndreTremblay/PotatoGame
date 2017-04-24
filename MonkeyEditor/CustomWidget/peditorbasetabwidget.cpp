#include "peditorbasetabwidget.h"
#include "custumopenglwidget.h"

PEditorBaseTabWidget::PEditorBaseTabWidget(QWidget *parent) :
    QWidget(parent)
{
    base_layout = new QVBoxLayout();

       CustumOpenGlWidget *myLabel = new CustumOpenGlWidget();



       base_layout->addWidget(myLabel);
       setLayout(base_layout);
}

PEditorBaseTabWidget::~PEditorBaseTabWidget(){

}
