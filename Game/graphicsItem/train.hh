#ifndef TRAIN_HH
#define TRAIN_HH

#include <QGraphicsPixmapItem>
#include <QVector2D>
#include "Constants.hh"
#include "window/talkwindow.hh"

class Train : public QGraphicsPixmapItem
{
public:
    explicit Train(QGraphicsItem* parent =0);
    const QVector2D trainBeginPosition = {25*TileWidth,4*TileHeight};
    const QVector2D trainEndPosition = {61*TileWidth,4*TileHeight};

    const int trainWidth = 515; // 8.04 tiles
    const int trainHeight = 81; // 3 tiles

    // the window interacting with train
    TalkWindow* trainWindow;
    void initTrainWindow();
private:
    void windowQuestionResponse(bool answer);


};

#endif // TRAIN_HH
