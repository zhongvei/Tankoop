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
public:

    /* Constructor and Destructor*/
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

    void startGame();

public slots:
    void start_button_clicked();
    void game_rules_button_clicked();
    void play_button_clicked();
    void back_button_clicked();

private:
    Ui::MainWindow *ui;
    List *list = nullptr;
    QPointer<QMediaPlayer> music = new QMediaPlayer();

signals:
    void startLocalGame(int nbPlayers, int nbViews);
    void setVisibleWidget(int i);
};

#endif // MAINWINDOW_H
