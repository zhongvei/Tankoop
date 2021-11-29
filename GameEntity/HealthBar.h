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
    HealthBar(Tank* tank, QGraphicsScene* scene);
    ~HealthBar();
protected:
    void advance(int step) override;
};

#endif // HEALTHBAR_H
