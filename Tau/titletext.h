#ifndef TITLETEXT_H
#define TITLETEXT_H

#include <QObject>
#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QString>

class titleText : public QGraphicsObject
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    titleText(QString fontName, QPointF *titleCenter, int size, QString text);
    virtual QRectF boundingRect() const;
    QRectF realRect() const;
    bool containsPt(QPoint p);
    void setText(QString s);

    double getOpacity() const;
    void setOpacity(double value);

protected:
    void paint (QPainter * painter, const QStyleOptionGraphicsItem*, QWidget*);

private:
    double opacity = 1.0;
    QRectF rect;
    QString text;
    QFontMetrics* titleFontMetrics;
    QFont* titleFont;
    int size;
    QPointF* titleCenter;
};

#endif // TITLETEXT_H
