#ifndef PEDITORBASETABWIDGET_H
#define PEDITORBASETABWIDGET_H

#include <QtWidgets>
#include <QLabel>

class PEditorBaseTabWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *base_layout;
public:
    explicit PEditorBaseTabWidget(QWidget *parent = 0);
    ~PEditorBaseTabWidget();
signals:
public slots:
};

#endif // PEDITORBASETABWIDGET_H
