#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <QObject>
#include <QIcon>
#include <QList>
#include <QImage>

class AssetManager : public QObject
{
    Q_OBJECT
private:
    QList<QImage*> *bitmap_list;
public:
    explicit AssetManager(QObject *parent = 0);
    ~AssetManager();
    void LoadAsset();

signals:

public slots:
};

#endif // ASSETMANAGER_H
