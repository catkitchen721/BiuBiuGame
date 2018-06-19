#ifndef ENEMY_H
#define ENEMY_H

#include "minion.h"

#define TOTAL_HP 50000

class Enemy : public Minion
{
public:
    Enemy();
    virtual void forwardMoving();
    virtual void leftMoving();
    virtual void rightMoving();
    virtual void backwardMoving();
    virtual void shooting();

    bool isDead;

public slots:
    virtual void checkHit();

};

#endif // ENEMY_H
