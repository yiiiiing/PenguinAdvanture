#ifndef QUESTLIGHT_HH
#define QUESTLIGHT_HH

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class QuestLight : public QGraphicsPixmapItem
{
public:
    explicit QuestLight(const QPixmap &pixmap, QGraphicsItem *parent = 0);
    bool isQuestClicked();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    bool isClicked = false;
};

#endif // QUESTLIGHT_HH
