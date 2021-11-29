#ifndef BULLET_H
#define BULLET_H

#include "Tank.h"
#include "GameEntity.h"
#include "../GameEngine.h"

#include <QObject>
#include <QString>
#include <QMediaPlayer>

class GameEngine;

class Bullet : public QObject, public GameEntity
{
    Q_OBJECT
public:        
    Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy,
           GameEngine* const game_engine);
    double get_damage() const;
    double get_degree() const {return degree;}
    void set_degree (double degree) {this->degree = degree;}
    Tank* get_tank() const;
    GameEntity::CATEGORY get_category() const override;

private:
    double damage;
    double degree;
    Tank* tank;
    GameEngine* const game_engine;
    //QMediaPlayer* music = new QMediaPlayer();



public slots:
    void move();
signals:
    void enemyDiedSignal(QString name, int score);
};

#endif // BULLET_H
