#include "startscene.hh"

StartScene::StartScene(QObject *parent):QGraphicsScene(parent)
{
    initialScene();

    // 2s for picture animation
    mTimeLine = new QTimeLine(2 * 1000);
    mTimeLine->setFrameRange(0,5);
    mTimeLine->stop();

    pictureAnimation = new QGraphicsItemAnimation;
    pictureAnimation->setTimeLine(mTimeLine);

    // add prologue
    prologueList = new QMediaPlaylist;
    prologueList->addMedia(QUrl("qrc:/prologue/prologue/sentence0.mp3"));
    prologueList->addMedia(QUrl("qrc:/prologue/prologue/sentence1.mp3"));
    prologueList->addMedia(QUrl("qrc:/prologue/prologue/sentence2.mp3"));
    prologueList->addMedia(QUrl("qrc:/prologue/prologue/sentence3.mp3"));
    prologueList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    prologueList->setCurrentIndex(currentPictureIndex);

    prologue = new QMediaPlayer;
    prologue->setPlaylist(prologueList);
    prologue->stop();

    // connect mediaPlayer with play rotation animation
    // when mediaPlayer stop, then begin to rotate
    connect(prologue, &QMediaPlayer::stateChanged, this, &StartScene::playAnimation);


    // when finish one animation, set current picture invisible
    // and stop animation timer, and clear animtion
    connect(mTimeLine, &QTimeLine::finished, [this](){
        pictures.at(currentPictureIndex)->setVisible(false);
        pictureAnimation->clear();
        mTimeLine->stop();
        currentPictureIndex += 1;
        prologueList->setCurrentIndex(currentPictureIndex);
        prologue->play();
    });
}

void StartScene::startPlayPrologue()
{
    prologue->play();

}

void StartScene::initialScene()
{
    // set fixed scene size
    setSceneRect(0,0,1200, 788);

    // add background picture into scene
    for (int i = totalPictureNum-1; i >= 0; --i){
        QString picturePath = ":/backgroundImage/images/startScene" + QString::number(i) + ".png";
        BackgroundItem* pic = new BackgroundItem(QPixmap(picturePath));
        pictures.push_front(pic);
        pic->setPos(0,0);
        this->addItem(pic);
    }

    // let last picture has startGame button
    startGameButton = new QuestLight(QPixmap(":/otherImage/images/startButton.png"));
    addItem(startGameButton);
    startGameButton->setParentItem(pictures.at(totalPictureNum-1));
    startGameButton->setPos(600,654);
    startGameButton->setVisible(false);

    checkTimer.start();
    checkTimer.setInterval(100);
    connect(&checkTimer, &QTimer::timeout, [this](){
        if (this->startGameButton->isQuestClicked()){
            emit startGame();
            checkTimer.stop();
        }
    });
}

void StartScene::playAnimation(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState){
        if (currentPictureIndex == totalPictureNum-1){
            // if prologue is finished, then make start button visible
            startGameButton->setVisible(true);
            return;
        }
        pictureAnimation->setItem(pictures.at(currentPictureIndex));
        pictureAnimation->setRotationAt(1, -90);
        mTimeLine->start();
    }

}
