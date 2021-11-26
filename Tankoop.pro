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

