#include "bullet.h"


Bullet::Bullet()
{
    this->speed = 12;
    this->inclination = 5;
    this->isBomb = false;
}

void Bullet::fly()
{
    setPos(x(), y() - this->speed);
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void Bullet::flyL()
{
    setPos(x() - ((float)this->speed / this->inclination), y() - (this->speed * sqrt(this->inclination * this->inclination - 1) / this->inclination));
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void Bullet::flyR()
{
    setPos(x() + ((float)this->speed / this->inclination), y() - (this->speed * sqrt(this->inclination * this->inclination - 1) / this->inclination));
    if(y() < 0 || x() < 0 || x() > this->scene()->width()) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void Bullet::setBullet(int mode, Minion *minion)
{
    if(qrand() % 2 == 0) {
        this->setPixmap(QPixmap(":/pic/resource/0.png").scaled(30, 30));
    }
    else {
        this->setPixmap(QPixmap(":/pic/resource/1.png").scaled(30, 30));
    }

    if(!this->isBomb)
    {
        this->setPos(minion->x() + minion->pixmap().width() / 2 - this->pixmap().width() / 2, minion->y() - this->pixmap().height());
    }

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

const QRectF Bullet::boundingRect()
{
    qreal w = this->pixmap().width() / 2;
    qreal h = this->pixmap().height() / 2;

    qreal x = this->x() + (this->pixmap().width() / 2) - (w / 2);
    qreal y = this->y() + (this->pixmap().height() / 2) - (h / 2);

    return QRectF(x, y, w, h);
}
