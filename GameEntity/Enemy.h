#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"
#include "Block.h"
#include "Basic.h"
#include "GameEngine.h"

#include <QObject>
#include <QGraphicsRotation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QVector>

class GameEngine;

class Enemy: public Tank, public QObject, public QTransform
{
    Q_OBJECT
    enum class STATE{HUNTING, RUNNING};

public:
    Enemy(double attack_range,const int& size, GameEngine* game_engine);
    QGraphicsEllipseItem* get_attack_area(){ return attack_area; }
    QGraphicsEllipseItem* get_sight_area(){ return sight_area; }
    int get_range() const { return attack_range; }
    double get_attack_scale() const { return attack_scale; }
    double get_sight_scale() const { return sight_scale; }

    void fire();
    void detecting(QList <QGraphicsItem *> items, int &detected_blocks);

    double distanceTo(GameEntity * the_target);

    ~Enemy();
    QVector<QString> EnemyNames {QString("John"), QString("Adam"), QString("Bing"), QString("Chilli")};
    QString name = EnemyNames[qrand() % 4];

    /* Enemy statistics for end game leaderboard */
//    QVector<QString> EnemyNames {QString("John"), QString("Adam"), QString("Bing"), QString("Chilli")};
//    struct enemyStats
//    {
//        Enemy* ptr = nullptr;
//        QString name = QString("");
//        int score = 0;
//    };
//    static QVector<enemyStats> cumulativeEnemyList; // vector that contains all enemies that spawns during the game
//    static QVector<Enemy*> currentEnemyList; // vector that contains current enemies in the game





public slots:
    void move();
    void cumulativeEnemyList__pushback();
    void currentEnemyList_pushback();

private:
    int num_target;
    QTimer *timer = nullptr;
    double attack_range;
    double attack_scale;
    double sight_scale;
    bool player_detected {false};
    QPointF player_location;


    STATE current_state = STATE::HUNTING;
    QGraphicsEllipseItem *attack_area;
    QGraphicsEllipseItem *sight_area;

    void stateHunting();
    //void stateRunning(QPointF *blocks_coordinate, const int &detected_blocks);

};

//QVector<enemyStats> Enemy::cumulativeEnemyList;
//QVector<Enemy*> Enemy::currentEnemyList;
#endif // ENEMY_H



