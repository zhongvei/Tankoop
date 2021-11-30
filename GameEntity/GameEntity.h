#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <QGraphicsRectItem>

class GameEntity: public QGraphicsRectItem
{
public:
    enum class CATEGORY{
        TANK,
        BULLET,
        BLOCK,
        WALL
    };

    enum class CLASS {
        NONE,
        BASIC,
        ENEMY,
        TURRET
    };

    ~GameEntity() = default;

    double get_max_health() const;
    void set_max_health(double max_health);

    double get_health() const;
    void set_health(double health);

    double get_health_regen() const;
    void set_health_regen(double health_regen);

    int get_size() const;
    void set_size(int size);

    double get_vx() const;
    double get_vy() const;
    void set_vx(double vx);
    void set_vy(double vy);

    double get_xp() const;
    void set_xp(double xp);

    int get_level() const;
    void set_level(int level);

    virtual GameEntity::CATEGORY get_category() const = 0;
    virtual GameEntity::CLASS get_class() const;

private:

    double max_health {};
    double health {};
    double health_regen {};

    int size{};
    double vx{}, vy{};
    double xp{};
    int level{};


protected:
    GameEntity(const double& health, const double& health_regen, const double& max_health, const int& size,
               const double& vx, const double& vy,const double& xp,const int& level);

};

#endif // GAMEENTITY_H
