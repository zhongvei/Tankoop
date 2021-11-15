//#include "dataLoader.h"
//#include <QDebug>
//#include <QtXml>
//#include <QFile>
//#include <QHash>
//#include <QDomDocument>
//#include <QVector2D>

//#define PLAYER_IN_LAYER 3       // Définit que les joueurs se trouvent entre
//// les layers x et x+1

///**
// * Constructeur du DataLoader, ne crée qu'un seul objet.
// * Charge les données d'animations des joueurs, des bonbons,
// * les couches de Tiles, les ressource de chaque type de bonbons, etc...
// */
//DataLoader::DataLoader(QString terrainFileName)//, bool isMultiplayer) //: multiplayer(isMultiplayer)
//{
//    terrainXMLDoc = getFileContent(terrainFileName);
////    loadPlayerAnimations();
////    loadCandyAnimations();
//    loadTilesRessources();
////    loadCandyRessources();
//    loadTileLayers();
//    updateTileLayersZIndex();
//    setPlayersSpawnpoint();
//}

///**
// * Lit et retourne le contenu du fichier donné en paramètre.
// */
//QDomDocument DataLoader::getFileContent(QString fileName) {
//    QDomDocument xmlBOM;
//    QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly))
//        qFatal("Erreur de lecture du fichier");
//    xmlBOM.setContent(&file);
//    file.close();
//    return xmlBOM;
//}

///**
// * Retourne la vitesse du joueur.
// */
//int DataLoader::getPlayerSpeed() {
//    return playerSpeed;
//}

///**
// * Retourne un vecteur 2D représentant la taille du joueur.
// */
//QVector2D DataLoader::getPlayerSize() {
//    return QVector2D(playerWidth, playerHeight);
//}

///**
// * Retourne si la partie est mutlijoueur ou non.
// */
////bool DataLoader::isMultiplayer() {
////    return multiplayer;
////}

///**
// * Définit l'id du joueur si le jeu est en multijoueur.
// */
////void DataLoader::setPlayerIndexInMulti(int id) {
////    playerIndexInMulti = id;
////}

///**
// * Retourne l'id du joueur en multijoueur.
// */
////int DataLoader::getPlayerIndexInMulti() {
////    return playerIndexInMulti;
////}

//// PLAYER SPAWNPOINTS -----------------------------------------------------------------------

///**
// * Définir le point d'apparition des joueurs.
// */
//void DataLoader::setPlayersSpawnpoint() {
//    for(int y = 0; y < tileLayers["5-config"]->tiles.size(); y++) {
//        for(int x = 0; x < tileLayers["5-config"]->tiles.at(y).size(); x++) {
//            int tileType = tileLayers["5-config"]->tiles.at(y).at(x);
//            if(tileType == 0)
//                continue;
//            if(getTileRessource(tileType)->name == "world/config/spawn-player-red.png")
//                teamsSpawnpoints.insert(0,
//                                        QPoint(
//                                            getTileSize() * (x + tileLayers["5-config"]->topLeftX),
//                                        getTileSize() * (y + tileLayers["5-config"]->topLeftY)
//                        ));
//            if(getTileRessource(tileType)->name == "world/config/spawn-player-black.png")
//                teamsSpawnpoints.insert(1,
//                                        QPoint(
//                                            getTileSize() * (x + tileLayers["5-config"]->topLeftX),
//                                        getTileSize() * (y + tileLayers["5-config"]->topLeftY)
//                        ));
//        }
//    }
//}

///**
// * Retourne le point d'apparition de l'id de l'équipe donné en paramètre.
// */
////QPoint DataLoader::getTeamSpawnpoint(int teamId) {
////    return teamsSpawnpoints[teamId];
////}

//// PLAYER ANIMATIONS ------------------------------------------------------------------------

///**
// * Charger les animations des joueurs.
// */
////void DataLoader::loadPlayerAnimations() {
////    playerAnimations.insert(0, setupPlayerAnimation(6, 150, ":/Resources/player/idle/boy-black-idle.png"));
////    playerAnimations.insert(1, setupPlayerAnimation(6, 150, ":/Resources/player/idle/girl-black-idle.png"));
////    playerAnimations.insert(2, setupPlayerAnimation(6, 150, ":/Resources/player/idle/boy-red-idle.png"));
////    playerAnimations.insert(3, setupPlayerAnimation(6, 150, ":/Resources/player/idle/girl-red-idle.png"));
////    playerAnimations.insert(4, setupPlayerAnimation(10, 50, ":/Resources/player/run/boy-black-run.png"));
////    playerAnimations.insert(5, setupPlayerAnimation(10, 50, ":/Resources/player/run/girl-black-run.png"));
////    playerAnimations.insert(6, setupPlayerAnimation(10, 50, ":/Resources/player/run/boy-red-run.png"));
////    playerAnimations.insert(7, setupPlayerAnimation(10, 50, ":/Resources/player/run/girl-red-run.png"));
////    // The boss'es animation
////    playerAnimations.insert(8, setupPlayerAnimation(6, 150, ":/Resources/bosses/idle/boss-black-idle.png"));
////    playerAnimations.insert(9, setupPlayerAnimation(6, 150, ":/Resources/bosses/idle/boss-red-idle.png"));
////}

/////**
//// * Retourne les données de l'animation du joueur.
//// */
////DataLoader::PlayerAnimationsStruct* DataLoader::setupPlayerAnimation(int nbFrame, int framerate, QString fileName) {
////    PlayerAnimationsStruct* aStruct = new PlayerAnimationsStruct;
////    aStruct->nbFrame = nbFrame;
////    aStruct->framerate = framerate;
////    aStruct->image = new QPixmap(fileName);
////    return aStruct;
////}

///**
// * Retourner l'animation, sous forme de int, du joueur passé en paramètre avec son genre, son équipe et son animation.
// */
////int DataLoader::getPlayerAnimationId(int gender, int team, int animation) {
////    if(gender == 0 && team == 0 && animation == 0) return 3;
////    if(gender == 1 && team == 0 && animation == 0) return 2;
////    if(gender == 0 && team == 1 && animation == 0) return 1;
////    if(gender == 1 && team == 1 && animation == 0) return 0;
////    if(gender == 0 && team == 0 && animation == 1) return 7;
////    if(gender == 1 && team == 0 && animation == 1) return 6;
////    if(gender == 0 && team == 1 && animation == 1) return 5;
////    if(gender == 1 && team == 1 && animation == 1) return 4;
////    return -1;
////}

///**
// * Récupérer l'animation du Boss selon l'id de l'équipe.
// */
////int DataLoader::getBossAnimationId(int team) {
////    if(team == 0) return 9;
////    if(team == 1) return 8;
////    return -1;
////}

//// CANDY RESSOURCES -------------------------------------------------------------------------

///**
// * Charger les ressources des Candy.
// */
////void DataLoader::loadCandyRessources() {
////    candiesRessources.insert(getTileType("candy/peanut-small.png"), setupCandyRessources(1, 0, 0, 25 * 1000));
////    candiesRessources.insert(getTileType("candy/mandarin-small.png"), setupCandyRessources(3, 1, 0, 30 * 1000));
////    candiesRessources.insert(getTileType("candy/peanut-big.png"), setupCandyRessources(5, 0, 1, 20 * 1000));
////    candiesRessources.insert(getTileType("candy/mandarin-big.png"), setupCandyRessources(10, 1, 1, 30 * 1000));
////}

/////**
//// * Retourne les ressources du Candy.
//// */
////DataLoader::CandyRessourcesStruct* DataLoader::setupCandyRessources(int nbPoints, int candyType, int candySize, int delayRespawnMs) {
////    CandyRessourcesStruct* aStruct = new CandyRessourcesStruct;
////    aStruct->nbPoints = nbPoints;
////    aStruct->candyType = candyType;
////    aStruct->candySize = candySize;
////    aStruct->respawnDelayMs = delayRespawnMs;
////    return aStruct;
////}

/////**
//// * Retourne les ressources du Candy selon son tile type.
//// */
////DataLoader::CandyRessourcesStruct *DataLoader::getCandyRessources(int tileType) {
////    if(candiesRessources.contains(tileType)) {
////        return candiesRessources[tileType];
////    }
////    return nullptr;
////}

//// CANDY ANIMATIONS ------------------------------------------------------------------

///**
// * Charger les animations des Candy.
// */
////void DataLoader::loadCandyAnimations() {
////    candyAnimations.insert(0, setupCandyAnimation(8, 100 , "peanut-small-idle"));
////    candyAnimations.insert(1, setupCandyAnimation(8, 100, "mandarin-small-idle"));
////    candyAnimations.insert(2, setupCandyAnimation(12, 100, "peanut-big-idle"));
////    candyAnimations.insert(3, setupCandyAnimation(10, 100, "mandarin-big-idle"));
////}

/////**
//// * Retourne les données de l'animation du joueur.
//// */
////DataLoader::CandyAnimationsStruct *DataLoader::setupCandyAnimation(int nbFrame, int framerate, QString fileName) {
////    CandyAnimationsStruct* aStruct = new CandyAnimationsStruct;
////    aStruct->nbFrame = nbFrame;
////    aStruct->framerate = framerate;
////    aStruct->image = new QPixmap(":/Resources/candy/idle/" + fileName + ".png");
////    aStruct->imageBlack = new QPixmap(":/Resources/candy/idle/hovers/" + fileName + "-black.png");
////    aStruct->imageRed = new QPixmap(":/Resources/candy/idle/hovers/" + fileName + "-red.png");
////    return aStruct;
////}

///**
// * Retourne l'identifiant de l'animation du Candy.
// */
////int DataLoader::getCandyAnimationId(int type, int size) {
////    if(type == 0 && size == 0) return 0;
////    if(type == 0 && size == 1) return 2;
////    if(type == 1 && size == 0) return 1;
////    if(type == 1 && size == 1) return 3;
////    return -1;
////}

//// TILE LAYERS ------------------------------------------------------------------------------

//// https://lucidar.me/fr/dev-c-cpp/reading-xml-files-with-qt/
///**
// * Charger les couches de tiles.
// */
//void DataLoader::loadTileLayers() {
//    // Lire le fichier XML et créer les ressources nécessaires
//    QDomNodeList layers = terrainXMLDoc.elementsByTagName("layer");

//    for(int i = 0; i < layers.count(); i++) {
//        QDomElement layer = layers.at(i).toElement();
//        // Chaque layer

//        TileLayerStruct *tileLayer = new TileLayerStruct();
//        int topLeftX = 0, topLeftY = 0;

//        // Prendre chaque chunk de la layer
//        QDomNodeList chunks = layer.firstChild().childNodes();
//        tileLayer->tiles = setupTileLayer(chunks, &topLeftX, &topLeftY);

//        tileLayer->height = tileLayer->tiles.size();
//        if(tileLayer->height != 0)
//            tileLayer->width = tileLayer->tiles.at(0).size();
//        QDomElement firstChunk = layers.at(i).firstChild().firstChild().toElement();
//        tileLayer->zIndex = QVariant(i);
//        tileLayer->topLeftX = topLeftX;
//        tileLayer->topLeftY = topLeftY;
//        tileLayers.insert(layer.attribute("name"), tileLayer);
//    }
//}

///**
// * Retourne la configuration des couches de tiles.
// */
//QList<QList<int>> DataLoader::setupTileLayer(QDomNodeList chunks, int *topLeftX, int *topLeftY) {
//    QList<QList<int>> dimLevel;

//    int chunkSize = chunks.at(0).toElement().attribute("width").toInt(); // 16
//    int layerWidth = 0, layerHeight = 0;

//    // Déterminer la taille de la layer
//    getLayerPlacement(&layerWidth, &layerHeight, topLeftX, topLeftY, chunkSize, chunks);

//    // Initialiser la liste
//    for(int i = 0; i < layerHeight; i++) {
//        QList<int> subList;
//        for(int j = 0; j < layerWidth; j++) {
//            subList.append(0);
//        }
//        dimLevel.append(subList);
//    }

//    for(int i = 0; i < chunks.length(); i++) {
//        QDomElement chunk = chunks.at(i).toElement();
//        if(chunk.attribute("width") != chunk.attribute("height"))
//            qFatal("chunk pas carré");

//        QList<QString> stringList = chunk.text().replace("\n", "").replace("\r", "").split(",");
//        QList<int> intList;
//        for(int i = 0; i < stringList.length(); i++) {
//            intList.append(stringList.at(i).toInt());
//        }
//        for(int y = 0; y < chunkSize; y++) {
//            for(int x = 0; x < chunkSize; x++) {
//                int insertYList = chunk.attribute("y").toInt() + y - *topLeftY;
//                int insertXList = chunk.attribute("x").toInt() + x - *topLeftX;
//                QList<int> subList = dimLevel.value(insertYList);
//                subList.replace(insertXList, intList.at(y*chunkSize + x));
//                dimLevel.replace(insertYList, subList);
//            }
//        }
//    }
//    return dimLevel;
//}

///**
// * Mettre dans les variables layerWidth et layerHeight la taille de la layer
// * (nombre de tiles en x et nombre de tiles en y)
// */
//void DataLoader::getLayerPlacement(int *layerWidth, int *layerHeight, int *chunkMinX, int *chunkMinY, int chunkSize, QDomNodeList chunks) {
//    if(chunks.length() == 1) {
//        *layerWidth = chunkSize;
//        *layerHeight = chunkSize;
//        return;
//    }

//    int minX = chunks.at(0).toElement().attribute("x").toInt();
//    int maxX = minX;
//    int minY = chunks.at(0).toElement().attribute("y").toInt();
//    int maxY = minY;

//    for(int i = 0; i < chunks.size(); i++) {
//        int newX = chunks.at(i).toElement().attribute("x").toInt();
//        int newY = chunks.at(i).toElement().attribute("y").toInt();
//        minX = minX < newX ? minX : newX;
//        maxX = maxX > newX ? maxX : newX;
//        minY = minY < newY ? minY : newY;
//        maxY = maxY > newY ? maxY : newY;
//    }

//    *chunkMinX = minX;
//    *chunkMinY = minY;
//    *layerWidth = maxX - minX + chunkSize;
//    *layerHeight = maxY - minY + chunkSize;
//}

///**
// * Retourne le point le plus haut et le plus bas du terrain.
// */
//QHash<QString, int> DataLoader::highestLowestPointsOfMap() {
//    QMapIterator<QString, TileLayerStruct*> i(tileLayers);
//    QHash<QString, int> returnValue;
//    returnValue["highest"] = tileLayers.first()->topLeftY;
//    returnValue["lowest"] = tileLayers.first()->tiles.length() + tileLayers.first()->topLeftY;

//    while(i.hasNext()) {
//        i.next();
//        if(i.value()->topLeftY < returnValue["highest"])
//            returnValue["highest"] = i.value()->topLeftY;
//        if(i.value()->tiles.length() + i.value()->topLeftY > returnValue["lowest"])
//            returnValue["lowest"] = i.value()->tiles.length() + i.value()->topLeftY;
//    }

//    returnValue["highest"] *= 130;
//    returnValue["lowest"] *= 130;
//    return returnValue;
//}

///**
// * Mise à jour des couches du terrain en tenant compte du z index.
// */
//void DataLoader::updateTileLayersZIndex() {
//    QMapIterator<QString, TileLayerStruct*> i(tileLayers);
//    QHash<QString, int> HLPoints = highestLowestPointsOfMap();
//    int j = 0;

//    while(i.hasNext()) {
//        i.next();
//        if(j < PLAYER_IN_LAYER)
//            i.value()->zIndex.setValue(i.value()->zIndex.toInt() + HLPoints["highest"]);
//        if(j > PLAYER_IN_LAYER)
//            i.value()->zIndex.setValue(i.value()->zIndex.toInt() + HLPoints["lowest"]);
//        if(j == PLAYER_IN_LAYER)
//            i.value()->zIndex.setValue(nullptr);
//        j++;
//    }

//}

//// TILE RESSOURCES --------------------------------------------------------------------------

///**
// * Charger les ressources des tiles.
// */
//void DataLoader::loadTilesRessources() {
//    QHash<int, QString> tilesIds = loadTilesIds();
//    QHashIterator<int, QString> tilesIdsIterator(tilesIds);

//    while (tilesIdsIterator.hasNext()) {
//        tilesIdsIterator.next();
//        TileRessourcesStruct *tileRessource = new TileRessourcesStruct();
//        tileRessource->image = new QPixmap(":/Resources/" + tilesIdsIterator.value());
//        tileRessource->name = tilesIdsIterator.value();
//        tileRessources.insert(tilesIdsIterator.key(), tileRessource);
//    }
//}

///**
// * Charge les tiles avec leur id et le retourne.
// */
//QHash<int, QString> DataLoader::loadTilesIds() {
//    QHash<int, QString> tilesIds;
//    QDomNodeList tilesets = terrainXMLDoc.elementsByTagName("tileset");

//    for(int i = 0; i < tilesets.count(); i++) {
//        QDomElement tileset = tilesets.at(i).toElement();
//        int tilesetId = tileset.attribute("firstgid").toInt();
//        QDomNodeList tiles = tileset.childNodes();

//        for(int j = 0; j < tiles.size(); j++) {
//            QDomElement tile = tiles.at(j).toElement();

//            if(tile.tagName() == "tile") {
//                int tileId = tile.attribute("id").toInt();
//                QString tileFile = tile.firstChild().toElement().attribute("source");
//                tilesIds.insert(tilesetId + tileId, tileFile);
//            }
//        }
//    }
//    return tilesIds;
//}

///**
// * Récupérer une tile selon son type.
// */
//DataLoader::TileRessourcesStruct* DataLoader::getTileRessource(int tileType) {
//    if(tileRessources.contains(tileType)) {
//        return tileRessources[tileType];
//    }
//    return nullptr;
//}

///**
// * Récupérer une tile selon le nom spécifié.
// */
//int DataLoader::getTileType(QString name) {
//    QHashIterator<int, TileRessourcesStruct*> tileRessoucesIterator(tileRessources);
//    while(tileRessoucesIterator.hasNext()) {
//        tileRessoucesIterator.next();

//        if(tileRessoucesIterator.value()->name == name) {
//            return tileRessoucesIterator.key();
//        }
//    }
//    return -1;
//}

///**
// * Retourne la taille de la tile.
// */
//int DataLoader::getTileSize() {
//    return tileSize;
//}
