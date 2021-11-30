#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "List.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QPointer>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    List *list = nullptr;
    QPointer<QMediaPlayer> music = new QMediaPlayer();

public:

    /*
     *  @funct: Constructs the Main Window with all of its attributes
     *
     *  @param: parent: nullptr
     *  @return: N/A
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /*
     *  @funct: Destructor of the Main Window with all of its attributes
     *
     *  @param: N/A
     *  @return: N/A
     */
    ~MainWindow() = default;

    /*
     *  @funct:  Starting the game and moving the screen to Game Window
     *
     *  @param:  N/A
     *  @return: N/A
     */
    void startGame();

public slots:
    void start_button_clicked();
    void game_rules_button_clicked();
    void play_button_clicked();
    void back_button_clicked();

signals:
    void startLocalGame(int nbPlayers, int nbViews);
    void setVisibleWidget(int i);
};

#endif // MAINWINDOW_H
