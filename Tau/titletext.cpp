#include "titletext.h"

titleText::titleText(QString fontName, QPointF* center, int size, QString text)
{
    this->text = text;
    titleFont = new QFont(fontName,size,QFont::Normal,false);
    titleFontMetrics = new QFontMetrics(QFont(*titleFont));
    this->titleCenter = center;
    this->opacity = 1.0;
    this->rect = realRect();

    this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
}

QRectF titleText::realRect() const
{
    return QRectF(titleCenter->x()-titleFontMetrics->width(text)/2,titleCenter->y()-titleFontMetrics->height(),
                  titleFontMetrics->width(text),titleFontMetrics->height()+10);
}

bool titleText::containsPt(QPoint p)
{
    return this->rect.contains(p.x(),p.y());
}

void titleText::setText(QString s)
{
    this->text = s;
    this->update();
}

QRectF titleText::boundingRect() const
{
    return realRect();
}

void titleText::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(QColor::fromRgb(255,255,255,255));
    painter->setBrush(QBrush(QColor::fromRgb(255,255,255,255)));
    painter->setFont(*titleFont);
    painter->setOpacity(opacity);
    painter->drawText(titleCenter->x()-titleFontMetrics->width(text)/2,titleCenter->y(),text);
}

double titleText::getOpacity() const
{
    return opacity;
}

void titleText::setOpacity(double value)
{
    opacity = value;
    this->update();
}
