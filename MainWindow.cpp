#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GameWindow.h"
#include "EndGameWindow.h"

#include <QGraphicsView>
#include <QGraphicsScene>

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
    connect(ui->load_button, SIGNAL(clicked()), this, SLOT(load_button_clicked()));
}

void MainWindow::startGame() {
    GameWindow* gameWindow = new GameWindow();
    gameWindow->setAttribute(Qt::WA_DeleteOnClose);

    this->close();
}

void MainWindow::start_button_clicked() {
    startGame();
}

void MainWindow::load_button_clicked() {
    EndGameWindow* window = new EndGameWindow;
    window->setWindowTitle("TankOOaP");

    window->show();

    this->close();
}
