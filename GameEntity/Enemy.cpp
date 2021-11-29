#include "Enemy.h"
#include "Bullet.h"
#include "Block.h"


#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QList>


Enemy::Enemy(GameEngine* const g, double attack_range, double sight_range, const int& size): Tank(200,1,200,size,10,10,0,0.6,0.6,15,1,0,0), g(g), attack_range(attack_range), sight_range(sight_range)
{
    int stage = static_cast<int>(g->get_waves() / 3);
    int ministage = g->get_waves() % 3;

    if (g->get_waves() % 5 == 0) {
        if (g->get_enemy_count() == 0) {
            set_health(get_health()*2.5);
            set_damage(get_damage()*2.5);
            set_size(get_size()*1.5);
            set_health_regen(get_health_regen()*1.5);
            set_bullet_speed(get_bullet_speed()*3);
            set_max_health(get_max_health()*2.5);
            set_reload_speed(get_reload_speed()/3);
        }
    }

    if (g->get_waves() > 3) {
        int randomizer_highlevel = rand()%8;
        switch (randomizer_highlevel) {
            case 0:
                change_type(Tank::TYPE::GIANT);
                change_subtank(Tank::SUBTANK::POUNDER);
                set_health(get_health() + 60*stage + 15*ministage);
                set_max_health(get_max_health() + 60*stage + 15*ministage);
                set_health_regen(get_health_regen() + 4*stage + 1*ministage);
                set_damage(get_damage()+ 5*stage + 1*ministage);
                set_bullet_speed(get_bullet_speed() + 0.4*stage + 0.1*ministage);
                break;
            case 1:
                change_type(Tank::TYPE::ASSASSIN);
                change_subtank(Tank::SUBTANK::HUNTER);
                set_reload_speed(get_reload_speed() / (1+1*stage) - 0.075*ministage );
                set_damage(get_damage() + 10*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                set_bullet_speed(get_bullet_speed() + 0.6*stage + 0.15*ministage);
                break;
            case 2:
                change_type(Tank::TYPE::SHARPSHOOTER);
                change_subtank(Tank::SUBTANK::SNIPER);
                set_bullet_speed(get_bullet_speed() + 1.5*stage + 0.4*ministage);
                set_damage(get_damage() + 20*stage + 6*ministage);
                set_reload_speed(get_reload_speed() * (1+0.2*stage) + 0.05*ministage );
                attack_range += (400*stage + 80*ministage);
                sight_range += (600*stage + 120*ministage);
                break;
            case 3:
                change_type(Tank::TYPE::ENGINEER);
                change_subtank(Tank::SUBTANK::SPAWNER);
                set_health(get_health() + 40*stage + 8*ministage);
                set_max_health(get_max_health() + 40*stage + 8*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_reload_speed(get_reload_speed() / (1+1*stage) - 0.075*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.2*ministage);
                break;
            case 4:
                change_type(Tank::TYPE::GIANT);
                change_subtank(Tank::SUBTANK::SPINNER);
                set_health(get_health() + 45*stage + 10*ministage);
                set_max_health(get_max_health() + 45*stage + 10*ministage);
                set_health_regen(get_health_regen() + 3*stage + 0.75*ministage);
                set_damage(get_damage()+ 14*stage + 3*ministage);
                set_reload_speed(get_reload_speed() / (1+0.2*stage) - 0.02*ministage );
                set_bullet_speed(get_bullet_speed() + 0.6*stage + 0.15*ministage);
                break;
            case 5:
                change_type(Tank::TYPE::ASSASSIN);
                change_subtank(Tank::SUBTANK::IMMUNE);
                set_health_regen(get_health_regen() + 5*stage + 1*ministage);
                set_reload_speed(get_reload_speed() / (1+0.5*stage) - 0.05*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.2*ministage);
                set_damage(get_damage() + 8*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                break;
            case 6:
                change_type(Tank::TYPE::SHARPSHOOTER);
                change_subtank(Tank::SUBTANK::DUAL);
                set_bullet_speed(get_bullet_speed() + 1*stage + 0.3*ministage);
                set_damage(get_damage() + 16*stage + 4*ministage);
                attack_range += (150*stage + 30*ministage);
                sight_range += (300*stage + 60*ministage);
                break;
            case 7:
                change_type(Tank::TYPE::ENGINEER);
                change_subtank(Tank::SUBTANK::TRAPPER);
                set_health(get_health() + 50*stage + 15*ministage);
                set_max_health(get_max_health() + 50*stage + 15*ministage);
                set_health_regen(get_health_regen() + 5*stage + 1*ministage);
                set_reload_speed(get_reload_speed() / (1+0.6*stage) - 0.05*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.25*ministage);
                break;
        }
    }
    else if (g->get_waves() > 1) {
    int randomizer_lowlevel = rand()%6;
        switch (randomizer_lowlevel) {
            case 0:
                change_type(Tank::TYPE::GIANT);
                change_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 50*stage + 10*ministage);
                set_max_health(get_max_health() + 50*stage + 10*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_damage(get_damage()+ 15*stage + 3*ministage);
                break;
            case 1:
                change_type(Tank::TYPE::ASSASSIN);
                change_subtank(Tank::SUBTANK::DEFAULT);
                set_reload_speed(get_reload_speed() / (1+0.5*stage) - 0.05*ministage );
                set_damage(get_damage() + 7*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                break;
            case 2:
                change_type(Tank::TYPE::SHARPSHOOTER);
                change_subtank(Tank::SUBTANK::DEFAULT);
                set_bullet_speed(get_bullet_speed() + 0.4*stage + 0.1*ministage);
                set_damage(get_damage() + 10*stage + 3*ministage);
                attack_range += (150*stage + 30*ministage);
                sight_range += (300*stage + 60*ministage);
                break;
            case 3:
                change_type(Tank::TYPE::ENGINEER);
                change_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 40*stage + 8*ministage);
                set_max_health(get_max_health() + 40*stage + 8*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_reload_speed(get_reload_speed() / (1+0.4*stage) - 0.04*ministage );
                break;
            default:
                change_type(Tank::TYPE::NORMAL);
                change_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 25*stage + 5*ministage);
                set_max_health(get_max_health() + 25*stage + 5*ministage);
                set_health_regen(get_health_regen() + 1*stage + 0.25*ministage);
                set_damage(get_damage()+ 10*stage + 3*ministage);
                set_reload_speed(get_reload_speed() / (1+0.2*stage) - 0.02*ministage );
                set_bullet_speed(get_bullet_speed() + 0.2*stage + 0.05*ministage);
                break;
        }
    }
    attack_scale = attack_range/get_size();
    sight_scale = sight_range/get_size(); // change 800 to variable later

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
    scene()->removeItem(this);
    delete name_item; name_item = nullptr;
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
        Bullet * bullet = new Bullet(this,this->get_damage(),0,10,this->get_bullet_speed(),this->get_bullet_speed(),g);
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

        QPointF pos = this->pos() + QPointF(16,-40);
        name_item->setPos(pos);
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

        QPointF pos = this->pos() + QPointF(16,-40);
        name_item->setPos(pos);
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
