#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T15:12:05
#
#-------------------------------------------------

QT       += core gui concurrent multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tau
TEMPLATE = app

RC_FILE = icon.rc

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
    playbutton.cpp \
    titletext.cpp \
    settings.cpp \
    skynet.cpp

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
    playbutton.h \
    titletext.h \
    settings.h \
    skynet.h

FORMS    +=

RESOURCES += \
    icons.qrc \
    overridingconcern.qrc \
    proofofconcept.qrc \
    runningonair.qrc

DISTFILES += \
    LICENSE.md

QMAKE_MAC_SDK = macosx10.12
