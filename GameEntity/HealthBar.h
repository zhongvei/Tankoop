#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Basic.h"
#include <QGraphicsRectItem>

class HealthBar : public QGraphicsRectItem
{
Tank* tank = nullptr;
QGraphicsRectItem* healthPercentageRect;
QGraphicsScene* scene;

public:
    HealthBar(Tank* tank, QGraphicsScene* scene);
protected:
    void advance(int step) override;
};

#endif // HEALTHBAR_H
