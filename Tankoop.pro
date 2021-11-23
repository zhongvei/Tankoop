QT       += core gui network xml multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TEMPLATE = app
TARGET = Tankoop

SOURCES += \
    GameEntity/Basic.cpp \
    GameEntity/Block.cpp \
    GameEntity/Bullet.cpp \
    GameEntity/HealthBar.cpp \
    GameEntity/View.cpp \
    GameEntity/myRect.cpp \
    GameWindow.cpp \
    MainWindow.cpp \
    GameEntity/Tank.cpp \
    GameEntity/gameentity.cpp \
    main.cpp \
    #GameEntity/tankgraphic.cpp

HEADERS += \
    GameEntity/Basic.h \
    GameEntity/Block.h \
    GameEntity/Bullet.h \
    GameEntity/HealthBar.h \
    GameEntity/View.h \
    GameEntity/myRect.h \
    GameWindow.h \
    MainWindow.h \
    GameEntity/Tank.h \
    GameEntity/gameentity.h \
    #GameEntity/tankgraphic.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

FORMS += \
    MainWindow.ui
