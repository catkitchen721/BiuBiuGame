#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 800, 600)),
    player(new Player),
    timer(new QTimer),
    realTimer(new QTimer),
    bgm(new QMediaPlayer),
    bgmPlaylist(new QMediaPlaylist)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/pic/resource/bg.jpeg").scaled(800, 1200));
    scene->setSceneRect(0, 0, 800, 600);
    player->setPixmap(QPixmap(":/pic/resource/player.png").scaled(32, 32));
    scene->addItem(static_cast<QGraphicsPixmapItem *>(player));
    player->setPos(350, 550);

    this->setWindowTitle("D - D - O - S !!");

    bgm->setMedia(QMediaContent(QUrl("qrc:/audio/resource/bgm.mp3")));
    bgmPlaylist->addMedia(QUrl("qrc:/audio/resource/bgm.mp3"));
    bgmPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    bgm->setMedia(bgmPlaylist);
    bgm->setVolume(50);
    bgm->play();

    timer->start(10);
    realTimer->start(1000);

    //countTime = 0;
    //connect(timer, SIGNAL(timeout()), this, SLOT(backgroundMoving()));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    enemy = new Enemy;
    scene->addItem(static_cast<QGraphicsPixmapItem *>(enemy));
    enemy->setPixmap(QPixmap(":/pic/resource/enemy.png").scaled(128, 128));
    enemy->setPos(350, 50);

    enemyMovingFreq = new QTimer();
    enemyMovingFreq->start(2000);

    enemy->isbackwardMoving = false;
    enemy->isshooting = true;

    connect(enemyMovingFreq, SIGNAL(timeout()), this, SLOT(enemyMovingByAI()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateLCD()));
    connect(realTimer, SIGNAL(timeout()), this, SLOT(countScore()));

    this->isWin = false;
    this->score = 10000000;
    this->currentTime = 0l;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::backgroundMoving()
{
    if(countTime == 600)
    {
        scene->setSceneRect(0, 600 - countTime * 1, 800, 600);
        countTime = 0;
    }
    else
    {
        scene->setSceneRect(0, 600 - countTime * 1, 800, 600);
        ++countTime;
    }
}

void MainWindow::countScore()
{
    ++this->currentTime;
    if(player->isDead) this->score = 0;
    if(this->score <= 0) return;
    if(currentTime <= 10l)
    {
        this->score -= 148763;
    }
    else if(currentTime > 10l && currentTime <= 60l)
    {
        this->score -= 94870;
    }
    else if(currentTime > 60l && currentTime <= 120l)
    {
        this->score -= 7210;
    }
    else
    {
        this->score -= 666;
    }
}

void MainWindow::enemyMovingByAI()
{
    if(enemy->isDead)
    {
        this->enemyMovingFreq->stop();
        return;
    }
    if(!enemy->isforwardMoving && !enemy->isbackwardMoving && !enemy->isrightMoving && !enemy->isleftMoving)
    {

        if(enemy->x() == 100) directionChoose = 0;
        else if(enemy->x() == enemy->scene()->width() - 100 - enemy->pixmap().width()) directionChoose = 1;
        else directionChoose = qrand() % 2;
    }

    switch(directionChoose)
    {
    /*case 0:
        if(!enemy->isforwardMoving) enemy->isforwardMoving = true;
        else enemy->isforwardMoving = false;
        break;
    case 1:
        if(!enemy->isbackwardMoving) enemy->isbackwardMoving = true;
        else enemy->isbackwardMoving = false;
        break;*/
    case 0:
        if(!enemy->isrightMoving) enemy->isrightMoving = true;
        else enemy->isrightMoving = false;
        break;
    case 1:
        if(!enemy->isleftMoving) enemy->isleftMoving = true;
        else enemy->isleftMoving = false;
        break;
    }


    if(!enemy->isshooting)
    {
        enemy->isshooting = true;
        enemy->setPixmap(QPixmap(":/pic/resource/enemyShoot.png").scaled(128, 128));
    }
    else
    {
        enemy->isshooting = false;
        enemy->setPixmap(QPixmap(":/pic/resource/enemy.png").scaled(128, 128));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(player->isinitialing == true) return;

    switch(e->key()) {

    case Qt::Key_W:
        if(!e->isAutoRepeat())
        {
            player->isforwardMoving = true;
        }
        break;

    case Qt::Key_S:
        if(!e->isAutoRepeat())
        {
            player->isbackwardMoving = true;
        }
        break;

    case Qt::Key_A:
        if(!e->isAutoRepeat())
        {
            player->isleftMoving = true;
        }
        break;

    case Qt::Key_D:
        if(!e->isAutoRepeat())
        {
            player->isrightMoving = true;
        }
        break;

    case Qt::Key_J:
        if(!e->isAutoRepeat())
        {
            player->isshooting = true;
        }
        break;

    case Qt::Key_K:
        if(!e->isAutoRepeat())
        {
            player->bomb();
        }
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(player->isinitialing == true) return;

    switch(e->key()) {

    case Qt::Key_W:
        if(!e->isAutoRepeat())
        {
            player->isforwardMoving = false;
        }
        break;

    case Qt::Key_S:
        if(!e->isAutoRepeat())
        {
            player->isbackwardMoving = false;
        }
        break;

    case Qt::Key_A:
        if(!e->isAutoRepeat())
        {
            player->isleftMoving = false;
        }
        break;

    case Qt::Key_D:
        if(!e->isAutoRepeat())
        {
            player->isrightMoving = false;
        }
        break;

    case Qt::Key_J:
        if(!e->isAutoRepeat())
        {
            player->isshooting = false;
        }
        break;

    case Qt::Key_K:
        if(!e->isAutoRepeat())
        {

        }
        break;
    }
}

void MainWindow::updateLCD()
{
    if(this->isWin) return;
    if(!enemy->isDead && !player->isDead)
    {
        ui->score->display(this->score);
        if(this->score <= 0)
        {
            ui->score->display(0);
        }
        ui->currentTolerance->display(TOTAL_HP - enemy->getHP());
        ui->restLife->display(player->getHP());
        ui->restBomb->display(player->getBombNum());
        if(player->getHP() <= 0)
        {
            ui->restLife->display(0);
            ui->restBomb->display(0);
        }
    }
    else if(enemy->isDead)
    {
        ui->currentTolerance->display(66666);
        ui->totalTolerance->display(66666);
        ui->restLife->display(6);
        ui->restBomb->display(6);
        this->isWin = true;
    }
    else if(player->isDead)
    {
        ui->currentTolerance->display(88888);
        ui->totalTolerance->display(88888);
        ui->restLife->display(8);
        ui->restBomb->display(8);
        ui->score->display(0);
    }
}
