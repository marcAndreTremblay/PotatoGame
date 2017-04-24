#include "gameobjectpickerWidget.h"

#include <QtWidgets>


GameObjectPickerWidget::GameObjectPickerWidget(QWidget *parent):
    QGroupBox(parent)
{
    this->setMaximumWidth(250);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    QGroupBox * top_seach_box = new QGroupBox();
    QHBoxLayout *top_seach_layout = new QHBoxLayout();
                seach_text_editor = new QLineEdit();
    QPushButton *button_seach = new QPushButton("Seach");

         top_seach_layout->addWidget(new QLabel("Seach : "));
         top_seach_layout->addWidget(seach_text_editor);
         top_seach_layout->addWidget(button_seach);
    top_seach_box->setLayout(top_seach_layout);

    connect(button_seach,SIGNAL(released()),
            this,SLOT(on_released()));

    connect(seach_text_editor,SIGNAL(returnPressed()),
            this,SLOT(on_returnPressed()));

    obj_tree = new QTreeWidget();
    obj_tree->setHeaderLabel(QString("Name"));

    layout->addWidget(top_seach_box);
     layout->addWidget(obj_tree);

    this->setLayout(layout);
}
void GameObjectPickerWidget::on_released(){
    seach_text_editor->setText("Test");
}

void GameObjectPickerWidget::on_returnPressed(){
    obj_tree->insertTopLevelItem(0,new  QTreeWidgetItem((QTreeWidgetItem*)0, QStringList(QString("Element")),0));
}

GameObjectPickerWidget::~GameObjectPickerWidget()
{

}
