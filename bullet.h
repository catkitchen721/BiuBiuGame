#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <cmath>

#include "player.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
    virtual void setBullet(int mode, Minion *minion);

    virtual const QRectF boundingRect();

    bool isBomb;

public slots:
    virtual void fly();
    virtual void flyL();
    virtual void flyR();

protected:
    int speed;
    float inclination;
};

#endif // BULLET_H
