#ifndef GMAINMENUSCENE_H
#define GMAINMENUSCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <arena.h>
#include <constants.h>
#include <playbutton.h>
#include <titletext.h>
#include <QTextItem>
#include <QThread>
#include <settings.h>

class GMainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GMainMenuScene(Arena* box, Settings *settingsmgr);
    void exitSequence();
    void entrySequence();
    titleText* creditsButton = new titleText("Georgia",new QPointF(windowWidth/2,windowHeight/2+mainMenuArenaRadius+200),50,"Credits");
    void adjustRules(int wins);

signals:
    void doneExiting();

public slots:
    void refresh();

private:
    titleText* title = new titleText("Times New Roman",new QPointF(windowWidth/2,windowHeight/4),200,"\u03C4");
    titleText* description = new titleText("Georgia",new QPointF(windowWidth/2,windowHeight/2+mainMenuArenaRadius+70),20,"\u03C4 (tau) -- torque (physics), 2\u03C0 \u2248 6.28 (math, c. 2001)");
    titleText* rules = new titleText("Georgia", new QPointF(windowWidth/2,windowHeight/2+mainMenuArenaRadius+100),20,"First to 3 wins");
    playButton* pb;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
    Arena* box;
};

#endif // GMAINMENUSCENE_H
