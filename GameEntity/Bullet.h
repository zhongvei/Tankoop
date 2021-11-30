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

    /*
    *  @funct:  constructor for the Bullet
    *
    *  @param:  tank: the pointer to the Tank that shoots(create) the bullet, damage: the damage for the Bullet, size: the size for the Bullet
    *  @param:  vx: the movement speed in the x axis for the Bullet, vy: the movement speed in the y axis for the Bullet
    *  @param:  game_engine: the pointer to the GameEngine that the current Bullet is created at
    *  @return: N/A     
    */
    Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy,
           GameEngine* const game_engine);
    /*
    *  @funct:  the destructor of the Bullet, remove the dynamic allocated objects
    *
    *  @param:  N/A
    *  @return: N/A
    */
    ~Bullet();

    /* Accessor */
    /*
    *  @funct:  get the damage of the Bullet
    *
    *  @param:  N/A   
    *  @return: double: the damage of the Bullet
    */
    double get_damage() const;

    /*
    *  @funct:  get the travelling degree of the of the Bullet
    *
    *  @param:  N/A   
    *  @return: double: the travelling degree of the of the Bullet
    */
    double get_degree() const;

    /*
    *  @funct:  get the pointer to the Tank that creates the tank
    *  @param:  N/A   
    *  @return: Tank*: the pointer to the Tank that creates the tank
    */
    Tank* get_tank() const;

    /* Mutators */
    /*
    *  @funct:  get the pointer to the Tank that creates the tank
    *
    *  @param:  N/A   
    *  @return: Tank*: the pointer to the Tank that creates the tank
    */
    void set_degree (double degree) {this->degree = degree;}

    /*
    *  @funct:  get the GameEntity category type, which is GameEntity::CATEGORY::BULLET in this case
    *
    *  @param:  N/A
    *  @return: GameEntitiy::CATEGORY: the GameEntity category type, which is GameEntity::CATEGORY::BULLET in this case      
    */
    GameEntity::CATEGORY get_category() const override;

private:
    double damage{};
    double degree{};
    Tank* tank{};
    GameEngine* const game_engine{};
    QTimer* timer{};

public slots:
    /*
    *  @funct:  the function that is being repeated called to update and move the bullet
    *
    *  @param:  N/A
    *  @return: N/A      
    */
    void move();

signals:
    /*
    *  @funct:  the signal that is emitted for the case where a bullet destroy an enemy
    *
    *  @param:  name: the name of the enemy, score: the score of the enemy, which is the total exp for the enemy
    *  @return: N/A      
    */
    void enemyDiedSignal(QString name, int score);
    
};

#endif // BULLET_H
