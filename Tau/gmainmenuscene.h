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

class GMainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GMainMenuScene(Arena* box);
    QTimer* refresher;
    void exitSequence();

signals:
    void doneExiting();

public slots:
    void refresh();

private:
    titleText* title;
    playButton* pb;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
    Arena* box;
};

#endif // GMAINMENUSCENE_H
