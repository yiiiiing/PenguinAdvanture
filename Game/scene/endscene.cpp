#include "endscene.hh"

EndScene::EndScene(QObject *parent):QGraphicsScene(parent)
{
    BackgroundItem* picture = new BackgroundItem(QPixmap(":/backgroundImage/images/endScene0.png"));
    picture->setPos(0,0);
    this->addItem(picture);

}
