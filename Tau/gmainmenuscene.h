#ifndef GMAINMENUSCENE_H
#define GMAINMENUSCENE_H
#include <QObject>
#include <QGraphicsScene>
#include <arena.h>
#include <constants.h>
#include <playbutton.h>

class GMainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GMainMenuScene(Arena* box);
    QTimer* refresher;

public slots:
    void refresh();

private:
    playButton* pb;
    QBrush* brush = new QBrush(QColor::fromRgb(255,255,255));
    QPen* arenaPen = new QPen(*brush,arenaWidth,Qt::SolidLine,Qt::SquareCap);
    Arena* box;
};

#endif // GMAINMENUSCENE_H
