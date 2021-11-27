#ifndef TURRET_H
#define TURRET_H

#include "Tank.h"
#include "Basic.h"

#include <QObject>
#include <QTransform>
#include <QGraphicsEllipseItem>

//class Tank;
class Basic;


class Turret: public QObject, public QTransform, public Tank
{
    Q_OBJECT
public:

    Turret(double attack_range, const int& size, Tank* creator);
    ~Turret();
    QGraphicsEllipseItem* get_attack_area(){ return attack_area; }
    int get_attack_range() const { return attack_range; }
    double get_attack_scale() const { return attack_scale; }

    void fire();
    void bounces();
    void detecting(QList <QGraphicsItem *> items, int &detected_blocks);
    Tank* get_creator() const;
    double distanceTo(GameEntity * the_target);
    GameEntity::CLASS get_class() const override;
public slots:
    void move();
private:
    Tank* creator;
    int num_target;
    QTimer *timer = nullptr;
    double attack_range{};

    double attack_scale;
    bool enemy_detected {false};
    QPointF enemy_location;

    QGraphicsEllipseItem *attack_area;
};

#endif // TURRET_H
