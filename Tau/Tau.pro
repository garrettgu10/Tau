#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T15:12:05
#
#-------------------------------------------------

QT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tau
TEMPLATE = app


SOURCES += main.cpp \
    ggraphicsview.cpp \
    player.cpp \
    ball.cpp \
    helper.cpp \
    powerup.cpp \
    ggamescene.cpp \
    arena.cpp \
    scoredisplay.cpp \
    gmainmenuscene.cpp \
    playbutton.cpp

HEADERS  += \
    ggraphicsview.h \
    player.h \
    constants.h \
    ball.h \
    helper.h \
    powerup.h \
    ggamescene.h \
    arena.h \
    scoredisplay.h \
    gmainmenuscene.h \
    playbutton.h

FORMS    +=

RESOURCES += \
    icons.qrc \
    music.qrc

DISTFILES += \
    LICENSE.md
