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



double Enemy::distanceTo(GameEntity * basic){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(basic->x() + basic->get_size()/2, basic->y() + basic->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

int reload_finish = 0;
bool reload = true;

void Enemy::fire(bool &reload){
    QTransform transform;
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    //transform.translate(-dx,-dy);
    this->setTransform(transform);

    if(!reload){
        reload = true;
        qDebug() << "ENEMY GOES PEW-PEW";
        Bullet * bullet = new Bullet(this,50,0,10,0.6,0.6);
        bullet->set_degree(this->get_degree());
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y() +(this->get_size()/2*(1+sin(bullet->get_degree()/57))));
        scene()->addItem(bullet);
    }




}

template <typename T>
void findClosestDistance(T a, double this_dist, double &closest_dist, QPointF &closest_pt, double &closest_size){
    if (this_dist < closest_dist){
        closest_dist = this_dist;
        closest_pt = a->pos();
        closest_size = a->get_size();
    }
}


void Enemy::detecting(QList<QGraphicsItem *> items, QPointF *blocks_coordinate, int &detected_blocks){

    double closest_dist = 800;
    QPointF closest_pt = QPointF(0,0);
    double closest_size = 0;

    for (int i = 0, n = items.size(); i < n; ++i){
        /* Enemies spotted */
        if (typeid(*(items[i])) == typeid(Basic) || typeid(*(items[i])) == typeid(Block)){

            blocks_coordinate[detected_blocks] = items[i]->pos();
            detected_blocks++;
            if(!player_detected){
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
                    num_target += 1;
                }
            }

            GameEntity *the_target = dynamic_cast<GameEntity*>(items[i]);
            double this_dist = distanceTo(the_target);
            findClosestDistance(the_target,this_dist,closest_dist,closest_pt,closest_size);

            if(typeid(*(items[i])) == typeid(Basic)){
                player_detected = true;
                closest_pt = items[i]->pos();
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
                    num_target = 1;
                }
                break;
            }


        }
        else if(i == n-1){
            player_detected = false;
        }
//        if (typeid(*(items[i])) == typeid(Basic)){
//            blocks_coordinate[detected_blocks] = items[i]->pos();
//            detected_blocks++;
//            if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
//                num_target += 1;
//            }

//            GameEntity *the_target = dynamic_cast<GameEntity*>(items[i]);
//            double this_dist = distanceTo(the_target);
//            findClosestDistance(the_target,this_dist,closest_dist,closest_pt,closest_size);
//            player_detected = true;
//            break;
//        }


//        if (typeid(*(items[i])) == typeid(Block)){
//            blocks_coordinate[detected_blocks] = items[i]->pos();
//            detected_blocks++;

//            if(!player_detected){
//                if((items[i]->x() > x() - attack_range && items[i]->x() < x() + attack_range) && (items[i]->y() > y() - attack_range && items[i]->y() < y() + attack_range)){
//                    num_target += 1;
//                    //qDebug() << "BLOCK DETECTED INSIDE SHOOTING RANGE";
//                }

//            }
//            GameEntity *the_target = dynamic_cast<GameEntity*>(items[i]);
//            double this_dist = distanceTo(the_target);
//            findClosestDistance(the_target,this_dist,closest_dist,closest_pt,closest_size);
//        }
//        else if(i == n-1){
//            player_detected = false;
//        }


    }

    if(closest_pt.x() && closest_pt.y()){
        double angle_in_radians = std::atan2((closest_pt.y() + closest_size/2 -(y()+get_size()/2)),(closest_pt.x() + closest_size/2 -(x()+get_size()/2))); //ricat
        double angle_in_degrees = (angle_in_radians / M_PI) * 180;

        set_degree(angle_in_degrees);
    }
    else{
        // random movement
    }

}


void Enemy::stateHunting(){
    if(reload){
        reload_finish += 1;
        if (reload_finish == 10){
            reload = false;
            reload_finish = 0;
        }
    }

    if(num_target){
        fire(reload);
        num_target = 0;
    }
    else{
        setPos(x()+(10*cos(get_degree()/57)),y()+(10*sin(get_degree()/57)));
    }


}

void Enemy::whereToMove(QPointF *running_location, int size){


}

void Enemy::stateRunning(QPointF *blocks_coordinate, const int &detected_blocks){
    double angle_in_radians = std::atan2((player_location.y() + 30/2 -(y()+get_size()/2)),(player_location.x() + 30/2 -(x()+get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
    double player_degree = angle_in_degrees;
    int quadrant = 0;
    if(-179 <= player_degree && player_degree < -90){
        quadrant = 2;
    }
    else if (90 < player_degree && player_degree <= 180){
        quadrant = 3;
    }

    int num_possible_running_location = 0;
    QPointF *max_possible_running_location = new QPointF [detected_blocks];
    for(int i = 0; i < detected_blocks; i++){
        angle_in_radians = std::atan2((blocks_coordinate[i].y() + 30/2 -(y()+get_size()/2)),(blocks_coordinate[i].x() + 30/2 -(x()+get_size()/2)));
        angle_in_degrees = (angle_in_radians / M_PI) * 180;

        if(quadrant == 2){
            if(angle_in_degrees < 180){
                angle_in_degrees -= 360;
            }
        }
        else if(quadrant == 3){
            if(angle_in_degrees < 0){
                angle_in_degrees += 360;
            }
        }
        if(angle_in_degrees < (player_degree - 90) || angle_in_degrees > (player_degree + 90) ){
            max_possible_running_location[num_possible_running_location] = blocks_coordinate[i];
            num_possible_running_location++;
        }

    }
    qDebug() << num_possible_running_location;
    //whereToMove(max_possible_running_location, num_possible_running_location);
    delete[] max_possible_running_location;

    //setPos(x()+(10*cos((get_degree()+180)/57)),y()+(10*sin((get_degree()+180)/57)));
}

void Enemy::move(){

    /* Detecting the enemies */
    QList<QGraphicsItem *> spotted_items = sight_area->collidingItems();
    QPointF *blocks_coordinate = new QPointF [spotted_items.size()]; //do delete later
    int detected_blocks = 0;
    detecting(spotted_items, blocks_coordinate, detected_blocks);

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
            stateRunning(blocks_coordinate, detected_blocks); break;
    }


    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);

    delete[] blocks_coordinate;
    // destroy enemy when it goes out of the screen
    if (pos().y() > 2000){
        //decrease the health
        qDebug() << "ENEMY DELETED";
        scene()->removeItem(this);
        delete this;
    }
}
