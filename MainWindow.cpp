#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GameWindow.h"
#include "EndGameWindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <QMessageBox>

/* The Constructor of MainWindow */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /* Set the background color of the main window */
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::lightGray);
    this->setWindowIcon(QIcon(":/Resources/icon/tankoop.jpg"));
    setAutoFillBackground(true);
    setPalette(pal);

    /* Initializing the User Interface */
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    /* Connector */
    connect(ui->start_button, SIGNAL(clicked()), this, SLOT(start_button_clicked()));
    connect(ui->quit_button, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
    connect(ui->howtoplay_button, SIGNAL(clicked()), this, SLOT(game_rules_button_clicked()));
    connect(ui->play_button, SIGNAL(clicked()), this, SLOT(play_button_clicked()));
    connect(ui->back_button, SIGNAL(clicked()), this, SLOT(back_button_clicked()));
    connect(ui->back_button_2, SIGNAL(clicked()), this, SLOT(back_button_clicked()));


    /* Play background music */
    music->setMedia(QUrl("qrc:/Resources/sounds/mainbruh.mp3"));
    music->setVolume(100);
    music->play();
}

void MainWindow::startGame() {

    /* Input name from the user */
    QString nameValue = ui->name_entry->toPlainText();
    ui->name_entry->clear();

    /* Proceeds to the Game Window */
    GameWindow* gameWindow = new GameWindow(0,nullptr,nullptr, nameValue);
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);

    /* Stop the music before proceeding to the Game Window page */
    music->stop();
    delete music;

    /* Closing Main Window */
    this->close();
}

/* Move to "Enter Name" Page */
void MainWindow::start_button_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

/* Show the "How To Play" page */
void MainWindow::game_rules_button_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}

/* Start the Game */
void MainWindow::play_button_clicked() {
    if(ui->name_entry->toPlainText().length() > 7) {
        QMessageBox* msg_box = new QMessageBox(this);
        msg_box->setText("Username must be less than 8 characters long!     "); // Ending whitespace for formatting
        msg_box->show();
        return;
    }
    startGame();
}

/* Go back to the main page */
void MainWindow::back_button_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}
