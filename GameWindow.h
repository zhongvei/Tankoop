#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GameEngine.h"

#include <QGraphicsView>
#include <QGraphicsScene>


class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:

    const static int WINDOW_WIDTH = 2000;
    const static int WINDOW_HEIGHT = 2000;

    //CHANGE TO FRIEND LATER
    QGraphicsScene* scene;

    GameWindow(QWidget* parent=0);

};

#endif // GAMEWINDOW_H
