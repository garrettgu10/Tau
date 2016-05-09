#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QTimer>
#include <QCloseEvent>
#include <ggamescene.h>
#include <gmainmenuscene.h>

class GGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GGraphicsView();
    void setGScene(GGameScene* scene);

public slots:
    void startGame();
    void startMainMenu();

protected:
    GMainMenuScene* MScene;
    GGameScene* GScene;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void startEndSequence();
    void startBeginSequence();
    QTimer* updateBg;
    QMediaPlayer* music;
    QMediaPlaylist* playlist;
    bool startedGame = false;
    Arena* box;
    bool clockWise[2];
    void closeEvent(QCloseEvent*);
    QTimer* movep1;
    QTimer* movep0;
    void setupTimer(QTimer* t, Player* p, bool cw);
};

#endif // GGRAPHICSVIEW_H
