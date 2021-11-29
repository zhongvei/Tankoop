#include "Bullet.h"
#include "Block.h"
#include "Enemy.h"
#include "Basic.h"
#include "Wall.h"
#include "Turret.h"

#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

//bullet has no health, max health, health_regen and xp
Bullet::Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy,
               GameEngine* const game_engine):
    GameEntity(0,0,0,size,vx,vy,0,0), damage(damage), degree(degree), tank(tank), game_engine(game_engine)
{
    setRect(0,0,size,size);
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(1000/60);

    connect(this, SIGNAL(enemyDiedSignal(QString, int)), game_engine, SLOT(enemyDied(QString, int)));

}

GameEntity::CATEGORY Bullet::get_category() const {return GameEntity::CATEGORY::BULLET;}

double Bullet::get_damage() const { return damage; }
Tank* Bullet::get_tank() const {return tank;}

void Bullet::move(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0, n = colliding_items.size(); i < n; ++i){
                GameEntity* the_thing =  dynamic_cast<GameEntity*>(colliding_items[i]);
                if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK && tank->get_class() == GameEntity::CLASS::TURRET){
                    /* Removing both the bullet and the block from the screen when colliding */
                    /* the_thing would be a block in this case*/
                    the_thing->set_health(the_thing->get_health()-get_damage());

                    /* Delete the Block if the heath is less than or equal to zero */
                    if(the_thing->get_health() <= 0){
                       Turret* the_turret = dynamic_cast<Turret*>(tank);
                       the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_thing->get_xp());
                       delete the_thing;
                       colliding_items[i] = nullptr;
                    }

                    /* Deleting both the Bullet */
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::ENEMY && this->tank->get_class() == GameEntity::CLASS::TURRET){
                    /* the_thing would be an enemy in this case*/
                    /* Removing both the bullet and the block from the screen when colliding */
                    Turret* the_turret = dynamic_cast<Turret*>(tank);
                    the_thing->set_health(the_thing->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_thing->get_health() <= 0){
                       Enemy* the_enemy= dynamic_cast<Enemy*>(the_thing);
                       the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_thing->get_xp());
                       emit enemyDiedSignal(the_enemy->get_name(), the_enemy->get_xp());
                       delete the_thing;
                       colliding_items[i] = nullptr;
                       the_thing = nullptr;
                    }
                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK){
                    /* the_thing would be a block in this case*/
                    /* Removing both the bullet and the block from the screen when colliding */
                    the_thing->set_health(the_thing->get_health()-get_damage());
                    /* Delete the Block if the heath is less than or equal to zero */
                    if(the_thing->get_health() <= 0){
                       tank->set_xp(tank->get_xp()+the_thing->get_xp());
                       scene()->removeItem(the_thing);
                       delete the_thing;
                       colliding_items[i] = nullptr;
                       the_thing = nullptr;
                    }

                    /* Delete the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::ENEMY && tank->get_class() == GameEntity::CLASS::BASIC){
                    /* the_thing would be an enemy in this case*/
                    /* Removing both the bullet and the block from the screen when colliding */
                    the_thing->set_health(the_thing->get_health()-get_damage());
                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_thing->get_health() <= 0){

                       tank->set_xp(tank->get_xp()+the_thing->get_xp());
                       //DELETING THE ENEMY FROM SCENE IS RUN IN THE DESTRUCTOR
                       Enemy* the_enemy= dynamic_cast<Enemy*>(colliding_items[i]);
                       emit enemyDiedSignal(the_enemy->get_name(), the_thing->get_xp());
                       delete the_thing;
                       the_thing = nullptr;
                       colliding_items[i] = nullptr;
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::BASIC && this->tank->get_class() == GameEntity::CLASS::ENEMY){
                    /* the_thing would be a player in this case*/
                    /* Removing both the bullet and the block from the screen when colliding */
                    the_thing->set_health(the_thing->get_health()-get_damage());
                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                } else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::WALL && tank->get_class() == GameEntity::CLASS::ENEMY){
                    /* the_thing would be a wall in this case*/
                    /* Removing both the bullet and the block from the screen when colliding */
                    the_thing->set_health(the_thing->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_thing->get_health() <= 0){
                       Enemy* the_enemy= dynamic_cast<Enemy*>(colliding_items[i]);
                       emit enemyDiedSignal(the_enemy->get_name(), the_enemy->get_xp());
                       scene()->removeItem(the_thing);
                       delete the_thing;
                       the_thing = nullptr;
                       colliding_items[i]= nullptr;
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
            }

            /* Set The Movement of the Bullet */
            setPos(x()+(this->get_vx()*10*cos(this->degree/57)),y()+(this->get_vy()*10*sin(this->degree/57)));
            if (pos().y() + rect().height() < 0){
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().x() + rect().height() < 0){
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().y() + rect().height() > 2000){
                delete this;
                return;
            }
            if (pos().x() + rect().height() > 2000){
                delete this;
                return;
            }
}
