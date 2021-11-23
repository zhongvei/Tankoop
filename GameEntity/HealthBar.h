#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Basic.h"
#include <QGraphicsRectItem>

class HealthBar : public QGraphicsRectItem
{
Tank* tank = nullptr;

public:
    HealthBar(Tank* tank);
protected:
    void advance(int step) override;
};

#endif // HEALTHBAR_H
