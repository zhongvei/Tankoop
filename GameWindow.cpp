#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent)
{
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,1400,1000);

//    setScene(scene);
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1400,1000);

    show();
}

//void GameWindow::startGame(int nbPlayers, int nbViews) {
//    game = new Game();

//    connect(gameTimer, &QTimer::timeout, this, &GameWidget::timerDecreases);
//    connect(game, &Game::teamsPointsChanged, this, &GameWidget::updateTeamsPoints);
//    connect(game, &Game::showEndScreen, this, [=] (int teamWinner) {
//        emit setFinishMenuWinner(teamWinner);
//        emit setVisibleWidget(3);
//    });

//    QString terrainFileName = "";
//    //if(nbPlayers >= 5) {
//        //terrainFileName = ":/Resources/bigTerrain.tmx";
//    //}else if(nbPlayers < 5) {
//    terrainFileName = ":/Resources/mediumTerrain.tmx";
//    //}


//    if(nbViews == 0) nbViews = nbPlayers;
//    // S'il y a autant de QGraphicsView que de joueurs -> splitscreen
//    bool isMultiplayer = nbPlayers == nbViews ? false : true;
//    game->startGame(terrainFileName, nbPlayers, isMultiplayer, tcpClient);
//    viewsLayout = new QHBoxLayout(this);

//    for(int i = 0; i < 1; i++) {
//        View *v = new View(i);
//        v->setScene(game);
//        viewsLayout->addWidget(v);
//        views.append(v);
//    }

//    viewsLayout->setContentsMargins(0, 0, 0, 0);
//    viewsLayout->setSpacing(0);
//    setLayout(viewsLayout);
//    teamsPointsProgess->raise();
//    pointsRed->raise();
//    pointsBlack->raise();
//    pointsRed->setText("0");
//    pointsBlack->setText("0");
//    timeLeft->raise();
//    setFocusPolicy(Qt::StrongFocus);
//    setFocus();

//    ambientMusicPlayer->setMedia(QUrl("qrc:/Resources/sounds/mainTitle.wav"));
//    ambientMusicPlayer->play();
//    emit stopMenuMusic();
//    min = 3, sec = 0;
//    gameTimer->start();
//    gameRunning = true;
//}
