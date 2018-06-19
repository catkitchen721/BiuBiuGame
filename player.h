#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "minion.h"

class Player : public Minion
{
public:
    Player();
    virtual void forwardMoving();
    virtual void leftMoving();
    virtual void rightMoving();
    virtual void backwardMoving();
    virtual void shooting();

    bool isDead;

    void bomb();
    void setBombNum(int num);
    int getBombNum();

public slots:
    virtual void checkHit();

private:
    QMediaPlayer *shootingSound;
    QMediaPlaylist *playlist;
    int bombNum;
};

#endif // PLAYER_H
