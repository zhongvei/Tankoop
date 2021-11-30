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

//bullet has no health, max health, health_regen, xp and level
Bullet::Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy,
               GameEngine* game_engine):
    GameEntity(0,0,0,size,vx,vy,0,0), damage(damage), degree(degree), tank(tank), game_engine(game_engine)
{
    setRect(0,0,size,size); //setting the size of the bullet in the GameWindow

    timer = new QTimer();   //setting up the move timer for the bullet
    timer->start(1000/60);  //which is 60 fps

    //connectors for the function to be called
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(this, SIGNAL(enemyDiedSignal(QString, int)), game_engine, SLOT(enemyDied(QString, int)));
}

Bullet::~Bullet() {
    delete timer;
}

double Bullet::get_degree() const {return degree;}
double Bullet::get_damage() const { return damage; }
GameEntity::CATEGORY Bullet::get_category() const {return GameEntity::CATEGORY::BULLET;}
Tank* Bullet::get_tank() const {return tank;}

void Bullet::move(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0, n = colliding_items.size(); i < n; ++i){
                //dynamic casting the colliding items so that the type, category can be identified
                GameEntity* the_thing =  dynamic_cast<GameEntity*>(colliding_items[i]);
                if(the_thing != nullptr) {
                    if (the_thing->get_category() == GameEntity::CATEGORY::BLOCK && tank->get_class() == GameEntity::CLASS::TURRET){
                        //the_thing would be a Block in this case and the Bullet is fire by the turret
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        // Delete the Block if the heath is less than or equal to zero
                        if(the_thing->get_health() <= 0){
                           //finding out the Tank that creates the Turret
                           Turret* the_turret = dynamic_cast<Turret*>(tank);
                           the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_thing->get_xp());
                           delete the_thing;
                           colliding_items[i] = nullptr;
                           the_thing = nullptr;
                        }

                        // Delete the Bullet as well
                        scene()->removeItem(this);
                        delete this;
                        return;
                    }
                    else if (the_thing->get_class() == GameEntity::CLASS::ENEMY && this->tank->get_class() == GameEntity::CLASS::TURRET){
                        //the_thing would be a Enemy in this case and the bullet hits a Turret
                        //finding out the Tank that creates the Turret
                        Turret* the_turret = dynamic_cast<Turret*>(tank);
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        //Delete the Enemy if its health is less than or equal to zero
                        if(the_thing->get_health() <= 0){
                           Enemy* the_enemy= dynamic_cast<Enemy*>(the_thing);
                           the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_thing->get_xp());
                           emit enemyDiedSignal(the_enemy->get_name(), the_enemy->get_xp());
                           delete the_thing;
                           colliding_items[i] = nullptr;
                           the_thing = nullptr;
                        }

                        // Delete the Bullet as well
                        scene()->removeItem(this);
                        delete this;
                        return;
                    }
                    else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK){
                        //the_thing would be a block in this case
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        // Delete the Block if the heath is less than or equal to zero
                        if(the_thing->get_health() <= 0){
                           tank->set_xp(tank->get_xp()+the_thing->get_xp());
                           scene()->removeItem(the_thing);
                           delete the_thing;
                           colliding_items[i] = nullptr;
                           the_thing = nullptr;
                        }

                        //Delete the Bullet
                        scene()->removeItem(this);
                        delete this;
                        return;
                    }
                    else if (the_thing->get_class() == GameEntity::CLASS::ENEMY && tank->get_class() == GameEntity::CLASS::BASIC){
                        //the_thing will be the enemy and the bullet is fire by a player
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        // Delete the Enemy if its health is less than or equal to zero
                        if(the_thing->get_health() <= 0){
                           tank->set_xp(tank->get_xp()+the_thing->get_xp());
                           Enemy* the_enemy= dynamic_cast<Enemy*>(colliding_items[i]);
                           emit enemyDiedSignal(the_enemy->get_name(), the_thing->get_xp());
                           delete the_thing;
                           the_thing = nullptr;
                           colliding_items[i] = nullptr;
                        }

                        //Delete the bullet
                        scene()->removeItem(this);
                        delete this;
                        return;
                    }
                    else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::BASIC && this->tank->get_class() == GameEntity::CLASS::ENEMY){
                        // the_thing would be a player in this case and is fire by an enemy
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        //Deleting the bullet
                        scene()->removeItem(this);
                        delete this;
                        return;
                    } else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::WALL && tank->get_class() == GameEntity::CLASS::ENEMY){
                        //the_thing would be a wall in this case and is fire by the enemy
                        the_thing->set_health(the_thing->get_health()-get_damage());

                        // Delete the Enemy if its health is less than or equal to zero
                        if(the_thing->get_health() <= 0){
                           Enemy* the_enemy= dynamic_cast<Enemy*>(colliding_items[i]);
                           emit enemyDiedSignal(the_enemy->get_name(), the_enemy->get_xp());
                           scene()->removeItem(the_thing);
                           delete the_thing;
                           the_thing = nullptr;
                           colliding_items[i]= nullptr;
                        }

                        //Delete the bullet
                        scene()->removeItem(this);
                        delete this;
                        return;
                    }
                }

            }

            // Set The Movement for the Bullet
            setPos(x()+(this->get_vx()*10*cos(this->degree/57)),y()+(this->get_vy()*10*sin(this->degree/57)));

            // Delete the bullet if the bullet touched the GameWindow
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
            if (pos().y() + rect().height() > GameWindow::WINDOW_HEIGHT){
                delete this;
                return;
            }
            if (pos().x() + rect().height() > GameWindow::WINDOW_WIDTH){
                delete this;
                return;
            }
}
