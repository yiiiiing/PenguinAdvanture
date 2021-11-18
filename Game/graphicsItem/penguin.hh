#ifndef PENGUIN_HH
#define PENGUIN_HH

#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>
#include<string>

// notice: QObject should be the first to inherite
class Penguin : public QGraphicsPixmapItem
{
public:
    explicit Penguin(QGraphicsItem* parent =0);
    void standAnimation(QTransform transform);
    void walkAnimation(QTransform transform);
    void attackAnimation(QTransform transform);
    void dieAnimation(QTransform transform);
    void jumpAnimation(QTransform transform);
    void hitAnimation();
    int mFrameIndex = 0;

    // define how many frames that the animation contains
    const int STAND_FRAME = 8;
    const int ATTACK_FRAME = 7;
    const int WALK_FRAME = 6;
    const int DIE_FRAME = 5;
    const int HIT_FRAME = 5;

};

#endif // PENGUIN_HH
