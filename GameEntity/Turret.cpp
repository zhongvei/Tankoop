#include "Turret.h"
#include "Tank.h"
#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"

#include <QTimer>

Turret::Turret( double attack_range, const int& size,Tank* creator):
    Tank(200,1,200,size,10,10,0,0.6,0.6,7,1,0,0), creator(creator), attack_range(attack_range)
{
    attack_scale = attack_range/size;

    attack_area = new QGraphicsEllipseItem(0,0,attack_range,attack_range);
    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);


    // make/connect a timer to move() the enemy every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}
Turret::~Turret() {
    delete attack_area;
    QList<QGraphicsItem *> list = scene()->items();
    for(int i = 0; i < list.size(); i++) {
        GameEntity* the_thing =  dynamic_cast<GameEntity*>(list[i]);
        if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BULLET) {
            Bullet* the_bullet= dynamic_cast<Bullet*>(list[i]);
            if(the_bullet->get_tank() == this) {
                delete the_bullet;
            }
        }
    }
    timer->stop();
}

double Turret::distanceTo(GameEntity * basic){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(basic->x() + basic->get_size()/2, basic->y() + basic->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

void Turret::fire(){
    QTransform transform;
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    //transform.translate(-dx,-dy);
    this->setTransform(transform);

    if(!this->get_reload_status()){
        change_reload_status();
        Bullet * bullet = new Bullet(this,30,0,10,0.6,0.6);
        bullet->set_degree(this->get_degree());
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))-bullet->get_size()/2),y() +(this->get_size()/2*(1+sin(bullet->get_degree()/57)))-bullet->get_size()/2);
        scene()->addItem(bullet);
    }
}

GameEntity::CLASS Turret::get_class() const {return GameEntity::CLASS::TURRET;}

template <typename T>
void findClosestDistance(T a, double this_dist, double &closest_dist, QPointF &closest_pt, double &closest_size){
    if (this_dist < closest_dist){
        closest_dist = this_dist;
        closest_pt = a->pos();
        closest_size = a->get_size();
    }
}


void Turret::detecting(QList<QGraphicsItem *> items, int &detected_blocks){

    double closest_dist = 800;
    QPointF closest_pt = QPointF(0,0);
    double closest_size = 0;

    for (int i = 0, n = items.size(); i < n; ++i){
        GameEntity* the_thing =  dynamic_cast<GameEntity*>(items[i]);
        if (the_thing != nullptr && (the_thing->get_class() == GameEntity::CLASS::ENEMY  || the_thing->get_category() == GameEntity::CATEGORY::BLOCK)){
            detected_blocks++;
            if(!enemy_detected){
                if( (the_thing->x() > x() - attack_range/2 && the_thing->x() < x() + attack_range/2) &&
                    (the_thing->y() > y() - attack_range/2 && the_thing->y() < y() + attack_range/2)){
                    num_target += 1;
                }

            }

            GameEntity *the_target = dynamic_cast<GameEntity*>(items[i]);
            double this_dist = distanceTo(the_target);
            findClosestDistance(the_target,this_dist,closest_dist,closest_pt,closest_size);

            if(the_target!= nullptr && the_target->get_class() == GameEntity::CLASS::BASIC){
                enemy_detected = true;
                closest_pt = the_target->pos();
                closest_size = the_target->get_size();
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
                    num_target = 1;
                }
                break;
            }
        }
        else if(i == n-1){
            enemy_detected = false;
        }
    }

    if(closest_pt.x() && closest_pt.y()){
        double angle_in_radians = std::atan2((closest_pt.y() + closest_size/2 -(y()+get_size()/2)),(closest_pt.x() + closest_size/2 -(x()+get_size()/2))); //ricat
        double angle_in_degrees = (angle_in_radians / M_PI) * 180;

        set_degree(angle_in_degrees);
    }
}

void Turret::move(){

    QList<QGraphicsItem *> spotted_items = attack_area->collidingItems();
    int detected_blocks = 0;
    detecting(spotted_items, detected_blocks);


    if(num_target){
        fire();
        num_target = 0;
    }
    if(this->get_reload_status()){
        this->set_reload_finish(this->get_reload_finish() + 1);
        if (get_reload_finish() == 10){
            this->change_reload_status();
            this->set_reload_finish(0);
        }
    }
}

Tank* Turret::get_creator() const {return creator;}

