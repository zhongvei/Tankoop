#include "Enemy.h"
#include "Bullet.h"
#include "Block.h"


#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QList>


Enemy::Enemy(GameEngine *g, double attack_range, double sight_range, const int& size): Tank(200,1,200,size,10,10,0,0.6,0.6,7,1,0,0), g(g), attack_range(attack_range), sight_range(sight_range)
{

    int randomizer_lowlevel = rand()%8;
    switch (randomizer_lowlevel) {
        case 0:
            change_class(Tank::TYPE::GIANT);
            change_subtank(Tank::SUBTANK::DEFAULT);
            break;
        case 1:
            change_class(Tank::TYPE::ASSASSIN);
            change_subtank(Tank::SUBTANK::DEFAULT);
            break;
        case 2:
            change_class(Tank::TYPE::SHARPSHOOTER);
            change_subtank(Tank::SUBTANK::DEFAULT);
            break;
        case 3:
            change_class(Tank::TYPE::ENGINEER);
            change_subtank(Tank::SUBTANK::DEFAULT);
            break;
        default:
            change_class(Tank::TYPE::NORMAL);
            change_subtank(Tank::SUBTANK::DEFAULT);
            break;
    }
    attack_scale = attack_range/size;
    sight_scale = sight_range/size; // change 800 to variable later

    attack_area = new QGraphicsEllipseItem(0,0,attack_range,attack_range);
    //attack_area->setStartAngle(90*16);
    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);

    sight_area = new QGraphicsEllipseItem(0,0,sight_range,sight_range); // change the value of sight_area to non const later
    //attack_area->setStartAngle(90*16);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);

    // make/connect a timer to move() the enemy every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);

}

Enemy::~Enemy(){
    delete attack_area;
    attack_area = nullptr;

    delete sight_area;
    sight_area = nullptr;

    delete this->get_health_bar();
    QList<QGraphicsItem *> list = scene()->items();
    for(int i = 0; i < list.size(); i++) {
        GameEntity* the_thing =  dynamic_cast<GameEntity*>(list[i]);
        if (the_thing !=nullptr && the_thing->get_category() == GameEntity::CATEGORY::BULLET) {
            Bullet* the_bullet= dynamic_cast<Bullet*>(list[i]);
            if(the_bullet->get_tank() == this) {
                delete the_bullet;
            }
        }
    }
    g->set_enemy_count(g->get_enemy_count()-1);
    timer->stop();
}

GameEntity::CLASS Enemy::get_class() const {return GameEntity::CLASS::ENEMY;}

double Enemy::distanceTo(GameEntity * basic){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(basic->x() + basic->get_size()/2, basic->y() + basic->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

void Enemy::fire(){
    QTransform transform;
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    //transform.translate(-dx,-dy);
    this->setTransform(transform);

    if(!this->get_reload_status()){
        change_reload_status();
//        qDebug() << "ENEMY GOES PEW-PEW";
        Bullet * bullet = new Bullet(this,50,0,10,0.6,0.6);
        bullet->set_degree(this->get_degree());
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))-bullet->get_size()/2),y() +(this->get_size()/2*(1+sin(bullet->get_degree()/57)))-bullet->get_size()/2);
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


void Enemy::detecting(QList<QGraphicsItem *> items, int &detected_blocks){

    double closest_dist = 800;
    QPointF closest_pt = QPointF(0,0);
    double closest_size = 0;

    for (int i = 0, n = items.size(); i < n; ++i){
        /* Enemies spotted */
        if (typeid(*(items[i])) == typeid(Basic) || typeid(*(items[i])) == typeid(Block)){
            random_movement = true; // the enemy can do random movement again only after seeing a block
            turn = 0;

            if(!player_detected){
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
                    num_target += 1;
                    //qDebug() << "BLOCK DETECTED INSIDE SHOOTING RANGE";
                }

            }

            GameEntity *the_target = dynamic_cast<GameEntity*>(items[i]);
            double this_dist = distanceTo(the_target);
            findClosestDistance(the_target,this_dist,closest_dist,closest_pt,closest_size);

            if(typeid(*(items[i])) == typeid(Basic)){
                player_detected = true;
                player_location = closest_pt;
                closest_pt = the_target->pos();
                closest_size = the_target->get_size();
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) && (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2)){
                    num_target = 1;
                }
                break;
            }
            else{
                detected_blocks++;
            }


        }
        else if(i == n-1){
            player_detected = false;
        }


    }

    if(closest_pt.x() && closest_pt.y()){
        double angle_in_radians = std::atan2((closest_pt.y() + closest_size/2 -(y()+get_size()/2)),(closest_pt.x() + closest_size/2 -(x()+get_size()/2))); //ricat
        double angle_in_degrees = (angle_in_radians / M_PI) * 180;

        set_degree(angle_in_degrees);
    }
    else{
        if(random_movement){
            random_movement = false;
            double degree_mult = 0;

            srand(time(NULL));
            degree_mult = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            if(!get_degree()){
                set_degree(180);
            }
            else{
                set_degree(get_degree()*degree_mult);
            }

        }
    }
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

void Enemy::stateRunning(const int &detected_blocks){
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

    if(pos().x() + 100 > 2000 || pos().y() + 100  > 2000 || pos().x() - 100 < 0 || pos().y() - 100  < 0){
        double angle_in_radians = std::atan2((player_location.y() + 30/2 -(y()+get_size()/2)),(player_location.x() + 30/2 -(x()+get_size()/2)));
        double angle_in_degrees = (angle_in_radians / M_PI) * 180;
        double player_degree = angle_in_degrees;
        set_degree(player_degree);
    }
    else{
        setPos(x()+(10*cos((get_degree()+180)/57)),y()+(10*sin((get_degree()+180)/57)));
    }
//    if (pos().x() + attack_range/2 > 2000 || pos().y() + attack_range/2  > 2000 || pos().x() - attack_range/2 < 0 || pos().y() - attack_range/2  < 0){

//    }
}

//void Enemy::stateRunning(QList<QGraphicsItem *> items_coordinate, const int &detected_blocks){
//    double angle_in_radians = std::atan2((player_location.y() + 30/2 -(y()+get_size()/2)),(player_location.x() + 30/2 -(x()+get_size()/2)));
//    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
//    double player_degree = angle_in_degrees;
//    int quadrant = 0;
//    if(-179 <= player_degree && player_degree < -90){
//        quadrant = 2;
//    }
//    else if (90 < player_degree && player_degree <= 180){
//        quadrant = 3;
//    }

//    int num_possible_running_location = 0;
//    QPointF *max_possible_running_location = new QPointF [detected_blocks];
//    for(int i = 0; i < detected_blocks; i++){
//        angle_in_radians = std::atan2((items_coordinate[i].y() + 30/2 -(y()+get_size()/2)),(items_coordinate[i].x() + 30/2 -(x()+get_size()/2)));
//        angle_in_degrees = (angle_in_radians / M_PI) * 180;

//        if(quadrant == 2){
//            if(angle_in_degrees < 180){
//                angle_in_degrees -= 360;
//            }
//        }
//        else if(quadrant == 3){
//            if(angle_in_degrees < 0){
//                angle_in_degrees += 360;
//            }
//        }
//        if(angle_in_degrees < (player_degree - 90) || angle_in_degrees > (player_degree + 90) ){
//            max_possible_running_location[num_possible_running_location] = items_coordinate[i];
//            num_possible_running_location++;
//        }

//    }
//    qDebug() << num_possible_running_location;
//    //whereToMove(max_possible_running_location, num_possible_running_location);
//    delete[] max_possible_running_location;

//    setPos(x()+(10*cos((get_degree()+180)/57)),y()+(10*sin((get_degree()+180)/57)));
//}

void Enemy::bounces(){
    if(turn == 10){
        turn = 0;
        turn = true;
        double degree_mult = 90;
        set_degree(get_degree()+degree_mult);
    }
    else{
        turn += 1;
    }
}

void Enemy::move(){

    /* Detecting the enemies */
    QList<QGraphicsItem *> spotted_items = sight_area->collidingItems();
//    QPointF *blocks_coordinate = new QPointF [spotted_items.size()]; //do delete later
    int detected_blocks = 0;
    detecting(spotted_items, detected_blocks);

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
            stateRunning(detected_blocks);
            break;
    }


    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);

//    delete[] blocks_coordinate;
    // destroy enemy when it goes out of the screen pos().y() > 2000 || pos().x() > 2000 || pos().y() < 0 || pos().x() < 0
    if (pos().x() + 100 > 2000 || pos().y() + 100  > 2000 || pos().x() - 100 < 0 || pos().y() - 100  < 0){
        bounces();
//        scene()->removeItem(this);
//        delete this;
    }
}
