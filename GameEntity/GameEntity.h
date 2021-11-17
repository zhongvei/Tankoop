#ifndef GAMEENTITY_H
#define GAMEENTITY_H


class GameEntity
{
public:
    enum class category{
        TANK,
        BULLET,
        BLOCK
    };

    ~GameEntity() = default;

    inline double get_max_health() const;
    inline void set_max_health(double max_health);

    inline double get_health() const;
    inline void set_health(double health);

    inline double get_health_regen() const;
    inline void set_health_regen(double health_regen);

    inline bool get_alive() const;
    inline void set_alive(bool alive);

    int get_size() const;
    inline void set_size(int size);

    inline int get_vx() const;
    inline int get_vy() const;
    inline void set_vx(int vx);
    inline void set_vy(int vy);

    inline double get_xp() const;
    inline void set_xp(double xp);

    inline int get_level() const;
    inline void set_level(int level);

private:

    double max_health {};
    double health {};
    double health_regen {};

    bool alive = 1;
    int size {};
    int vx{}, vy{};
    double xp{};
    int level{};


protected:
    GameEntity(const double& health, const double& health_regen, const double& max_health, const int& size,
               const int& vx, const int& vy,const double& xp,const int& level);

};

#endif // GAMEENTITY_H
