#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Tank.h"
#include <QGraphicsRectItem>

class Tank;

class HealthBar : public QGraphicsRectItem
{
private:
    Tank* tank = nullptr;
    QGraphicsRectItem* healthPercentageRect;
    QGraphicsScene* scene;

public:
    /*
    *  @funct:  the constructor for the Tank, in protected type so that no Tank can be created directly
    *
    *  @param:  tank: the tank which the Healthbar would be displayed on, scene: the scene which the HealthBar will be added to
    *  @return: N/A     
    */
    HealthBar(Tank* tank, QGraphicsScene* scene);

    /*
    *  @funct:  the destructor for Healthbar to remove dynamic allocated objects
    *
    *  @param:  N/A
    *  @return: N/A     
    */
    ~HealthBar();

protected:
    /*
    *  @funct:  an override function from QGraphicsRectItem such that this function is being repetedly called by the GameEngine
    *
    *  @param:  step: the phase of the function, step = 0 would not run the function body
    *  @return: N/A     
    */
    void advance(int step) override;
};

#endif // HEALTHBAR_H
