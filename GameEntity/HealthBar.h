#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsRectItem>
#include "Basic.h"

class HealthBar : public QGraphicsRectItem
{
Tank* tank = nullptr;

public:
    HealthBar(Tank* tank);
protected:
    void advance(int step) override;
};

#endif // HEALTHBAR_H
