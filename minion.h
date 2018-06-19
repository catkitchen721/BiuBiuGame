#ifndef MINION_H
#define MINION_H


#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QPainter>

class Minion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Minion();
    bool isinitialing;
    bool isforwardMoving;
    bool isleftMoving;
    bool isrightMoving;
    bool isbackwardMoving;
    bool isshooting;
    QTimer *t;
    QTimer *tBullet;

    void setSpeed(int speed);
    int getSpeed();

    void setHP(int hp);
    int getHP();
    void isHit(int hpConsume);

    virtual const QRectF boundingRect();

    friend class bullet;

private slots:
    virtual void forwardMoving() = 0;
    virtual void leftMoving() = 0;
    virtual void rightMoving() = 0;
    virtual void backwardMoving() = 0;
    virtual void shooting() = 0;
    virtual void checkHit() = 0;
    void stopInitialGo();


protected:
    int speed;
    int hp;
};

#endif // MINION_H
