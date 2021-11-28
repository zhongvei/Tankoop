#include "EndGameWindow.h"
#include "ui_EndGameWindow.h"
#include "MainWindow.h"
#include "GameWindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

EndGameWindow::EndGameWindow(List *list, QWidget *parent) : QMainWindow(parent), list(list), ui(new Ui::EndGameWindow)
{
    /* Set the background color of the main window */
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::lightGray);
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));

    setAutoFillBackground(true);
    setPalette(pal);

    ui->setupUi(this);

    connect(ui->start_button, SIGNAL(clicked()), this, SLOT(start_button_clicked()));
    connect(ui->home_screen, SIGNAL(clicked()), this, SLOT(home_screen_clicked()));
    connect(ui->quit_button, SIGNAL(clicked()), this, SLOT(quit_game()));
}

void EndGameWindow::start_button_clicked(){
    int wave = 3; // should be input from the screen.. create smt like the pa4
    GameWindow* window = new GameWindow(wave, list);
    window->setWindowTitle("TankOOP");
    window->show();
    this->close();
}

void EndGameWindow::home_screen_clicked() {
    homeScreen();
}

void EndGameWindow::quit_game(){
    list->list_delete(list);
    EndGameWindow::close();
}

void EndGameWindow::homeScreen() {
    MainWindow* window = new MainWindow;
    window->setWindowTitle("TankOOP");
    window->show();

    this->close();
}

/* Display end game stats */
void EndGameWindow::endGameStats(QString player_xp, QString player_class, QString player_subtank, QString player_time_alive) {
    ui->game_over_msg->setText("Game Over!");
    ui->score->setText("Score: " + player_xp);
    ui->player_class->setText("Class: " + player_class);
    ui->player_subtank->setText("Sub-tank: " + player_subtank);
    ui->time_alive->setText("Time Alive: " + player_time_alive + " seconds");
}

void EndGameWindow::endGameLeaderboard(QString name_1,QString name_2,QString name_3,QString name_4,QString name_5,
                                       int score_1, int score_2, int score_3, int score_4, int score_5) {
    ui->Name->setText("Name");
    ui->Score->setText("Score");
    ui->name_1->setText(name_1);
    ui->name_2->setText(name_2);
    ui->name_3->setText(name_3);
    ui->name_4->setText(name_4);
    ui->name_5->setText(name_5);
    ui->score_1->setText(QString::number(score_1));
    ui->score_2->setText(QString::number(score_2));
    ui->score_3->setText(QString::number(score_3));
    ui->score_4->setText(QString::number(score_4));
    ui->score_5->setText(QString::number(score_5));
}
