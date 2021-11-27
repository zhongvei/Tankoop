#include "EndGameWindow.h"
#include "ui_EndGameWindow.h"
#include "MainWindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>

EndGameWindow::EndGameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EndGameWindow)
{
    /* Set the background color of the main window */
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::lightGray);
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));

    setAutoFillBackground(true);
    setPalette(pal);

    ui->setupUi(this);

    connect(ui->home_screen, SIGNAL(clicked()), this, SLOT(home_screen_clicked()));
    connect(ui->quit_button, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
}

void EndGameWindow::home_screen_clicked() {
    homeScreen();
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
