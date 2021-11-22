#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QTimer>

#include <QCursor>
#include <QPoint>
#include "math.h"

#include "GameEntity/Basic.h"
#include "GameEntity/Block.h"
#include "Hud.h"

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    void main_loop();
    void facing_cursor(Basic* basic);
    void spawn_loop();
private:
    QTimer* loop_timer;
    QTimer* single;
    QGraphicsScene* scene;
    Basic* basic;
    Hud* hud;
};



#endif // GAMEWINDOW_H
