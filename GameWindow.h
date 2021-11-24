#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GameEntity/Basic.h"
#include "GameEntity/Block.h"
#include "Hud.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QCursor>

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:

    const int WINDOW_WIDTH = 2000;
    const int WINDOW_HEIGHT = 2000;

    GameWindow(QWidget* parent=0);
    void main_loop();
    void facing_cursor(Basic* basic);
    void spawn_loop();
    void spawn_enemies();
    bool game_over();

private:
    QTimer* loop_timer;
    QTimer* enemy_timer;
    QTimer* single;
    QGraphicsScene* scene;
    Basic* basic;
    Hud* hud;
};

#endif // GAMEWINDOW_H
