#include "enemybullet.h"

EnemyBullet::EnemyBullet() :Bullet()
{
    this->speed = 10;
    this->inclination = 2;
}

void EnemyBullet::fly()
{
    setPos(x(), y() + this->speed);
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void EnemyBullet::flyL()
{
    setPos(x() - ((float)this->speed / this->inclination), y() + (this->speed * sqrt(this->inclination * this->inclination - 1) / this->inclination));
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void EnemyBullet::flyR()
{
    setPos(x() + ((float)this->speed / this->inclination), y() + (this->speed * sqrt(this->inclination * this->inclination - 1) / this->inclination));
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void EnemyBullet::setBullet(int mode, Minion *minion)
{
    this->setPixmap(QPixmap(":/pic/resource/bomb.png").scaled(40, 40));

    this->setPos(minion->x() + minion->pixmap().width() / 2 - this->pixmap().width() / 2, minion->y() + this->pixmap().height() * 2);

    if(mode == 0)
    {
        this->connect(minion->t, SIGNAL(timeout()), this, SLOT(fly()));
    }
    if(mode == 1)
    {
        this->connect(minion->t, SIGNAL(timeout()), this, SLOT(flyL()));
    }
    if(mode == 2)
    {
        this->connect(minion->t, SIGNAL(timeout()), this, SLOT(flyR()));
    }

    minion->scene()->addItem(static_cast<QGraphicsPixmapItem*>(this));
}

void EnemyBullet::setSpeed(int speed)
{
    this->speed = speed;
}
void EnemyBullet::setInclination(int inclination)
{
    this->inclination = inclination;
}
