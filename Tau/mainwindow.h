#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void drawScene(QGraphicsScene *scene);
    ~MainWindow();
    QGraphicsScene *graphScene;

public slots:
    //void startRefresh();

private:
    Ui::MainWindow *ui;
    int x;
    int y;
};

#endif // MAINWINDOW_H
