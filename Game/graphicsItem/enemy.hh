#ifndef ENEMY_HH
#define ENEMY_HH

#include <QGraphicsPixmapItem>
#include <QVector2D>
#include <QTimer>
#include "hiteffect.hh"

class Enemy : public QGraphicsPixmapItem
{
public:
    Enemy(QString enemyPath);
    // enemy status
    enum class EnemyStatus{Walk, Hit, Die};

    // change enemy's statues
    void changeStatus(EnemyStatus status);
    // get and set method for enemy's position
    QVector2D getPosition() const;
    void setPosition(const QVector2D &value);

    // set enemy's start X and end X
    void setEndX(int value);
    void setStartX(int value);

    // update enemy position
    void updateEnemy();

    // play enemy walk animation
    void playWalk();

    // play enemy hit animation
    void playHit();

    // set hit effect status
    void hitEffectVisble(bool value);

    // add hit effect to the enemy
    HitEffect* hitEffect;

private:
    // enemy status
    EnemyStatus mStatus = EnemyStatus::Walk;
    // animation index
    int animationIndex = 0;
    // walk frame
    const int WalkFrame = 4;

    // enemy's position
    QVector2D position;
    // enemy's start X and end X (because we only move enemy horizontally)
    int startX;
    int endX;
    // enemy path
    const QString mEnemyPath;

    // enemy speed
    int walkSpeed = 3;

    //define the transform
    QTransform mTransform;


};


#endif // ENEMY_HH
