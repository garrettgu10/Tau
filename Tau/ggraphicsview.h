#ifndef GGRAPHICSVIEW_H
#define GGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QTimer>
#include <QCloseEvent>
#include <ggamescene.h>
#include <gmainmenuscene.h>
#include <QSettings>
#include <settings.h>

enum paddleMove {NONE = 0, ANTICLOCKWISE, CLOCKWISE};

class GGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GGraphicsView(Settings *settingsmgr);
    void setGScene(GGameScene* scene);

public slots:
    void startGame();
    void startMainMenu();
    void refresh();

protected:
    GMainMenuScene* MScene;
    GGameScene* GScene;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Settings* settingsmgr;
    QTimer* refresher;
    int winningScore = 3;
    void openCredits();
    void startEndSequence();
    void startBeginSequence();
    QTimer* updateBg;
    QMediaPlayer* music;
    QMediaPlaylist* playlist;
    bool startedGame = false;
    Arena* box;
    paddleMove movement[2];
    void closeEvent(QCloseEvent*);
};

#endif // GGRAPHICSVIEW_H
