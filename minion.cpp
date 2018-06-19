#include "minion.h"

Minion::Minion() :
    isforwardMoving(false), isleftMoving(false), isrightMoving(false), isbackwardMoving(false), isshooting(false),
    t(new QTimer), tBullet(new QTimer)
{
    connect(t, SIGNAL(timeout()), this, SLOT(forwardMoving()));
    connect(t, SIGNAL(timeout()), this, SLOT(leftMoving()));
    connect(t, SIGNAL(timeout()), this, SLOT(rightMoving()));
    connect(t, SIGNAL(timeout()), this, SLOT(backwardMoving()));
    connect(tBullet, SIGNAL(timeout()), this, SLOT(shooting()));
}

void Minion::setSpeed(int speed)
{
    this->speed = speed;
}

int Minion::getSpeed()
{
    return this->speed;
}

const QRectF Minion::boundingRect()
{
    qreal w = this->pixmap().width() / 4;
    qreal h = this->pixmap().height() / 4;

    qreal x = this->x() + (this->pixmap().width());
    qreal y = this->y() + (this->pixmap().height());

    return QRectF(x, y, w, h);
}


void Minion::stopInitialGo()
{
    isforwardMoving = false;
    this->setSpeed(5);
    t->start(10);
    isinitialing = false;
}

void Minion::setHP(int hp)
{
    this->hp = hp;
}

int Minion::getHP()
{
    return this->hp;
}

void Minion::isHit(int hpConsume)
{
    this->hp -= hpConsume;
}

