#include "Enemy.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include "Block.h"
#include "Basic.h"


Enemy::Enemy(double attack_range, const int& size): Tank(100,1,50,size,10,10,0,0.6,0.6,7,1,0,0), attack_range(attack_range)
{
    // const double& health, const double& health_regen, const double& max_health,
    // const int& size, const int& vx, const int& vy,const double& xp,
    // const double& attack_speed,
    // const double& bullet_speed,
    // const double& damage,
    // const int& level

    scale = attack_range/size;

    attack_area = new QGraphicsEllipseItem(0,0,attack_range,attack_range);
    attack_area->setStartAngle(90*16);
    attack_area->setPos(x() - get_size() * (get_scale()-1)/2, y() - get_size() * (get_scale()-1)/2);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);

}
double Enemy::distanceTo(QGraphicsItem * item){
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void Enemy::fire(){
    qDebug() << "ENEMY GOES PEW-PEW";
    Bullet * bullet = new Bullet(this,50,0,10,0,0);
    bullet->set_degree(this->get_degree());
    bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57))));
    scene()->addItem(bullet);

}

void Enemy::move(){
    // move enemy down

    /* Detecting the enemies */
    QList<QGraphicsItem *> spotted_items = attack_area->collidingItems();
    double closest_dist = 300;
    QPointF closest_pt = QPointF(0,0);

    for (int i = 0, n = spotted_items.size(); i < n; ++i){
        /* Enemies spotted */
        if (typeid(*(spotted_items[i])) == typeid(Block) || typeid(*(spotted_items[i])) == typeid(Basic)){
            double this_dist = distanceTo(spotted_items[i]);
            if (this_dist < closest_dist){
                closest_dist = this_dist;
                closest_pt = spotted_items[i]->pos();
            }
            num_target += 1;
        }

    }
    attack_dest = closest_pt;
    double angle_in_radians = std::atan2((attack_dest.y()-(y()+get_size()/2)),(attack_dest.x()-(x()+get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    set_degree(angle_in_degrees);

    if(num_target){
        fire();
        num_target = 0;
    }
    else{
        setPos(x(),y()+5);
    }

    attack_area->setPos(x() - get_size() * (get_scale()-1)/2, y() - get_size() * (get_scale()-1)/2);

    // destroy enemy when it goes out of the screen
    if (pos().y() > 2000){
        //decrease the health
        qDebug() << "ENEMY DELETED";
        scene()->removeItem(this);
        delete this;
    }
}
