#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H
#include <QGraphicsView>

class GGraphicsView : public QGraphicsView
{
public:
    GGraphicsView();
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // GGRAPHICSVIEW_H
