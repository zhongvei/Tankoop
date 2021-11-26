 #ifndef BASIC_H
#define BASIC_H

#include "Tank.h"
#include "tankgraphic.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsRotation>
#include <QTransform>

class Basic: public Tank, public QGraphicsRotation, public QTransform
{
private:
    double changex = 0;
    double changey = 0;
    int skill_cooldown;
    bool cooldown_status;

    QGraphicsView* parent = nullptr;

    bool UP, DOWN, RIGHT, LEFT;

public:

    enum class ADVANCED {
        POUNDER = 1,
        SPINNER = 2,
        HUNTER = 3,
        IMMUNE = 4,
        DUAL = 5,
        SNIPER = 6,
        SPAWNER = 7,
        TRAPPER = 8
    };

    Basic(QGraphicsView* parent=nullptr);
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void facing_cursor(Basic* basic);
    // void virtual skill();
    double get_changex();
    double get_changey();

    int get_skill_cooldown() const;
    void set_cooldown_status();

protected:
    void advance(int step) override;
    
};

#endif // BASIC_H
