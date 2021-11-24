#include "Enemy.h"
#include "Bullet.h"
#include "Block.h"
#include "Basic.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>

Enemy::Enemy(double attack_range, const int& size): Tank(100,1,50,100,10,10,0,0.6,0.6,7,1,0,0), attack_range(attack_range)
{
    scale = attack_range/size;

    attack_area = new QGraphicsEllipseItem(attack_range/2, attack_range/2,attack_range,attack_range);
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

int reload_finish = 0;
bool reload = true;

void Enemy::fire(){
    qDebug() << "ENEMY GOES PEW-PEW";
    reload = true;
    Bullet * bullet = new Bullet(this,50,0,10,0,0);
    bullet->set_degree(this->get_degree());
    bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57))));

    QTransform transform;
    //double dx = 0; double dy = 0;
    //transform.translate(dx,dy);
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    //transform.translate(-dx,-dy);
    this->setTransform(transform);

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
    //not accurate shots
    double angle_in_radians = std::atan2((attack_dest.y()-(y()+get_size()/2)),(attack_dest.x()-(x()+get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    set_degree(angle_in_degrees);

    //basic->setTransformOriginPoint(QPoi
    if(reload){
        reload_finish += 1;
        if (reload_finish == 10){
            reload = false;
            reload_finish = 0;
        }
    }
    if(num_target & !reload){
        fire();
        num_target = 0;
    }
    else if(!reload){
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
