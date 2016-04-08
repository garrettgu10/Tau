#include "ggraphicsview.h"
#include <QDebug>
#include <QMouseEvent>

GGraphicsView::GGraphicsView()
{

}

void GGraphicsView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->x();
    qDebug() << event->y();
}
