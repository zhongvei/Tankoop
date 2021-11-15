///*
// * Description : Cette  classe ne crée qu’un seul objet.
// *               Son utilité est de pouvoir capturer les événements du clavier
// *               au même endroit avant de les envoyer aux objets Player correspondants.
// * Version     : 1.0.0
// * Date        : 25.01.2021
// * Auteurs     : Prétat Valentin, Badel Kevin et Margueron Yasmine
//*/

//#include "keyInput.h"
//#include <QGraphicsItem>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QApplication>
//#include <QKeyEvent>
//#include <QRectF>
//#include <QDebug>

//keyInput::keyInput(int focusedPlayerId, QGraphicsObject *parent)
//    : QGraphicsObject(parent)
//{
//    setFlag(QGraphicsItem::ItemIsFocusable, true);
//    setPlayerKeys(focusedPlayerId);
//}

//void keyInput::keyPress(QKeyEvent * event) {
//    int key = event->key();

//    if(playersKeys.contains(key)) {
//        int playerId = playersKeys.value(key).at(0);
//        int playerMove = playersKeys.value(key).at(1);
//        emit playerKeyToggle(
//                    playerId,
//                    playerMove,
//                    true
//        );
//    }
//}

//void keyInput::keyRelease(QKeyEvent *event) {
//    int key = event->key();

//    if(playersKeys.contains(key)) {
//        int playerId = playersKeys.value(key).at(0);
//        int playerMove = playersKeys.value(key).at(1);
//        emit playerKeyToggle(
//                    playerId,
//                    playerMove,
//                    false
//        );
//    }
//}

///**
// * Player movements.
// */
//void keyInput::setPlayerKeys(int focusedPlayerId) {
//    if(focusedPlayerId == -1)
//        focusedPlayerId = 0;

//    // The key to press, {player id, direction}
//    playersKeys.insert(Qt::Key_W,       {focusedPlayerId, up});
//    playersKeys.insert(Qt::Key_A,       {focusedPlayerId, left});
//    playersKeys.insert(Qt::Key_S,       {focusedPlayerId, down});
//    playersKeys.insert(Qt::Key_D,       {focusedPlayerId, right});

//    if(focusedPlayerId == 0) {
//        // If the id of the 1st player is not a socketDescriptor
//        playersKeys.insert(Qt::Key_Up,      {1, up});
//        playersKeys.insert(Qt::Key_Left,    {1, left});
//        playersKeys.insert(Qt::Key_Down,    {1, down});
//        playersKeys.insert(Qt::Key_Right,   {1, right});
//    }
//}

//// OVERRIDE REQUIRED

///**
// * Draw the content of the article in local coordinates.
// */
//void keyInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    Q_UNUSED(painter)
//    Q_UNUSED(option)
//    Q_UNUSED(widget)
//}

///**
// * Returns the outer limits of the element as a rectangle.
// * Called by QGraphicsView to determine which regions need to be redrawn.
// */
//QRectF keyInput::boundingRect() const {
//    return QRectF(0, 0, 0, 0);
//}

///**
// * Collision detection.
// */
//QPainterPath keyInput::shape() const {
//    QPainterPath path;
//    path.addEllipse(boundingRect());
//    return path;
//}
