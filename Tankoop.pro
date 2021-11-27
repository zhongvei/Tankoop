TEMPLATE = app
TARGET = Tankoop

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += \
    EndGameWindow.cpp \
    GameEntity/Turret.cpp \
    GameEntity/Wall.cpp \
    main.cpp\
    GameEngine.cpp \
    GameEntity/Basic.cpp \
    GameEntity/Block.cpp \
    GameEntity/Bullet.cpp \
    GameEntity/HealthBar.cpp \
    GameEntity/Enemy.cpp \
    GameEntity/Tank.cpp \
    GameEntity/gameentity.cpp \
    GameWindow.cpp \
    Hud.cpp \
    MainWindow.cpp \


HEADERS += \
    EndGameWindow.h \
    GameEngine.h \
    GameEntity/Basic.h \
    GameEntity/Block.h \
    GameEntity/Bullet.h \
    GameEntity/HealthBar.h \
    GameEntity/Enemy.h \
    GameEntity/Turret.h \
    GameEntity/Wall.h \
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
    EndGameWindow.ui \
    Hud.ui \
    MainWindow.ui

RESOURCES += \
    Resources.qrc

