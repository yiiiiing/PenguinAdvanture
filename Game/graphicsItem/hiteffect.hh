#ifndef HITEFFECT_HH
#define HITEFFECT_HH

#include <QGraphicsPixmapItem>
#include <QTimer>

class HitEffect : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit HitEffect(const QString itemPath, const int animationFrame, QGraphicsItem *parent = 0);
    void playAnimation();
    QTimer animationTimer;

private:
    int frameIndex=0;
    QString itemPath;
    int animationFrame;
};

#endif // HITEFFECT_HH
