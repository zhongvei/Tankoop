#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "GameEngine.h"
#include "List.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QIcon>
#include <QPointF>
#include <QPainter>

class List;

class GameWindow : public QGraphicsView
{
    Q_OBJECT

public:

    /* Constructor and Destructor*/
    explicit GameWindow(int wave = 0, List *list = nullptr, QWidget* parent = 0, QString nameValue="");
    ~GameWindow() = default;

    /* Global Variable */
    const static int WINDOW_WIDTH = 2000;
    const static int WINDOW_HEIGHT = 2000;

    QGraphicsScene *scene;

};

#endif // GAMEWINDOW_H
