#include "questlight.hh"

#include <QDebug>

QuestLight::QuestLight(const QPixmap &pixmap, QGraphicsItem * parent)
    : QGraphicsPixmapItem(pixmap, parent)
{

}

bool QuestLight::isQuestClicked()
{
    return isClicked;

}

void QuestLight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     if(event->button() == Qt::LeftButton) {
         isClicked = true;
         //qDebug() << this->isSelected();
     }

}

void QuestLight::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isClicked = false;
    }

}
