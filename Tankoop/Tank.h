#ifndef TANK_H
#define TANK_H

#include "gameentity.h"

class Tank: public GameEntity {
public:
    Tank();

    double get_atk_spd() const;
    void set_atk_spd(double atk_spd);

    double get_blt_spd() const;
    void set_blt_spd(double blt_spd);

    double get_dmg() const;
    void set_dmg(double dmg);


private:
    double atk_spd;
    double blt_spd;
    double dmg;
};

#endif // TANK_H
