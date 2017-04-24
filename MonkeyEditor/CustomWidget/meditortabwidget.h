#ifndef MEDITORTABWIDGET_H
#define MEDITORTABWIDGET_H

#include <QtWidgets>

class MEditorTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MEditorTabWidget(QWidget *parent = 0);
signals:

public slots:
    void on_tabCloseRequested(int index);
};

#endif // MEDITORTABWIDGET_H
