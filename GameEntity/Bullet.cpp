#include "Bullet.h"
#include "Block.h"
//#include "Enemy.h"
#include "Basic.h"

#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

//bullet has no health, max health, health_regen and xp
Bullet::Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy):
    GameEntity(0,0,0,size,vx,vy,0,0), damage(damage), degree(degree), tank(tank)
{
    setRect(0,0,size,size);
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(1000/60);
}


double Bullet::get_damage() const { return damage; }

void Bullet::move(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0, n = colliding_items.size(); i < n; ++i){
                if (typeid(*(colliding_items[i])) == typeid(Block)){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Block *the_block = dynamic_cast<Block*>(colliding_items[i]);
                    the_block->set_health(the_block->get_health()-get_damage());

                    /* Delete the Block if the heath is less than or equal to zero */
                    if(the_block->get_health() <= 0){
                       scene()->removeItem(colliding_items[i]);
                       tank->set_xp(tank->get_xp()+the_block->get_xp());
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (typeid(*(colliding_items[i])) == typeid(Enemy) && typeid(*tank) == typeid(Basic)){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Enemy *the_enemy = dynamic_cast<Enemy*>(colliding_items[i]);
                    the_enemy->set_health(the_enemy->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_enemy->get_health() <= 0){
                       scene()->removeItem(colliding_items[i]);
                       scene()->removeItem(the_enemy->get_health_bar());
                       tank->set_xp(tank->get_xp()+the_enemy->get_xp());
                       enemyStats temp = {the_enemy, the_enemy->name,int(the_enemy->get_xp())}; // store enemy statistics in enemyList
                       Enemy::cumulativeEnemyList.push_back(temp);
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (typeid(*(colliding_items[i])) == typeid(Basic) && typeid(*tank) == typeid(Enemy)){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Basic *player = dynamic_cast<Basic*>(colliding_items[i]);
                    player->set_health(player->get_health()-get_damage());
                    qDebug()<<"HIT THE PLAYER";
                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }

            }

            /* Set The Movement of the Bullet */
            setPos(x()+(this->get_vx()*10*cos(this->degree/57)),y()+(this->get_vy()*10*sin(this->degree/57)));
            if (pos().y() + rect().height() < 0){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().x() + rect().height() < 0){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().y() + rect().height() > 2000){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().x() + rect().height() > 2000){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
}
