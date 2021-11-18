#include "penguin.hh"

Penguin::Penguin(QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
}

void Penguin::standAnimation(QTransform transform)
{

    QString pixelPath = ":/penguin/penguin/stand/stand0.png";
    QPixmap standPixel(pixelPath);
    setPixmap(standPixel);
    setOffset(-standPixel.width() / 2, -standPixel.height() / 2);
    setTransform(transform);
    //mFrameIndex += 1;
}

void Penguin::walkAnimation(QTransform transform)
{
    if (mFrameIndex > WALK_FRAME-1){
        mFrameIndex = 0;
    }
    QString pixelPath = ":/penguin/penguin/move/move" + QString::number(mFrameIndex) + ".png";
    QPixmap movePixel(pixelPath);
    setPixmap(movePixel);
    setOffset(-movePixel.width() / 2, -movePixel.height() / 2);
    setTransform(transform);
    mFrameIndex += 1;

}

// attack, die, jump, hit animation only play once
void Penguin::attackAnimation(QTransform transform)
{
    QString pixelPath = ":/penguin/penguin/attack/attack" + QString::number(mFrameIndex) + ".png";
    QPixmap attackPixel(pixelPath);
    setPixmap(attackPixel);
    setOffset(-attackPixel.width() / 2, -attackPixel.height() / 2);
    setTransform(transform);
    mFrameIndex += 1;
}

void Penguin::dieAnimation(QTransform transform)
{
    QString pixelPath = ":/penguin/penguin/die/die" + QString::number(mFrameIndex) + ".png";
    QPixmap diePixel(pixelPath);
    setPixmap(diePixel);
    setOffset(-diePixel.width() / 2, -diePixel.height() / 2);
    setTransform(transform);
    mFrameIndex += 1;
}

void Penguin::jumpAnimation(QTransform transform)
{
    QString pixelPath = ":/penguin/penguin/stand/stand0.png";
    QPixmap jumpPixel(pixelPath);
    setPixmap(jumpPixel);
    setOffset(-jumpPixel.width() / 2, -jumpPixel.height() / 2);
    setTransform(transform);
}

void Penguin::hitAnimation()
{
    QString pixelPath = ":/penguin/penguin/hit/hit" + QString::number(mFrameIndex) + ".png";
    QPixmap hitPixel(pixelPath);
    setPixmap(hitPixel);
    setOffset(-hitPixel.width() / 2, -hitPixel.height() / 2);
    mFrameIndex += 1;
}

