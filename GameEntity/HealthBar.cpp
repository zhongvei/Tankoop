#include "HealthBar.h"
#include <QPointF>
#include "Tank.h"
#include <QDebug>

HealthBar::HealthBar(Tank* tank) : tank(tank)
{

    this->setRect(0,0,100,20);
}

void HealthBar::advance(int step)
{
    if (!step)
        return;

    // qDebug("HealthBar advance");

    QPointF healthpos;
    healthpos.setX(this->x());
    healthpos.setY(this->y());


    QPointF tankPos;
    tankPos.setX(tank->x()-25);
    tankPos.setY(tank->y()+60);
    this->setPos(tankPos);

    // TODO: Update health bar's health




    /* DO NOT DELETE
     * Archived Code:
     * Updating Health Bar location relative to Tank
     */

    //    // METHOD 1
    //    QPointF relativeCoords;
    //    // change relativeCoords to adjust how far away Health Bar is from the tank.
    //    relativeCoords = QPointF(0,70);
    //    // Update Position of HealthBar relative to position of tank + relativeCoords
    //    this->setPos(healthpos + relativeCoords - tank->mapFromScene(healthpos) );

    //    // METHOD 2
    //    // QPointF pos = this->mapToItem(tank, 0, 100);
    //    // this->setPos(pos);

    // DO NOT DELETE
}


