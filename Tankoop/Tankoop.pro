TEMPLATE = app
TARGET = Tankoop

QT = core gui
QT += widgets

SOURCES += \
    Block.cpp \
    Bullet.cpp \
    MainWindow.cpp \
    Tank.cpp \
    gameentity.cpp \
    main.cpp \

HEADERS += \
    Block.h \
    Bullet.h \
    MainWindow.h \
    Tank.h \
    gameentity.h

FORMS += \
    MainWindow.ui
