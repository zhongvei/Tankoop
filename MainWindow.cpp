#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GameWindow.h"
#include "EndGameWindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QMessageBox>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /* Set the background color of the main window */
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::lightGray);
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));

    setAutoFillBackground(true);
    setPalette(pal);

    ui->setupUi(this);

    connect(ui->start_button, SIGNAL(clicked()), this, SLOT(start_button_clicked()));
    connect(ui->quit_button, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
    connect(ui->howtoplay_button, SIGNAL(clicked()), this, SLOT(game_rules_button_clicked()));
    connect(ui->play_button, SIGNAL(clicked()), this, SLOT(play_button_clicked()));
    connect(ui->back_button, SIGNAL(clicked()), this, SLOT(back_button_clicked()));
    connect(ui->back_button_2, SIGNAL(clicked()), this, SLOT(back_button_clicked()));

    ui->stackedWidget->setCurrentIndex(0);

    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc://Resources/sounds/mainMenu.mp3"));
    music->play();
}

void MainWindow::startGame() {
    // Get player's input name
    QString nameValue = ui->name_entry->toPlainText();
    ui->name_entry->clear();

    GameWindow* gameWindow = new GameWindow(0,nullptr,nullptr, nameValue);
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);

    this->close();
}

void MainWindow::start_button_clicked() {
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::game_rules_button_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::play_button_clicked() {
    if(ui->name_entry->toPlainText().length() > 7) {
        QMessageBox* msg_box = new QMessageBox(this);
        msg_box->setText("Username must be less than 8 characters long!     "); // Ending whitespace for formatting
        msg_box->show();
        return;
    }
    startGame();
}

void MainWindow::back_button_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}
