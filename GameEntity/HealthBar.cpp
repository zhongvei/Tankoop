#include "HealthBar.h"
#include "Tank.h"

#include <QPointF>
#include <QDebug>
#include <QGraphicsRectItem>

//the constructor for the HealthBar
HealthBar::HealthBar(Tank* tank, QGraphicsScene* scene) : tank(tank), scene(scene)
{
    this->setRect(0,0,80,18);
    healthPercentageRect = new QGraphicsRectItem(this);
    healthPercentageRect->setRect(0,0,100,20);
    healthPercentageRect->setBrush(Qt::green);
    scene->addItem(healthPercentageRect);
}

//the destuctor for the HealthBar
HealthBar::~HealthBar() {
    scene->removeItem(healthPercentageRect);
    delete healthPercentageRect;
    healthPercentageRect = nullptr;
}

void HealthBar::advance(int step)
{
    if (!step)
        return;

    QPointF tankPos;
    tankPos.setX(tank->x()+ tank->get_size()/100 * 20);
    tankPos.setY(tank->y()+ tank->get_size()/100 * 100);
    this->setPos(tankPos);

    // TODO: Update health bar's health
    double health = tank->get_health();
    double max_health = tank->get_max_health();
    double health_percentage = health/max_health;
    if(tank->get_health() < tank->get_max_health()) {
        tank->set_health(tank->get_health() + tank->get_health_regen()*0.05);
    }
    if (health_percentage<=0) {health_percentage=0;}

    healthPercentageRect->setRect(this->x(),this->y(),80*health_percentage,18); // change 80 if health_bar width is changed

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


