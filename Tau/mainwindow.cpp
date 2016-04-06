#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    graphScene = new QGraphicsScene;
    graphScene->setSceneRect(0,0,790,590);
    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setScene(graphScene);
    QPainterPath path;
    QFont font;
    font.setPixelSize(10);
    font.setBold(false);
    font.setFamily("Comic Sans");
    path.addText(100,50,font,"Hello world");
    graphScene->addPath(path,QPen(QBrush(Qt::black),1),QBrush(Qt::black));
    */
}


MainWindow::~MainWindow()
{
    delete ui;
}
