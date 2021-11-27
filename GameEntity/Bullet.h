#ifndef BULLET_H
#define BULLET_H

#include "Tank.h"
#include "GameEntity.h"
#include "Enemy.h"
#include "../GameEngine.h"

#include <QObject>
//struct enemyStats;
//enemyStats p;
//QVector<enemyStats> Enemy::cumulativeEnemyList;
//QVector<Enemy*> Enemy::currentEnemyList;

class Bullet : public QObject, public GameEntity
{
    Q_OBJECT
public:        
    Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy, GameEngine* game_engine);
    double get_damage() const;
    double get_degree() const {return degree;}
    void set_degree (double degree) {this->degree = degree;}

    struct enemyStats
    {
        Enemy* ptr = nullptr;
        QString name = QString("");
        int score = 0;
    };

private:
    double damage;
    double degree;
    Tank* tank;
    GameEngine* game_engine;

//    QVector<QString> EnemyNames {QString("John"), QString("Adam"), QString("Bing"), QString("Chilli")};
//    // how to put in Enemy.h ?

public slots:
    void move();
signals:
    void enemyDies(Enemy* enemy);
};

#endif // BULLET_H
