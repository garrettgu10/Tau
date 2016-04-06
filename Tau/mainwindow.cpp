#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphScene = new QGraphicsScene;
    graphScene->setSceneRect(0,0,790,590);
    ui->graphicsView->setFixedSize(800,600);
    ui->graphicsView->setScene(graphScene);
    x=this->width()/2;
    y=this->height()/2;
    this->drawScene(graphScene);
}


void MainWindow::drawScene(QGraphicsScene *graphScene){

    QPainterPath path;
    QFont font;
    font.setPixelSize(10);
    font.setBold(false);
    font.setFamily("Comic Sans");
    path.addText(100,50,font,"Hello world");
    path.addEllipse(QPointF(x,y),100,100);
    graphScene->clear();
    graphScene->addPath(path,QPen(QBrush(Qt::black),1),QBrush(Qt::red));
    qDebug("hey");
}

MainWindow::~MainWindow()
{
    delete ui;
}
