#include "assetmanager.h"


AssetManager::AssetManager(QObject *parent) : QObject(parent)
{

    bitmap_list = new QList<QImage*>();
  //  QBitmap* test = new QBitmap();
   // QIcon* test2 = new QIcon(test);
}
AssetManager::~AssetManager(){
    delete bitmap_list;
}

void AssetManager::LoadAsset()
{
    QImage* new_bm = new QImage(QString("Asset/varnish_of_purity.jpg"));
    this->bitmap_list->append(new_bm);
}
