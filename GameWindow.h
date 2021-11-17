#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QTimer>

#include "GameEntity/Basic.h"
#include "GameEntity/Block.h"

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    void main_loop();
    void spawn_loop();
private:
    QTimer* loop_timer;
    QTimer* single;
    QGraphicsScene* scene;
    Basic* basic;
    Block* block_arr[10];
};



#endif // GAMEWINDOW_H
