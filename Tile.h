
//#include "dataLoader.h"
//#include <QGraphicsObject>

//#ifndef TILE_H
//#define TILE_H

//class Tile : public QGraphicsObject
//{
//    Q_OBJECT

//public:
//    Tile(
//            int x,
//            int y,
//            DataLoader::TileLayerStruct* layerRessources,
//            QString layer,
//            int tileType,                   // number in the .tmx
//            DataLoader *dataLoader,
//            QGraphicsItem* parent = nullptr);
//    QRectF boundingRect() const override;
//    QPainterPath shape() const override;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//    int getTileType();

//private:
//    QString layer;
//    QPixmap* image;
//    QRectF boundingRectangle;

//protected:
//    // For TileCandyPlacement type tiles
//    int tileType;
//    DataLoader *dataLoader;
//};

//#endif // TILE_H
