#include "enemy.hh"

Enemy::Enemy(QString enemyPath):
    mEnemyPath(enemyPath)
{
    hitEffect = new HitEffect(":/penguin/penguin/hit/hit", 4);
    hitEffect->setParentItem(this);
    hitEffect->setPos(0,0);
    hitEffect->setVisible(false);
    mTransform.scale(-1,1);
}

void Enemy::changeStatus(Enemy::EnemyStatus status)
{
    mStatus = status;
}

QVector2D Enemy::getPosition() const
{
    return position;
}

void Enemy::setPosition(const QVector2D &value)
{
    position = value;
}

void Enemy::setEndX(int value)
{
    endX = value;
}

void Enemy::setStartX(int value)
{
    startX = value;
}

void Enemy::updateEnemy()
{
    // if current x is greater than endX, then walk to left
    // if current x is less than startX, then walk to right
    // then, transform and walkspeed should be changed
    switch (mStatus) {
    case EnemyStatus::Walk:
        if (position.x() > endX || position.x() < startX){
            mTransform.scale(-1,1);
            walkSpeed = -walkSpeed;
        }
        position.setX(position.x() + walkSpeed);
        playWalk();
        break;
    case EnemyStatus::Hit:
        playHit();
        hitEffect->setVisible(true);
        hitEffect->animationTimer.start();
        hitEffect->playAnimation();
        break;
    case EnemyStatus::Die:


        break;
    }
}

void Enemy::playWalk()
{
    if (animationIndex > WalkFrame-1){
        animationIndex = 0;
    }
    QString pixelPath = mEnemyPath + "move" + QString::number(animationIndex) + ".png";
    QPixmap movePixel(pixelPath);
    setPixmap(movePixel);
    setOffset(-movePixel.width() / 2, -movePixel.height() / 2);
    // set transform
    setTransform(mTransform);
    animationIndex += 1;

}

void Enemy::playHit()
{
    // hit only has 1 frame
    QString pixelPath = mEnemyPath + "hit0.png";
    QPixmap hitPixel(pixelPath);
    setPixmap(hitPixel);
    setOffset(-hitPixel.width() / 2, -hitPixel.height() / 2);
    // set transform
    setTransform(mTransform);
}

void Enemy::hitEffectVisble(bool value)
{
    hitEffect->setVisible(value);
}
