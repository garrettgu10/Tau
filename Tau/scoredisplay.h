#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H
#include <QGraphicsItem>
#include <constants.h>
#include <QPen>
#include <QBrush>

class ScoreDisplay: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    ScoreDisplay();
    int getScore(int playerNum);
    virtual QRectF boundingRect() const;
    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void score(int playerNum);
    double opacity = 1.0;

protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    int padding = 20;
    QPen pen;
    QBrush brush;
    int scores[2];
};

#endif // SCOREDISPLAY_H
