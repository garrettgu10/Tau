#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H
#include <QGraphicsView>
#include <ggraphicsscene.h>
#include <QTimer>

class GGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GGraphicsView();
    void setGScene(GGraphicsScene* scene);
protected:
    GGraphicsScene* GScene;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QTimer* movep1;
    QTimer* movep2;
    void setupTimer(QTimer* t, Player* p, bool cw);
};

#endif // GGRAPHICSVIEW_H
