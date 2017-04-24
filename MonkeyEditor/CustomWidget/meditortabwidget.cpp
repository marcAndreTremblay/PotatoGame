#include "meditortabwidget.h"

MEditorTabWidget::MEditorTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    this->setTabsClosable(true);
    this->setTabShape(Rounded);
    this->setTabPosition(QTabWidget::North);

    this->connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(on_tabCloseRequested(int)));
}

void MEditorTabWidget::on_tabCloseRequested(int index){
    this->removeTab(index);
}
