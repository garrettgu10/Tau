#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T15:12:05
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tau
TEMPLATE = app


SOURCES += main.cpp \
    ggraphicsscene.cpp \
    ggraphicsview.cpp \
    player.cpp \
    ball.cpp \
    helper.cpp \
    powerup.cpp

HEADERS  += \
    ggraphicsscene.h \
    ggraphicsview.h \
    player.h \
    constants.h \
    ball.h \
    helper.h \
    powerup.h

FORMS    +=

RESOURCES += \
    icons.qrc
