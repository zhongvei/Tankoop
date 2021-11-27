#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"
#include "HealthBar.h"

#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QStyleOption>


class HealthBar;

class Tank: public GameEntity {
public:

    enum class TYPE {
        NORMAL = 0,
        GIANT = 1,
        ASSASSIN = 2, // TODO: fix spelling: ASSASSIN
        SHARPSHOOTER = 3,
        ENGINEER = 4
    };

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
        QString("ASSASSIN"),
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

    double get_reload_speed() const;
    void set_reload_speed(double reload_speed);

    double get_bullet_speed() const;
    void set_bullet_speed(double bullet_speed);

    double get_damage() const;
    void set_damage(double damage); 

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    double get_degree() const;
    void set_degree(double degree);

    int get_skill_point() const;
    void increase_skill_point();
    void decrease_skill_point();

    int get_total_skill_point() const;
    void increase_total_skill_point();

    int get_evolution_point() const;
    void increase_evolution_point();
    void decrease_evolution_point();

    int get_sub_tank_evolution_point() const;
    void increase_sub_tank_evolution_point();
    void decrease_sub_tank_evolution_point();

    void check_collision();
    void increase_level();

    int get_reload_finish() const;
    void set_reload_finish(int reload_finish);

    bool get_reload_status() const;
    void change_reload_status();

    bool get_cooldown_status() const;
    void change_cooldown_status();

    int get_cooldown() const;
    void set_cooldown(int cooldown);

    bool get_skill_status() const;
    void change_skill_status();

    void change_class(Tank::TYPE type);
    TYPE get_class() const;

    void change_subtank(Tank::SUBTANK subtank);
    SUBTANK get_subtank() const;

    void create_heatlh_bar(QGraphicsScene* scene);

    HealthBar* get_health_bar() const;
    void skill();
    void skill_timer_timeout();

    void set_collision_damage(double collision_damage);
    double get_collision_damage() const;


private:
    double reload_speed{};
    double bullet_speed{};
    double damage{};
    int total_skill_point{};
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
    Tank::SUBTANK subtank = Tank::SUBTANK::TRAPPER;

    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;

protected:
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

    void advance(int step) override;

};

#endif // TANK_H
