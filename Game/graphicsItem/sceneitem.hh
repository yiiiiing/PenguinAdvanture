#ifndef SCENEITEM_HH
#define SCENEITEM_HH

#include <QGraphicsPixmapItem>
#include <QTimer>

// sceneItem means the graphicsPixmapItem in the scene but this item has animation and
// it's position will not change
class SceneItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit SceneItem(const QString itemPath, const int animationFrame, QGraphicsItem *parent = 0);
    virtual void processCollideWithPlayer();
    void setItemPath(const QString newItemPath, const int newAnimationFrame);
    void playAnimation();

private:
    int frameIndex=0;
    QString itemPath;
    int animationFrame;


};

#endif // SCENEITEM_HH
