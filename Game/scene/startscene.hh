#ifndef STARTSCENE_HH
#define STARTSCENE_HH

#include <QGraphicsScene>
#include <QGraphicsItemAnimation>
#include <QVector>
#include <QTimer>
#include <QTimeLine>
#include "graphicsItem/backgrounditem.hh"
#include "graphicsItem/questlight.hh"
#include "Constants.hh"
#include <QMediaPlaylist>
#include <QMediaPlayer>

class StartScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit StartScene(QObject *parent = 0);
    void startPlayPrologue();
signals:
    void startGame();
private:
    void initialScene();
    void playAnimation(QMediaPlayer::State state);

    // there are 4 pictures in the start scene in total
    const int totalPictureNum = 4;
    // define pictures in start scene
    QVector<BackgroundItem* > pictures;

    // current picture index
    int currentPictureIndex = 0;

    // define Animation timer
    QTimeLine* mTimeLine;
    QGraphicsItemAnimation* pictureAnimation;

    // define timer to check if startGame button is clicked
    QTimer checkTimer;

    // add start game button
    QuestLight* startGameButton;

    // add prologue
    QMediaPlaylist* prologueList;
    QMediaPlayer* prologue;

};

#endif // STARTSCENE_HH
