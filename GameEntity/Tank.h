#ifndef TANK_H
#define TANK_H

#include "GameEntity.h"

#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QtMath>

class Tank: public GameEntity, public QGraphicsRectItem {

public:

    enum class TYPE {
        NORMAL = 0,
        GIANT = 1,
        ASSASIN = 2,
        SHARPSHOOTER = 3,
        ENGINEER = 4
    };

    double get_attack_speed() const;
    void set_attack_speed(double attack_speed);

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

    void check_collision();
    void increase_level();

    int get_reload_finish() const;
    void set_reload_finish(int reload_finish);

    bool get_reload_status() const;
    void change_reload_status();

    void change_class(Tank::TYPE type);

    virtual void skill(){}
    
private:
    double attack_speed{};
    double bullet_speed{};
    double damage{};
    int total_skill_point{};
    int skill_point{};
    int evolution_point{};
    double degree{};
    int reload_finish{};
    bool reload {1};

    Tank::TYPE type = Tank::TYPE::NORMAL;

    qreal angle = 0;
    qreal speed = 0;
    qreal mouseEyeDirection = 0;
    QColor color;

protected:
    Tank(
        const double& health, const double& health_regen, const double& max_health, 
        const int& size, const double& vx, const double& vy,const double& xp,
        const double& attack_speed,
        const double& bullet_speed,
        const double& damage,
        const int& level,
        const int& skill_point,
        const int& degree
    );

    void advance(int step) override;

};

#endif // TANK_H
