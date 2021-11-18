#ifndef ENDSCENE_HH
#define ENDSCENE_HH

#include <QGraphicsScene>
#include "graphicsItem/backgrounditem.hh"

class EndScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EndScene(QObject *parent = 0);
};

#endif // ENDSCENE_HH
