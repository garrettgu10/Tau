#ifndef TITLETEXT_H
#define TITLETEXT_H

#include <QObject>
#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QString>

class titleText : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    titleText(QString fontName, QPointF *titleCenter, int size, QString text);
    virtual QRectF boundingRect() const;
    double opacity = 1.0;

protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    QString text;
    QFontMetrics* titleFontMetrics;
    QFont* titleFont;
    int size;
    QPointF* titleCenter;
};

#endif // TITLETEXT_H
