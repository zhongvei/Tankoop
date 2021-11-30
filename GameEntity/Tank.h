#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"
#include "HealthBar.h"
#include "Wall.h"

#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QStyleOption>
#include <QMediaPlayer>


class HealthBar;
class Turret;

class Tank: public GameEntity {
public:

    /* enum class to help differentiate the type of the Tank */
    enum class TYPE {
        NORMAL = 0,
        GIANT = 1,
        ASSASSIN = 2,
        SHARPSHOOTER = 3,
        ENGINEER = 4
    };

    /* enum class to help differentiate the subtank of the Tank */
    enum class SUBTANK {
        DEFAULT = 0,
        SPINNER = 1,
        POUNDER = 2,
        HUNTER = 3,
        IMMUNE = 4,
        SNIPER = 5,
        DUAL = 6,
        SPAWNER = 7,
        TRAPPER = 8
    };

    /* To print out enum class values as text */
    QString TYPE_textstr[5] =
    {
        QString("Normal"),
        QString("Giant"),
        QString("Assassin"),
        QString("Sharpshooter"),
        QString("Engineer"),
    };
    QString SUBTANK_textstr[9] =
    {
        QString("Default"),
        QString("Spinner"),
        QString("Pounder"),
        QString("Hunter"),
        QString("Immune"),
        QString("Sniper"),
        QString("Dual"),
        QString("Spawner"),
        QString("Trapper"),
    };

    /*
    *  @funct:  destructor for the tank, to remove the dynamic allocated objects
    *
    *  @param:  N/A
    *  @return: N/A
    */
    ~Tank();

    /* Accesors */
    /*
    *  @funct:  get the reload speed for the Tank
    *
    *  @param:  N/A
    *  @return: double: reload speed of the Tank
    */
    double get_reload_speed() const;

    /*
    *  @funct:  get the bullet speed of the Tank
    *
    *  @param:  N/A
    *  @return: double: bullet speed of the Tank
    */
    double get_bullet_speed() const;

    /*
    *  @funct:  get the damage of the Tank
    *
    *  @param:  N/A
    *  @return: double: the damage of the Tank
    */
    double get_damage() const;

    /*
    *  @funct:  get the angle of shooting of the Tank
    *
    *  @param:  N/A
    *  @return: double: the angle of shooting of the Tank
    */
    double get_degree() const;

    /*
    *  @funct:  get the number of skill point(s) of the Tank
    *
    *  @param:  N/A
    *  @return: int: the number of skill point(s) of the Tank
    */
    int get_skill_point() const;

    /*
    *  @funct:  get the number of evolution point(s) of the Tank
    *
    *  @param:  N/A
    *  @return: int: the number of evolution point(s) of the Tank
    */
    int get_evolution_point() const;

    /*
    *  @funct:  get the number of sub tank evolution point(s) of the Tank
    *
    *  @param:  N/A
    *  @return: int: the number of sub tank evolution point(s) of the Tank
    */
    int get_sub_tank_evolution_point() const;

    /*
    *  @funct:  get the remaining time for the Tank to finish the reload process
    *
    *  @param:  N/A
    *  @return: int: the remaining time for the Tank to finish the reload process
    */
    int get_reload_finish() const;

    /*
    *  @funct:  get the reload status for the Tank
    *
    *  @param:  N/A
    *  @return: bool: true if the Tank is still reloading and false otherwise
    */
    bool get_reload_status() const;

    /*
    *  @funct:  get the the cooldown status for the Tank's skill cooldown
    *
    *  @param:  N/A
    *  @return: bool: true if the Tank's skill is in cooldown, false otherwise
    */
    bool get_cooldown_status() const;

    /*
    *  @funct:  get the remaining time for the Tank's skill cooldown
    *
    *  @param:  N/A
    *  @return: int: the remaining time for the Tank's skill cooldown
    */
    int get_cooldown() const;

    /*
    *  @funct:  get the status for the Tank's skill cooldown
    *
    *  @param:  N/A
    *  @return: bool: true if the Tank's skill is still in cooldown and false otherwise
    */
    bool get_skill_status() const;

    /*
    *  @funct:  get the Tank's collision damage with a Block
    *
    *  @param:  N/A
    *  @return: double: the Tank's collision damage with a Block
    */
    double get_collision_damage() const;

    /*
    *  @funct:  get the type of the Tank based on the value in the enum class Tank::TYPE
    *
    *  @param:  N/A
    *  @return: Tank::Type: the type of the Tank based on the value in the enum class Tank::TYPE
    */
    TYPE get_type() const;

    /*
    *  @funct:  get the subtank of the Tank based on the value in the enum class Tank::SUBTANK
    *
    *  @param:  N/A
    *  @return: Tank::SUBTANK: the subtank of the Tank based on the value in the enum class Tank::SUBTANK
    */
    SUBTANK get_subtank() const;

    /*
    *  @funct:  get the pointer to the Healthbar which is assigned to the tank
    *
    *  @param:  N/A
    *  @return: HealthBar*: the pointer to the Healthbar which is assigned to the tank
    */
    HealthBar* get_health_bar() const;

    /*
    *  @funct:  get the name of the Tank in QString data type
    *
    *  @param:  N/A
    *  @return: QString: the name of the Tank in QString data type
    */
    QString get_name() const;


    /* Mutators */
    /*
    *  @funct:  set the reload speed for the Tank
    *
    *  @param:  reload_speed: the reload speed for the Tank
    *  @return: N/A
    */
    void set_reload_speed(double reload_speed);

    /*
    *  @funct:  set the bullet speed for the Tank
    *
    *  @param:  bullet_speed: the bullet speed of the Tank
    *  @return: N/A
    */
    void set_bullet_speed(double bullet_speed);

    /*
    *  @funct:  set the damage for the Tank
    *
    *  @param:  damage: the damage for the Tank
    *  @return: N/A
    */
    void set_damage(double damage);

    /*
    *  @funct:  set the degree of movement for the Tank
    *
    *  @param:  degree: the degree of movement for the Tank
    *  @return: N/A
    */
    void set_degree(double degree);

    /*
    *  @funct:  set the skill point for the Tank
    *
    *  @param:  skill_point: the skill point for the Tank
    *  @return: N/A
    */
    void set_skill_point(int skill_point);

    /*
    *  @funct:  increase the skill point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_skill_point();

    /*
    *  @funct:  decrease the skill point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void decrease_skill_point();

    /*
    *  @funct:  increase the evolution point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_evolution_point();

    /*
    *  @funct:  decrease the evolution point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void decrease_evolution_point();

    /*
    *  @funct:  increase the sub tank evolution point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_sub_tank_evolution_point();

    /*
    *  @funct:  decrease the sub tank evolution point for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void decrease_sub_tank_evolution_point();

    /*
    *  @funct:  set the remaining time for the Tank to finish the reload process
    *
    *  @param:  reload_finish: the remaining time for the Tank to finish the reload process
    *  @return: N/A
    */
    void set_reload_finish(int reload_finish);

    /*
    *  @funct:  change the reload status for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void change_reload_status();

    /*
    *  @funct:  change the cooldown status for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void change_cooldown_status();

    /*
    *  @funct:  check the colliding blocks for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void check_collision();

    /*
    *  @funct:  increase the level for the Tank if the experience point reach 100 and give the tank certain skill point when it reached certain levels
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void increase_level();

    /*
    *  @funct:  set the remaining time for the Tank's skill cooldown
    *
    *  @param:  int cooldown: the remaining time for the Tank's skill cooldown
    *  @return: N/A
    */
    void set_cooldown(int cooldown);

    /*
    *  @funct:  change the skill status for the Tank
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void change_skill_status();

    /*
    *  @funct:  change the type for the Tank with multipliers for the Tank's status
    *
    *  @param:  type: the new type for the Tank to change into
    *  @return: N/A
    */
    void change_type(Tank::TYPE type);

    /*
    *  @funct:  set the type for the Tank without multipliers for the Tank's status
    *
    *  @param:  type: the new type for the Tank
    *  @return: N/A
    */
    void set_type(Tank::TYPE type);


    /*
    *  @funct:  set the sub tank type for the Tank with different skills being accessible by the tank
    *
    *  @param:  subtank: the subtank for the Tank to change into
    *  @return: N/A
    */
    void set_subtank(Tank::SUBTANK subtank);

    /*
    *  @funct:  create a healthbar for the Tank
    *
    *  @param:  scene: the scene for which the healthbar is created on
    *  @return: N/A
    */
    void create_health_bar(QGraphicsScene* scene);

    /*
    *  @funct:  set skill for the Tank, which differs for subtank and the default subtank doesn't have a skill
    *
    *  @param:  N/A
    *  @return: N/A
    */
    void skill();

    /*
    *  @funct:  skill timeout for the Tank's skill, reset the status for the Tank to the original status
    *
    *  @param:  N/a
    *  @return: N/A
    */
    void skill_timer_timeout();

    /*
    *  @funct:  set the collision damage for the Tank when it hits a block
    *
    *  @param:  collision_damage: the collision damage for the Tank when it hits a block
    *  @return: N/A
    */
    void set_collision_damage(double collision_damage);

    /*
    *  @funct:  set the name for the Tank
    *
    *  @param:  name: the name for the Tank
    *  @return: N/A
    */
    void set_name(QString name);

    /*
    *  @funct:  an override function from QGraphicsRectItem such that the bounding area of the Tank is setup
    *
    *  @param:  N/A
    *  @return: N/A
    */
    QRectF boundingRect() const override;

    /*
    *  @funct:  an override function from QGraphicsRectItem such that the shape of the Tank is setup
    *
    *  @param:  N/A
    *  @return: N/A
    */
    QPainterPath shape() const override;

    /*
    *  @funct:  an override function from GameEntity such the Tank can be identified as GameEntity::CATEGORY::TANK
    *
    *  @param:  N/A
    *  @return: N/A
    */
    GameEntity::CATEGORY get_category() const override;

    /*
    *  @funct:  an override function from QGraphicsRectItem such that the shape of the Tank is paint on the screen
    *
    *  @param:  name: the name for the Tank
    *  @return: N/A
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    //WILSON
    Tank& operator=(const Tank& tank);

    /*
    *  @funct:  a copy constructor for the tank
    *
    *  @param:  tank: the tank that is being copied from
    *  @return: N/A
    */
    Tank(const Tank& tank);

    QGraphicsTextItem* name_item {};
    QMediaPlayer* music = new QMediaPlayer;

private:
    /* Private Data Members */
    double reload_speed{};
    double bullet_speed{};
    double damage{};
    int skill_point{};
    int evolution_point{};
    int sub_tank_evolution_point{};
    double degree{};
    int reload_finish{};
    bool reload {1};
    bool cooldown_status {};
    int cooldown {};
    double collision_damage {7};
    bool skill_status {};

    HealthBar* health_bar{};

    Tank::TYPE type = Tank::TYPE::NORMAL;
    Tank::SUBTANK subtank = Tank::SUBTANK::DEFAULT;

    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;
    Turret* turret{};

    QVector<QString> EnemyNames {QString("Shadow"), QString("Voyage"), QString("Bing"), QString("Chilli"), QString("Galaxy"),
                                QString("Blays"), QString("Gibbs")};
    QString name;

protected:

    /*
    *  @funct:  the constructor for the Tank, in protected type so that no Tank can be created directly
    *
    *  @param:  health: initial health for the Tank, health_regen: initial health regen for the Tank, max_health: initial max_health for the Tank,
    *  @param:  size: initial size for the Tank, vx: initial movement speed in the x axis for the Tank, vy: initial movement speed in the y axis for the Tank,
    *  @param:  xp: initial experience point for the GameEntity, reload_speed: the reload speed for the Tank, bullet_speed: the bullet speed for teh Tank
    *  @param:  level: initial level for the GameEntity, skill_point: the initial skill point for the tank, degree: the initial degree of shooting for the Tank    
    *  @return: N/A     
    */
    Tank(
        const double& health, const double& health_regen, const double& max_health,
        const int& size, const double& vx, const double& vy,const double& xp,
        const double& reload_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree
    );

    /*
    *  @funct:  an override function from QGraphicsRectItem such that this function is being repetedly called by the GameEngine
    *
    *  @param:  step: the phase of the function, step = 0 would not run the function body
    *  @return: N/A     
    */
    void advance(int step) override;



};

#endif // TANK_H
