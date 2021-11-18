#include "hiteffect.hh"

#include <QDebug>

HitEffect::HitEffect(const QString itemPath, const int animationFrame, QGraphicsItem *parent):
      QGraphicsPixmapItem(parent),
      itemPath(itemPath),
      animationFrame(animationFrame)
{
    animationTimer.stop();
    //the hitting effect should be player fast
    animationTimer.setInterval(100);
    connect(&animationTimer, &QTimer::timeout, this, &HitEffect::playAnimation);
}

void HitEffect::playAnimation()
{
    // when play once finished, it's parentItem should be invisible and stop timer
    if (frameIndex > animationFrame){
        qDebug() << "play hit animation";
        animationTimer.stop();
        frameIndex = 0;
        this->parentItem()->setVisible(false);
        this->setVisible(false);
    }
    QString pixelPath = itemPath + QString::number(frameIndex) + ".png";
    QPixmap aniPixel(pixelPath);
    setPixmap(aniPixel);
    setOffset(-aniPixel.width() / 2, -aniPixel.height() / 2);
    frameIndex += 1;

}

