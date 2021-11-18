#ifndef BACKGROUNDITEM_HH
#define BACKGROUNDITEM_HH

#include <QGraphicsPixmapItem>

class BackgroundItem : public QGraphicsPixmapItem
{
public:
    explicit BackgroundItem(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};


#endif // BACKGROUNDITEM_HH
