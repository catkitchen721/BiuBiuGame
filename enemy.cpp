#include "enemy.h"
#include "enemybullet.h"

Enemy::Enemy() : Minion()
{
    tBullet->start(200);
    t->start(100);
    this->setSpeed(10);
    this->setHP(50000);

    this->isDead = false;

    connect(t, SIGNAL(timeout()), this, SLOT(checkHit()));
}

void Enemy::forwardMoving()
{

    if(isforwardMoving && isleftMoving && (this->y() > 0))
    {
        this->setPos(this->x(), this->y() - this->getSpeed()/sqrt(2));
    }
    else if(isforwardMoving && isrightMoving && (this->y() > 0))
    {
        this->setPos(this->x(), this->y() - this->getSpeed()/sqrt(2));
    }
    else if(isforwardMoving && (this->y() > 0))
    {
        this->setPos(this->x(), this->y() - this->getSpeed());
    }
}

void Enemy::leftMoving()
{
    if(isforwardMoving && isleftMoving && (this->x() > 100))
    {
        this->setPos(this->x() - this->getSpeed()/sqrt(2), this->y());
    }
    else if(isleftMoving && (this->x() > 100))
    {
        this->setPos(this->x() - this->getSpeed(), this->y());
    }
}

void Enemy::rightMoving()
{
    if(isforwardMoving && isrightMoving && (this->x() < this->scene()->width() - 100 - this->pixmap().width()))
    {
        this->setPos(this->x() + this->getSpeed()/sqrt(2), this->y());
    }
    else if(isrightMoving && (this->x() < this->scene()->width() - 100 - this->pixmap().width()))
    {
        this->setPos(this->x() + this->getSpeed(), this->y());
    }
}

void Enemy::backwardMoving()
{
    if(isbackwardMoving && isleftMoving && (this->y() < this->scene()->height() - this->pixmap().height()))
    {
        this->setPos(this->x(), this->y() + this->getSpeed()/sqrt(2));
    }
    else if(isbackwardMoving && isrightMoving && (this->y() < this->scene()->height() - this->pixmap().height()))
    {
        this->setPos(this->x(), this->y() + this->getSpeed()/sqrt(2));
    }
    else if(isbackwardMoving && (this->y() < this->scene()->height() - this->pixmap().height()))
    {
        this->setPos(this->x(), this->y() + this->getSpeed());
    }
}

void Enemy::shooting()
{
    if(isshooting)
    {
        EnemyBullet *b[3];
        b[0] = new EnemyBullet;
        b[1] = new EnemyBullet;
        b[2] = new EnemyBullet;

        if(this->hp <= 30000)
        {
            b[0]->setSpeed(15);
            b[1]->setSpeed(15);
            b[2]->setSpeed(15);
        }
        else if(this->hp <= 10000)
        {
            b[0]->setSpeed(30);
            b[1]->setSpeed(30);
            b[2]->setSpeed(30);
            b[0]->setInclination(2);
            b[1]->setInclination(2);
            b[2]->setInclination(2);
        }

        b[0]->setBullet(0, this);
        b[1]->setBullet(1, this);
        b[2]->setBullet(2, this);
    }
    else
    {
    }
}

void Enemy::checkHit()
{
    if(!this->isDead)
    {
        QList<QGraphicsItem *> colliders = this->collidingItems();
        for(int i=0; i<colliders.size(); ++i)
        {
            if(typeid(*(colliders[i])) == typeid(Bullet))
            {
                if(this->getHP() <= 0)
                {
                    this->isDead = true;
                    return;
                }
                else this->isHit(50);
                this->scene()->removeItem(colliders[i]);
                delete colliders[i];
            }
        }
    }
    else
    {
        this->setVisible(false);
    }
}
