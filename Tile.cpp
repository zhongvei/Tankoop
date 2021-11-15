
//#include "dataLoader.h"
//#include "Tile.h"
//#include <QGraphicsItem>
//#include <QPainter>
//#include <QDebug>

//#define IMAGE_PIXEL_SIZE 13

//Tile::Tile(int indexX, int indexY, DataLoader::TileLayerStruct* layerRessources, QString layer, int tileType, DataLoader *dataLoader, QGraphicsItem* parent)
//    :QGraphicsObject(parent),
//      layer(layer),
//      tileType(tileType),
//    dataLoader(dataLoader)
//{
//    int tileSize = dataLoader->getTileSize();
//    image = dataLoader->getTileRessource(tileType)->image;
//    int x = layerRessources->topLeftX * tileSize + indexX * tileSize;
//    int y = layerRessources->topLeftY * tileSize + indexY * tileSize;
//    int ratio = tileSize / IMAGE_PIXEL_SIZE;
//    int tileWidth = image->width() * ratio;
//    int tileHeight = image->height() * ratio;

//    prepareGeometryChange();
//    boundingRectangle = QRectF(0, tileSize - tileHeight, tileWidth, tileHeight);

//    setPos(x, y);

//    if(layerRessources->zIndex.userType() == QMetaType::Int)
//        setZValue(layerRessources->zIndex.toInt());
//    else
//        setZValue(y + tileSize);
//}

//// OVERRIDE REQUIRED

///**
// * Draw the content of the item in local coordinates.
// */
//void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    if(!(layer == "1-spawns" || layer == "4-collision" || layer == "5-config")) {
//        QRectF sourceRect(0, 0, image->width(), image->height());
//        painter->drawPixmap(boundingRect(), *image, sourceRect);
//    }

//    // Lines for the compiler
//    Q_UNUSED(option)
//    Q_UNUSED(widget)
//}

//int Tile::getTileType() {
//    return tileType;
//}

///**
// * Returns the outer limits of the element as a rectangle.
// * Called by QGraphicsView to determine which regions need to be redrawn
// */
//QRectF Tile::boundingRect() const {
//    return boundingRectangle;
//}

///**
// * Collision Detection
// */
//QPainterPath Tile::shape() const {
//    QPainterPath path;
//    path.addRect(QRect(0, 0, dataLoader->getTileSize(), dataLoader->getTileSize()));
//    return path;
//}
