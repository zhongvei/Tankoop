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

    /*
     *  @funct: Destructs the Enemy with all of its attributes and deallocates their memory.
     *
     *  @param: N/A
     *  @return: N/A
     */
    ~Turret();

    /*
     *  @funct: Function to handle the shooting mechanism of the turret.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void fire();

    /*
     *  @funct: Function to detect all the entities inside the sight area ellipse and determine whether the enemy is inside
     *          the shooting range of the turret.
     *
     *  @param: items: a QList that store all the informations regarding each entities that collides with the items variable.
     *
     *  @return: N/A
     */
    void detecting(QList <QGraphicsItem *> items, int &detected_blocks);

    /*
     *  @funct: Function to calculate the distance between the entities and the turret based on the coordinates in
     *          the type of QPointF.
     *
     *  @param: the_target: a pointer of the target's necessary information including the coordinate of it.
     *
     *  @return: the distance between the entity and the enemy in double type.
     */

    /* Accessor */
    int get_attack_range() const { return attack_range; }
    double get_attack_scale() const { return attack_scale; }
    double distanceTo(GameEntity * the_target);
    Tank* get_creator() const;
    GameEntity::CLASS get_class() const override;
    QGraphicsEllipseItem* get_attack_area(){ return attack_area; }
    
public slots:

    /*
     *  @funct: A function that calls the detecting function and changing the state of the turret.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void move();

private:
    Tank* creator;
    QTimer *timer = nullptr;
    QPointF enemy_location;
    QGraphicsEllipseItem *attack_area;

    int num_target;
    double attack_range{};
    double attack_scale;
    bool enemy_detected {false};
    

    
};

#endif // TURRET_H
