#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QGraphicsView>
#include <QGraphicsScene>

#include "GamePlay.h"
//#include "tcpclient.h"
#include "view.h"
#include <QBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>
#include <QTimer>
#include <QMediaPlayer>

class GameWindow : public QGraphicsView
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    QGraphicsScene* scene;

};



#endif // GAMEWINDOW_H
