#ifndef GAMEOBJECTTREEITEM_H
#define GAMEOBJECTTREEITEM_H

#include <QtWidgets>

class GameObjectTreeItem : public QTreeWidgetItem
{
private:
public:
    GameObjectTreeItem(QTreeWidget *parent, int type);
     ~GameObjectTreeItem();
};

#endif // GAMEOBJECTTREEITEM_H
