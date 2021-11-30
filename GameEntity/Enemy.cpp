#include "Enemy.h"

Enemy::Enemy(GameEngine* const g, double attack_range, double sight_range, const int& size): Tank(200,1,200,size,10,10,0,0.6,0.6,15,1,0,0), g(g), attack_range(attack_range), sight_range(sight_range)
{
    int stage = static_cast<int>(g->get_waves() / 3);
    int ministage = g->get_waves() % 3;

    /* Spawn the boss enemy every 5 stages */
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

    /* Randomly choose the enemy's type after reaching waves 3 */
    if (g->get_waves() > 3) {
        int randomizer_highlevel = rand()%8;
        switch (randomizer_highlevel) {
            case 0:
                change_type(Tank::TYPE::GIANT);
                set_subtank(Tank::SUBTANK::POUNDER);
                set_health(get_health() + 60*stage + 15*ministage);
                set_max_health(get_max_health() + 60*stage + 15*ministage);
                set_health_regen(get_health_regen() + 4*stage + 1*ministage);
                set_damage(get_damage()+ 5*stage + 1*ministage);
                set_bullet_speed(get_bullet_speed() + 0.4*stage + 0.1*ministage);
                break;
            case 1:
                change_type(Tank::TYPE::ASSASSIN);
                set_subtank(Tank::SUBTANK::HUNTER);
                set_reload_speed(get_reload_speed() / (1+1*stage) - 0.075*ministage );
                set_damage(get_damage() + 10*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                set_bullet_speed(get_bullet_speed() + 0.6*stage + 0.15*ministage);
                break;
            case 2:
                change_type(Tank::TYPE::SHARPSHOOTER);
                set_subtank(Tank::SUBTANK::SNIPER);
                set_bullet_speed(get_bullet_speed() + 1.5*stage + 0.4*ministage);
                set_damage(get_damage() + 20*stage + 6*ministage);
                set_reload_speed(get_reload_speed() * (1+0.2*stage) + 0.05*ministage );
                attack_range += (400*stage + 80*ministage);
                sight_range += (600*stage + 120*ministage);
                break;
            case 3:
                change_type(Tank::TYPE::ENGINEER);
                set_subtank(Tank::SUBTANK::SPAWNER);
                set_health(get_health() + 40*stage + 8*ministage);
                set_max_health(get_max_health() + 40*stage + 8*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_reload_speed(get_reload_speed() / (1+1*stage) - 0.075*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.2*ministage);
                break;
            case 4:
                change_type(Tank::TYPE::GIANT);
                set_subtank(Tank::SUBTANK::SPINNER);
                set_health(get_health() + 45*stage + 10*ministage);
                set_max_health(get_max_health() + 45*stage + 10*ministage);
                set_health_regen(get_health_regen() + 3*stage + 0.75*ministage);
                set_damage(get_damage()+ 14*stage + 3*ministage);
                set_reload_speed(get_reload_speed() / (1+0.2*stage) - 0.02*ministage );
                set_bullet_speed(get_bullet_speed() + 0.6*stage + 0.15*ministage);
                break;
            case 5:
                change_type(Tank::TYPE::ASSASSIN);
                set_subtank(Tank::SUBTANK::IMMUNE);
                set_health_regen(get_health_regen() + 5*stage + 1*ministage);
                set_reload_speed(get_reload_speed() / (1+0.5*stage) - 0.05*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.2*ministage);
                set_damage(get_damage() + 8*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                break;
            case 6:
                change_type(Tank::TYPE::SHARPSHOOTER);
                set_subtank(Tank::SUBTANK::DUAL);
                set_bullet_speed(get_bullet_speed() + 1*stage + 0.3*ministage);
                set_damage(get_damage() + 16*stage + 4*ministage);
                attack_range += (150*stage + 30*ministage);
                sight_range += (300*stage + 60*ministage);
                break;
            case 7:
                change_type(Tank::TYPE::ENGINEER);
                set_subtank(Tank::SUBTANK::TRAPPER);
                set_health(get_health() + 50*stage + 15*ministage);
                set_max_health(get_max_health() + 50*stage + 15*ministage);
                set_health_regen(get_health_regen() + 5*stage + 1*ministage);
                set_reload_speed(get_reload_speed() / (1+0.6*stage) - 0.05*ministage );
                set_bullet_speed(get_bullet_speed() + 0.8*stage + 0.25*ministage);
                break;
        }
    }

    /* Increase the enemy's stats each wave */
    else if (g->get_waves() > 1) {
    int randomizer_lowlevel = rand()%6;
        switch (randomizer_lowlevel) {
            case 0:
                change_type(Tank::TYPE::GIANT);
                set_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 50*stage + 10*ministage);
                set_max_health(get_max_health() + 50*stage + 10*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_damage(get_damage()+ 15*stage + 3*ministage);
                break;
            case 1:
                change_type(Tank::TYPE::ASSASSIN);
                set_subtank(Tank::SUBTANK::DEFAULT);
                set_reload_speed(get_reload_speed() / (1+0.5*stage) - 0.05*ministage );
                set_damage(get_damage() + 7*stage + 2*ministage);
                set_vx(get_vx() + 3*stage + 0.75*ministage);
                set_vy(get_vy() + 3*stage + 0.75*ministage);
                break;
            case 2:
                change_type(Tank::TYPE::SHARPSHOOTER);
                set_subtank(Tank::SUBTANK::DEFAULT);
                set_bullet_speed(get_bullet_speed() + 0.4*stage + 0.1*ministage);
                set_damage(get_damage() + 10*stage + 3*ministage);
                attack_range += (150*stage + 30*ministage);
                sight_range += (300*stage + 60*ministage);
                break;
            case 3:
                change_type(Tank::TYPE::ENGINEER);
                set_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 40*stage + 8*ministage);
                set_max_health(get_max_health() + 40*stage + 8*ministage);
                set_health_regen(get_health_regen() + 2*stage + 0.5*ministage);
                set_reload_speed(get_reload_speed() / (1+0.4*stage) - 0.04*ministage );
                break;
            default:
                change_type(Tank::TYPE::NORMAL);
                set_subtank(Tank::SUBTANK::DEFAULT);
                set_health(get_health() + 25*stage + 5*ministage);
                set_max_health(get_max_health() + 25*stage + 5*ministage);
                set_health_regen(get_health_regen() + 1*stage + 0.25*ministage);
                set_damage(get_damage()+ 10*stage + 3*ministage);
                set_reload_speed(get_reload_speed() / (1+0.2*stage) - 0.02*ministage );
                set_bullet_speed(get_bullet_speed() + 0.2*stage + 0.05*ministage);
                break;
        }
    }

    /* Set the positioning of both the attack area and sight area */
    attack_scale = attack_range/get_size();
    attack_area = new QGraphicsEllipseItem(0,0,attack_range,attack_range);
    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);
    sight_scale = sight_range/get_size();
    sight_area = new QGraphicsEllipseItem(0,0,sight_range,sight_range);
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
    delete name_item;
    name_item = nullptr;
    g->set_enemy_count(g->get_enemy_count()-1);
    timer->stop();
}

/* Accessor */
GameEntity::CLASS Enemy::get_class() const {return GameEntity::CLASS::ENEMY;}
QGraphicsEllipseItem* Enemy::get_attack_area() const{ return attack_area; }
QGraphicsEllipseItem* Enemy::get_sight_area() const{ return sight_area; }
int Enemy::get_range() const { return attack_range; }
double Enemy::get_attack_scale() const { return attack_scale; }
double Enemy::get_sight_scale() const { return sight_scale; }

double Enemy::distanceTo(GameEntity * basic){
    QPointF this_pos = QPointF(x() + get_size()/2, y() + get_size()/2);
    QPointF target_pos = QPointF(basic->x() + basic->get_size()/2, basic->y() + basic->get_size()/2);
    QLineF ln(this_pos,target_pos);
    return ln.length();
}

/* Shooting mechanism and moves the pipes (shooter) of the enemy */
void Enemy::fire(){
    QTransform transform;
    transform.translate(this->get_size()/2,this->get_size()/2);
    transform.rotate(get_degree());
    transform.translate(-(this->get_size()/2),-(this->get_size()/2));
    this->setTransform(transform);

    if(!this->get_reload_status()){
        change_reload_status();
        Bullet * bullet = new Bullet(this,this->get_damage(),0,10,this->get_bullet_speed(),this->get_bullet_speed(),g);
        bullet->set_degree(this->get_degree());
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))-bullet->get_size()/2),y() +(this->get_size()/2*(1+sin(bullet->get_degree()/57)))-bullet->get_size()/2);
        scene()->addItem(bullet);
    }
}

/* To compare the closest distance between two value */
template <typename T>
void findClosestDistance(T a, double this_dist, double &closest_dist, QPointF &closest_pt, double &closest_size){
    if (this_dist < closest_dist){
        closest_dist = this_dist;
        closest_pt = a->pos();
        closest_size = a->get_size();
    }
}


void Enemy::detecting(QList<QGraphicsItem *> items){

    double closest_dist = 800;
    double closest_size = 0;
    QPointF closest_pt = QPointF(0,0);
    for (int i = 0, n = items.size(); i < n; ++i){
        /* Enemies spotted */
        if (typeid(*(items[i])) == typeid(Basic) || typeid(*(items[i])) == typeid(Block)){
            random_movement = true; // the enemy can do random movement again only after seeing a block
            turn = 0;
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
                player_location = closest_pt;
                closest_pt = the_target->pos();
                closest_size = the_target->get_size();
                if( (items[i]->x() > x() - attack_range/2 && items[i]->x() < x() + attack_range/2) &&
                    (items[i]->y() > y() - attack_range/2 && items[i]->y() < y() + attack_range/2))
                {
                    num_target = 1;
                }
                break;
            }

        }

        else if(i == n-1)
            player_detected = false;

    }

    /* Set the movement of the enemy if the enemy detects atleast one entity in its sight area */
    if(closest_pt.x() && closest_pt.y()){
        double angle_in_radians = std::atan2((closest_pt.y() + closest_size/2 -(y()+get_size()/2)),(closest_pt.x() + closest_size/2 -(x()+get_size()/2))); //ricat
        double angle_in_degrees = (angle_in_radians / M_PI) * 180;
        set_degree(angle_in_degrees);
    }

    /* Do a random movement if the enemy cannot detect any entity within its sight area */
    else{
        if(random_movement){
            random_movement = false;
            double degree_mult = 0;
            srand(time(NULL));
            degree_mult = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(!get_degree())
                set_degree(180);
            else
                set_degree(get_degree()*degree_mult);

        }
    }
}

/* The enemy state that enable the enemy to farm blocks and target the player */
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

/* The enemy state to flee or avoid the player at any cost when the enemy's health point is low */
void Enemy::stateRunning(){

    /* Reloading mechanism */
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

}

/* Make the enemy "bounces" everytime it comes close to the edge of the window */
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

/* A function that handle the enemy movement and calls the detecting function and changing the state of the enemy */
void Enemy::move(){

    /* Detecting the enemies */
    QList<QGraphicsItem *> spotted_items = sight_area->collidingItems();
    detecting(spotted_items);

    /* Set the state of the enemy based on the enemy's health and the position of the player. */
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
            stateRunning();
            break;
    }

    /* Set the position of the attack area and the sight area to follow the enemy's position */
    attack_area->setPos(x() - get_size() * (get_attack_scale()-1)/2, y() - get_size() * (get_attack_scale()-1)/2);
    sight_area->setPos(x() - get_size() * (get_sight_scale()-1)/2, y() - get_size() * (get_sight_scale()-1)/2);

    if (pos().x() + 100 > 2000 || pos().y() + 100  > 2000 || pos().x() - 100 < 0 || pos().y() - 100  < 0)
        bounces();
}
