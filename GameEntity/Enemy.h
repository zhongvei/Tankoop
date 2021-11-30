#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"
#include "Block.h"
#include "Basic.h"
#include "Bullet.h"
#include "../GameEngine.h"

#include <QObject>
#include <QGraphicsRotation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QList>


class GameEngine;

class Enemy: public QObject, public QTransform, public Tank
{
    Q_OBJECT
    enum class STATE{ HUNTING, RUNNING }; // the state of the enemy

private:
    int num_target;
    int turn = 0;
    double attack_scale;
    double sight_scale;
    double attack_range;
    double sight_range;
    bool random_movement = true;
    bool player_detected {false};

    GameEngine* const g;
    QTimer *timer = nullptr;
    STATE current_state = STATE::HUNTING;
    QGraphicsEllipseItem *attack_area;
    QGraphicsEllipseItem *sight_area;
    QPointF player_location;


    void stateHunting();
    void stateRunning();

public:

    /*
     *  @funct: Constructs the enemy inside the game and all of its attributes. The constructed enemy's status is
     *          affected by the current level of waves. The bigger the waves, the stronger the enemy becomes.
     *
     *  @param: g: the game engine where the enemy is active.
     *          attack_range: the attack range of the enemy in form of an ellipse with radius based on the attack_range variable.
     *          sight_range: the sight range of the enemy in form of an ellipse with radius based on the sight_range variable.
     *          size: the size of the enemy.
     *
     *  @return: N/A
     */
    Enemy(GameEngine* const g, double attack_range,double sight_range, const int& size);   

    /*
     *  @funct: Destructs the Enemy with all of its attributes and deallocates their memory.
     *
     *  @param: N/A
     *  @return: N/A
     */
    ~Enemy();

    /*
     *  @funct: Function to handle the shooting mechanism of the enemy.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void fire();

    /*
     *  @funct: Function to handle enemy movement in the edge of the window.
     *
     *  @param: N/A
     *  @return: N/A
     */
    void bounces();

    /*
     *  @funct: Function to detect all the entities inside the sight area ellipse and determine whether the player is inside
     *          the shooting range of the enemy.
     *
     *  @param: items: a QList that store all the informations regarding each entities that collides with the items variable.
     *
     *  @return: N/A
     */
    void detecting(QList <QGraphicsItem *> items);

    /*
     *  @funct: Function to calculate the distance between the entities and the enemy based on the coordinates in
     *          the type of QPointF.
     *
     *  @param: the_target: a pointer of the target's necessary information including the coordinate of it.
     *
     *  @return: the distance between the entity and the enemy in double type.
     */
    double distanceTo(GameEntity * the_target);

    /* Accessor */
    QGraphicsEllipseItem* get_attack_area() const;
    QGraphicsEllipseItem* get_sight_area() const;
    GameEntity::CLASS get_class() const override;
    int get_range() const;
    double get_attack_scale() const;
    double get_sight_scale() const;

public slots:
    /*
     *  @funct: A function that handle the enemy movement and calls the detecting function and changing the state of the enemy.
     *
     *  @param: N/A
     *  @return: N/A
     */

    void move();

};

#endif // ENEMY_H



