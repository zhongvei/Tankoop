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

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    void main_loop();
private:
    QTimer* loop_timer;
    QGraphicsScene* scene;
    MyRect* rect;
    Basic* basic;
};



#endif // GAMEWINDOW_H
