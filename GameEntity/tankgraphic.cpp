//#include "tankgraphic.h"
//#include <QRandomGenerator>
//#include <QGraphicsScene>
//#include <QPainter>
//#include <QStyleOption>
//#include <QtMath>

////constexpr qreal Pi = M_PI;
////constexpr qreal TwoPi = 2 * M_PI;

////static qreal normalizeAngle(qreal angle)
////{
////    while (angle < 0)
////        angle += TwoPi;
////    while (angle > TwoPi)
////        angle -= TwoPi;
////    return angle;
////}

//TankGraphic::TankGraphic() : color(QRandomGenerator::global()->bounded(256),
//                                   QRandomGenerator::global()->bounded(256),
//                                   QRandomGenerator::global()->bounded(256))
//{
//    //setRotation(QRandomGenerator::global()->bounded(360 * 16));
//}

//// When the QGraphicsScene decides to advance the scene by a frame,
//// it will call QGraphicsItem::advance() on each of the items.
//void TankGraphic::advance(int step)
//{
//    if (!step)
//        return;
//}
////    QLineF lineToCenter(QPointF(0, 0), mapFromScene(0, 0));
////    if (lineToCenter.length() > 150) {
////        qreal angleToCenter = std::atan2(lineToCenter.dy(), lineToCenter.dx());
////        angleToCenter = normalizeAngle((Pi - angleToCenter) + Pi / 2);

////        if (angleToCenter < Pi && angleToCenter > Pi / 4) {
////            // Rotate left
////            angle += (angle < -Pi / 2) ? 0.25 : -0.25;
////        } else if (angleToCenter >= Pi && angleToCenter < (Pi + Pi / 2 + Pi / 4)) {
////            // Rotate right
////            angle += (angle < Pi / 2) ? 0.25 : -0.25;
////        }
////    } else if (::sin(angle) < 0) {
////        angle += 0.25;
////    } else if (::sin(angle) > 0) {
////        angle -= 0.25;
////    }

////    const QList<QGraphicsItem *> dangerMice = scene()->items(QPolygonF()
////                               << mapToScene(0, 0)
////                               << mapToScene(-30, -50)
////                               << mapToScene(30, -50));

////    for (const QGraphicsItem *item : dangerMice) {
////        if (item == this)
////            continue;

////        QLineF lineToMouse(QPointF(0, 0), mapFromItem(item, 0, 0));
////        qreal angleToMouse = std::atan2(lineToMouse.dy(), lineToMouse.dx());
////        angleToMouse = normalizeAngle((Pi - angleToMouse) + Pi / 2);

////        if (angleToMouse >= 0 && angleToMouse < Pi / 2) {
////            // Rotate right
////            angle += 0.5;
////        } else if (angleToMouse <= TwoPi && angleToMouse > (TwoPi - Pi / 2)) {
////            // Rotate left
////            angle -= 0.5;
////        }
////    }

////    if (dangerMice.size() > 1 && QRandomGenerator::global()->bounded(10) == 0) {
////        if (QRandomGenerator::global()->bounded(1))
////            angle += QRandomGenerator::global()->bounded(1 / 500.0);
////        else
////            angle -= QRandomGenerator::global()->bounded(1 / 500.0);
////    }

////    speed += (-50 + QRandomGenerator::global()->bounded(100)) / 100.0;

////    qreal dx = ::sin(angle) * 10;
////    mouseEyeDirection = (qAbs(dx / 5) < 1) ? 0 : dx / 5;

////    setRotation(rotation() + dx);
////    setPos(mapToParent(0, -(3 + sin(speed) * 3)));
////}

//QRectF TankGraphic::boundingRect() const
//{
//    qreal adjust = 0.5;
//    return QRectF(-35 - adjust, -35 - adjust,
//                  60 + adjust, 60 + adjust);
//}

//void TankGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
//{
//    painter->drawRect(-12.5,-12.5,25,60);
//    painter->setBrush(color);
//    painter->drawEllipse(-25, -25, 50, 50);

//    // Body
////    painter->setBrush(color);
////    painter->drawEllipse(-10, -20, 20, 40);

//    // Eyes
////    painter->setBrush(Qt::white);
////    painter->drawEllipse(-10, -17, 8, 8);
////    painter->drawEllipse(2, -17, 8, 8);

//    // Nose
//    //painter->setBrush(Qt::black);
//    //painter->drawEllipse(QRectF(-2, -22, 4, 4));

//    // Pupils
//    //painter->drawEllipse(QRectF(-8.0 + mouseEyeDirection, -17, 4, 4));
//    //painter->drawEllipse(QRectF(4.0 + mouseEyeDirection, -17, 4, 4));

//    // Ears
//    //painter->setBrush(scene()->collidingItems(this).isEmpty() ? Qt::darkYellow : Qt::red);
//    //painter->drawEllipse(-17, -12, 16, 16);
//    //painter->drawEllipse(1, -12, 16, 16);

//    // Tail
////    QPainterPath path(QPointF(0, 50));
////    path.cubicTo(-5, 22, -5, 22, 0, 25);
////    path.cubicTo(5, 27, 5, 32, 0, 30);
////    path.cubicTo(-5, 32, -5, 42, 0, 35);
////    painter->setBrush(Qt::NoBrush);
////    painter->drawPath(path);
//}

//// for collision detection
//QPainterPath TankGraphic::shape() const
//{
//    QPainterPath path;
//    path.addEllipse(-25, -25, 50, 50);
//    return path;
//}
