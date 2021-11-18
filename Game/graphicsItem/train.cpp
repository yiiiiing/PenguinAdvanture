#include "train.hh"

Train::Train(QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    QString pixelPath = ":/animation/animation/train/train.png";
    QPixmap trainPixel(pixelPath);
    setPixmap(trainPixel);

    // define talkWindow
    trainWindow = new TalkWindow();
    initTrainWindow();

}

void Train::initTrainWindow()
{
    trainWindow->setButtonVisible("right", true);
    trainWindow->setButtonText("right", "Yes");
    trainWindow->setButtonVisible("left", true);
    trainWindow->setButtonText("left", "No");
    trainWindow->setDisplayText("Would you like to take the train?");
}
