#include "sceneitem.hh"

SceneItem::SceneItem(const QString itemPath, const int animationFrame, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent),
      itemPath(itemPath),
      animationFrame(animationFrame)
{

}

void SceneItem::processCollideWithPlayer()
{

}

void SceneItem::setItemPath(const QString newItemPath, const int newAnimationFrame)
{
    itemPath = newItemPath;
    animationFrame = newAnimationFrame;
}

void SceneItem::playAnimation()
{
    if (frameIndex > animationFrame){
        frameIndex = 0;
    }
    QString pixelPath = itemPath + QString::number(frameIndex) + ".png";
    QPixmap aniPixel(pixelPath);
    setPixmap(aniPixel);
    frameIndex += 1;
}
