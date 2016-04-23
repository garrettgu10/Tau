#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H
#include <QGraphicsView>
#include <ggamescene.h>
#include <QTimer>
#include <QCloseEvent>

class GGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GGraphicsView();
    void setGScene(GGameScene* scene);
protected:
    GGameScene* GScene;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    void closeEvent(QCloseEvent*);
    QTimer* movep1;
    QTimer* movep0;
    void setupTimer(QTimer* t, Player* p, bool cw);
};

#endif // GGRAPHICSVIEW_H
