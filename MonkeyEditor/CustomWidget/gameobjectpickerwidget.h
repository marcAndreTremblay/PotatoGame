#ifndef GAMEOBJECTPICKERWIDGET_H
#define GAMEOBJECTPICKERWIDGET_H

#include <QtWidgets>

class GameObjectPickerWidget : public QGroupBox
{
    Q_OBJECT
private:
    QLineEdit *seach_text_editor;
    QTreeWidget * obj_tree;
public:
    GameObjectPickerWidget(QWidget *parent = 0);
     ~GameObjectPickerWidget();
signals:
public slots:
    void on_released();
    void on_returnPressed();
};

#endif // GAMEOBJECTPICKERWIDGET_H
