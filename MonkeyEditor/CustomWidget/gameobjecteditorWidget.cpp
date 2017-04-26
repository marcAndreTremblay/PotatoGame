#include "CustomWidget/gameobjecteditorWidget.h"

#include <QtWidgets>
#include <QLabel>

GameObjectEditor::GameObjectEditor(QWidget *parent) :
    QGroupBox(tr("Object editor"),parent)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
    QVBoxLayout *layout = new QVBoxLayout();
    this->setLayout(layout);

     QGroupBox *ProGrp1 = new  QGroupBox(tr("Property group 1"));
     QGridLayout *Glayout = new QGridLayout();

     ProGrp1->setLayout(Glayout);

         Glayout->addWidget(new QLabel("Name"),0,0);
         Glayout->addWidget(new QLabel("Weight/Unit"),1,0);
         Glayout->addWidget(new QLabel("P Atk"),2,0);
         Glayout->addWidget(new QLabel("M Atk"),3,0);
         Glayout->addWidget(new QLabel("P Def"),4,0);
         Glayout->addWidget(new QLabel("M Def"),5,0);


         Glayout->addWidget(obj_name_editor = new QLineEdit(),0,1);
         Glayout->addWidget(obj_weight_editor= new QSpinBox(),1,1);
         Glayout->addWidget(obj_p_atk_editor= new QSpinBox(),2,1);
         Glayout->addWidget(obj_m_atk_editor= new QSpinBox(),3,1);
         Glayout->addWidget(obj_p_def_editor= new QSpinBox(),4,1);
         Glayout->addWidget(obj_m_def_editor= new QSpinBox(),5,1);


         Glayout->addWidget(new QLabel("Test2"),0,1);

         layout->addWidget(ProGrp1);

     QGroupBox *ProGrp2 = new  QGroupBox(tr("Property group 2"));
     QVBoxLayout *Grp2Vlayout = new QVBoxLayout();
     ProGrp2->setLayout(Grp2Vlayout);
         Grp2Vlayout->addWidget(new QLabel("Test1"));
         Grp2Vlayout->addWidget(new QLabel("Test2"));

     layout->addWidget(ProGrp2);



}
GameObjectEditor::~GameObjectEditor()
{

}
