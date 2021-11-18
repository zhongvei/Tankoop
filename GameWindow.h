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

#include "GameEntity/myRect.h"
#include "GameEntity/Basic.h"
#include "GameEntity/Block.h"
// class GameWindow : public QWidget, public QGraphicsView
class GameWindow : public QGraphicsView
{
    Q_OBJECT
    //using  QObject :: event;
    //using  QGraphicsView :: paintEvent;
public:
    GameWindow(QWidget* parent=0);
    void main_loop();
    void spawn_loop();
    //void paintEvent(QPaintEvent *event) override;
private:
    QTimer* loop_timer;
    QTimer* single;
    QGraphicsScene* scene;
    MyRect* rect;
    Basic* basic;
    Block* block_arr[10];
};



#endif // GAMEWINDOW_H
