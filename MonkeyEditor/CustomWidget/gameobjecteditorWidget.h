#ifndef GAMEOBJECTEDITOR_H
#define GAMEOBJECTEDITOR_H

#include <QtWidgets>


class GameObjectEditor : public QGroupBox
{
    Q_OBJECT
private:
     QLineEdit *obj_name_editor;

     QSpinBox *obj_weight_editor;
     QSpinBox *obj_p_atk_editor;
     QSpinBox *obj_m_atk_editor;
     QSpinBox *obj_p_def_editor;
     QSpinBox *obj_m_def_editor;
public:
    explicit GameObjectEditor(QWidget *parent = 0);
     ~GameObjectEditor();
signals:

public slots:

};

#endif // GAMEOBJECTEDITOR_H
