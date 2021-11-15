//#include <QMap>
//#include <QTimer>
//#include <QPixmap>
//#include <QDomDocument>
//#include <QVariant>

//#ifndef DATALOADER_H
//#define DATALOADER_H?

//class DataLoader
//{

//public:
//    DataLoader(QString terrainFileName);//, bool isMultiplayer);
//    int getTileSize();
//    int getPlayerSpeed();
//    QVector2D getPlayerSize();
//    bool isMultiplayer();
////    void setPlayerIndexInMulti(int id);
////    int getPlayerIndexInMulti();

//private:
//    int const tileSize = 130, playerHeight = 150, playerWidth = tileSize, playerSpeed = 8;
//    QDomDocument terrainXMLDoc;
////    bool multiplayer;
////    int playerIndexInMulti;         // position du joueur actuel dans la liste "players" si
////    // on est en multijoueur
//    QDomDocument getFileContent(QString fileName);

////    // PLAYER SPAWNPOINTS ----------------------------------------------------------------

//public:
//    QHash<int, QPoint> teamsSpawnpoints;
//    QPoint getTeamSpawnpoint(int teamId);

//private:
//    void setPlayersSpawnpoint();

////    // PLAYER ANIMATIONS -----------------------------------------------------------------

////public:
////    typedef struct PlayerAnimations_s {
////        QPixmap *image;
////        int nbFrame;
////        int framerate;
////    } PlayerAnimationsStruct;
////    QHash<int, PlayerAnimationsStruct*> playerAnimations;
////    int getPlayerAnimationId(int gender, int team, int animation);
////    int getBossAnimationId(int team);

////private:
////    void loadPlayerAnimations();
////    DataLoader::PlayerAnimationsStruct *setupPlayerAnimation(int nbFrame, int framerate, QString fileName);

////    // CANDY RESSOURCES ------------------------------------------------------------

////public:
////    typedef struct CandyRessources_s {
////        int nbPoints;
////        int candyType;
////        int candySize;
////        int respawnDelayMs;
////    } CandyRessourcesStruct;
////    // le int est le tileType (ce qu'il y a dans le .tmx)
////    QHash<int, CandyRessourcesStruct*> candiesRessources;
////    CandyRessourcesStruct *getCandyRessources(int tileType);

////private:
////    void loadCandyRessources();
////    DataLoader::CandyRessourcesStruct *setupCandyRessources(int nbPoints, int candyType, int candySize, int delayRespawnMs);

////    // CANDY ANIMATIONS ------------------------------------------------------------------

////public:
////    typedef struct CandyAnimations_s {
////        QPixmap *image;
////        QPixmap *imageBlack;
////        QPixmap *imageRed;
////        int nbFrame;
////        int framerate;
////    } CandyAnimationsStruct;
////    QHash<int, CandyAnimationsStruct*> candyAnimations;
////    int getCandyAnimationId(int type, int size);

////private:
////    void loadCandyAnimations();
////    DataLoader::CandyAnimationsStruct *setupCandyAnimation(int nbFrame, int framerate, QString fileName);

//    // TILE LAYERS ----------------------------------------------------------------------

//public:
//    typedef struct TileLayer_s {
//        QList<QList<int>> tiles;
//        int width;
//        int height;
//        int topLeftX;
//        int topLeftY;
//        QVariant zIndex;
//    } TileLayerStruct;
//    // doit être dans une qmap car plus tard dans le game.cpp, on prendra chaque layer
//    // dans l'ordre pour y construire les tiles (c'est pour ça que les layers sont
//    // nommées dans l'ordre alphabétique dans le .tmx)
//    QMap<QString, TileLayerStruct*> tileLayers;

//private:
//    void loadTileLayers();
//    QList<QList<int>> setupTileLayer(QDomNodeList chunks, int *topLeftX, int *topLeftY);
//    void getLayerPlacement(int *layerWidth, int *layerHeight, int *chunkMinX, int *chunkMinY, int size, QDomNodeList chunks);
//    QHash<QString, int> highestLowestPointsOfMap();
//    void updateTileLayersZIndex();

//    // TILES RESSOURCES ------------------------------------------------------------------

//public:
//    typedef struct TileRessource_s {
//        QPixmap *image;
//        QString name;   // corresponds to the path of the file from: / Resources
//    } TileRessourcesStruct;

//    // the int is the tileType (what's in the .tmx)
//    QHash<int, TileRessourcesStruct*> tileRessources;
//    TileRessourcesStruct* getTileRessource(int tileType);
//    int getTileType(QString name);

//private:
//    void loadTilesRessources();
//    QHash<int, QString> loadTilesIds();
//};

//#endif // DATALOADER_H
