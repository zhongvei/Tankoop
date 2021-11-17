#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>

#include <QCursor>
#include <QPoint>
#include "math.h"

#include "GameEntity/myRect.h"
#include "GameEntity/Basic.h"
#include "GameEntity/Block.h"

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    void main_loop();
<<<<<<< HEAD
    void facing_cursor(Basic* basic);
=======
    void spawn_loop();
>>>>>>> main
private:
    QTimer* loop_timer;
    QTimer* single;
    QGraphicsScene* scene;
    MyRect* rect;
    Basic* basic;
    Block* block_arr[10];
};



#endif // GAMEWINDOW_H
