TEMPLATE = app
TARGET = Tankoop

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += \
    main.cpp\
    GameEngine.cpp \
    GameEntity/Basic.cpp \
    GameEntity/Block.cpp \
    GameEntity/Bullet.cpp \
    GameEntity/FirstStage.cpp \
    GameEntity/HealthBar.cpp \
    GameEntity/Enemy.cpp \
    GameEntity/Subtank/Spinner.cpp \
    GameEntity/Subtank/Dual.cpp \
    GameEntity/Subtank/Hunter.cpp \
    GameEntity/Subtank/Immune.cpp \
    GameEntity/Subtank/Pounder.cpp \
    GameEntity/Subtank/Sniper.cpp \
    GameEntity/Subtank/Spawner.cpp \
    GameEntity/Subtank/Trapper.cpp \
    GameEntity/Tank.cpp \
    GameEntity/gameentity.cpp \
    GameWindow.cpp \
    Hud.cpp \
    MainWindow.cpp \


HEADERS += \
    GameEngine.h \
    GameEntity/Basic.h \
    GameEntity/Block.h \
    GameEntity/Bullet.h \
    GameEntity/FirstStage.h \
    GameEntity/HealthBar.h \
    GameEntity/Enemy.h \
    GameEntity/Subtank/Spinner.h \
    GameEntity/Subtank/Dual.h \
    GameEntity/Subtank/Hunter.h \
    GameEntity/Subtank/Immune.h \
    GameEntity/Subtank/Pounder.h \
    GameEntity/Subtank/Sniper.h \
    GameEntity/Subtank/Spawner.h \
    GameEntity/Subtank/Trapper.h\
    GameWindow.h \
    GameEntity/Tank.h \
    GameEntity/gameentity.h \
    Hud.h \
    MainWindow.h\


## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


FORMS += \
    Hud.ui \
    MainWindow.ui

RESOURCES += \
    Resources.qrc

