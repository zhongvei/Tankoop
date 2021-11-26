#include "Enemy.h"
#include "Bullet.h"
#include "Block.h"

#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>


Enemy::Enemy(double attack_range, const int& size): Tank(200,1,200,size,10,10,0,0.6,0.6,7,1,0,0), attack_range(attack_range)
{
    attack_scale = attack_range/size;
    sight_scale = 800/size; // change 800 to variable later

    attack_area = new QGraphicsEllipseItem(0,0,attack_range,attack_range);
    //attack_area->setStartAngle(90*16);
    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);

    sight_area = new QGraphicsEllipseItem(0,0,800,800); // change the value of sight_area to non const later
    //attack_area->setStartAngle(90*16);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);

}

Enemy::~Enemy(){
    delete attack_area;
    delete sight_area;
    //delete timer
}


double Enemy::distanceTo(Block * item){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(item->x() + item->get_size()/2, item->y() + item->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

double Enemy::distanceTo(Basic * basic){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(basic->x() + basic->get_size()/2, basic->y() + basic->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

//int reload_finish = 0;
//bool reload = true;

void Enemy::fire(){
    QTransform transform;
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    //transform.translate(-dx,-dy);
    this->setTransform(transform);

    if(!this->get_reload_status()){
        change_reload_status();
        qDebug() << "ENEMY GOES PEW-PEW";
        Bullet * bullet = new Bullet(this,50,0,10,0.6,0.6);
        bullet->set_degree(this->get_degree());
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y() +(this->get_size()/2*(1+sin(bullet->get_degree()/57))));
        scene()->addItem(bullet);
    }
}

template <typename T>
void findClosestDistance(T a, QList<QGraphicsItem *> item, double this_dist, double &closest_dist, int i, QPointF &closest_pt, double &closest_size){
    if (this_dist < closest_dist){
        closest_dist = this_dist;
        closest_pt = item[i]->pos();
        closest_size = a->get_size();
    }
}


void Enemy::detecting(){
    QList<QGraphicsItem *> spotted_items = sight_area->collidingItems();
    QList<QGraphicsItem *> shootable_items = attack_area->collidingItems();

    double closest_dist = 800;
    QPointF closest_pt = QPointF(0,0);
    double closest_size = 0;

    for (int i = 0, n = spotted_items.size(); i < n; ++i){
        /* Enemies spotted */
        if(!player_detected){
            if (typeid(*(spotted_items[i])) == typeid(Block)){
                bool in_shooting_range = false;
                for (int j = 0, n = shootable_items.size(); j < n; ++j){
                    if (spotted_items[i] == shootable_items[j]){
                        in_shooting_range = true;
                        break;
                    }
                }
                if(in_shooting_range){
                    num_target += 1;
                    //qDebug() << "BLOCK DETECTED INSIDE SHOOTING RANGE";
                }
                Block *the_target = dynamic_cast<Block*>(spotted_items[i]);
                double this_dist = distanceTo(the_target);
                findClosestDistance(the_target,spotted_items,this_dist,closest_dist, i,closest_pt,closest_size);

            }
        }

        if (typeid(*(spotted_items[i])) == typeid(Basic)){
            bool in_shooting_range = false;
            for (int j = 0, n = shootable_items.size(); j < n; ++j){
                if (spotted_items[i] == shootable_items[j]){
                    in_shooting_range = true;
                    break;
                }
            }
            if(in_shooting_range){
                num_target += 1;
            }
            qDebug() << "PLAYER DETECTED";
            Basic *the_target = dynamic_cast<Basic*>(spotted_items[i]);
            double this_dist = distanceTo(the_target);
            findClosestDistance(the_target,spotted_items,this_dist,closest_dist, i,closest_pt,closest_size);
            player_detected = true;
            break;
        }
        else if(i == n-1){
            player_detected = false;
        }

    }

    double angle_in_radians = std::atan2((closest_pt.y() + closest_size/2 -(y()+get_size()/2)),(closest_pt.x() + closest_size/2 -(x()+get_size()/2))); //ricat
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    set_degree(angle_in_degrees);

}


void Enemy::stateHunting(){
    if(this->get_reload_status()){
        this->set_reload_finish(this->get_reload_finish() + 1);
        if (get_reload_finish() == 10){
            this->change_reload_status();
            this->set_reload_finish(0);
        }
    }

    if(num_target){
        fire();
        num_target = 0;
    }
    else{
        setPos(x()+(10*cos(get_degree()/57)),y()+(10*sin(get_degree()/57)));
    }

}

void Enemy::stateRunning(){
    setPos(x()+(10*cos((get_degree()+180)/57)),y()+(10*sin((get_degree()+180)/57)));
}

void Enemy::move(){

    /* Detecting the enemies */
    detecting();
    if(get_health() >= get_max_health()*0.4){
        current_state = STATE::HUNTING;
    }
    else if(player_detected && get_health() < get_max_health() * 0.4){
        current_state = STATE::RUNNING;
    }
    else if(!player_detected && get_health() < get_max_health() * 0.4){
        current_state = STATE::HUNTING;
    }

    switch(current_state){
        case STATE::HUNTING:
            stateHunting(); break;
        case STATE::RUNNING:
            stateRunning(); break;
    }


    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);


    // destroy enemy when it goes out of the screen
    if (pos().y() > 2000){
        //decrease the health
        qDebug() << "ENEMY DELETED";
        scene()->removeItem(this);
        delete this;
    }
}
