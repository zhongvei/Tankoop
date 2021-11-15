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

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow(QWidget* parent=0);
    QGraphicsScene* scene;
//public:
//    GameWindow(QWidget *parent = nullptr);//TcpClient *tcpClient, QWidget *parent = nullptr);
//    void resizeEvent(QResizeEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;

//private:
//    QGraphicsScene scene;
//    //TcpClient *tcpClient;
//    QList<View*> views;
//    Game *game;
//    QBoxLayout *viewsLayout;
//    // GUI
//    QProgressBar *teamsPointsProgess;
//    QLabel *pointsRed;
//    QLabel *pointsBlack;
//    QLabel *timeLeft;
//    int min, sec;
//    QMediaPlayer *ambientMusicPlayer;
//    QTimer *gameTimer;
//    bool gameRunning;

//public slots:
//    void startGame(int nbPlayers, int nbViews = 0);
//    void resetGame();

//private slots:
//    void updateTeamsPoints(int nbPointsRed, int nbPointsBlack);
//    void timerDecreases();

//signals:
//    void setFinishMenuWinner(int teamWinner);
//    void setVisibleWidget(int index);
//    void stopMenuMusic();
};



#endif // GAMEWINDOW_H
