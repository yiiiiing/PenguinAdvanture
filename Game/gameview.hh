#ifndef GAMEVIEW_HH
#define GAMEVIEW_HH

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QObject>
#include <QSoundEffect>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMap>
#include "scene/airportscene.hh"
#include "scene/cityscene.hh"
#include "scene/tamperescene.hh"
#include "scene/universityscene.hh"
#include "scene/basicscene.hh"
#include "scene/hospitalscene.hh"
#include "scene/startscene.hh"
#include "scene/endscene.hh"
#include "window/login.hh"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView();
    ~GameView();
    void initView();
    void startView();
    void setCurrentScene(BasicScene::SceneType currentScene);

private:
    // if basic scene emit the signal to change scene, then GameView class process
    void processChangeScene(BasicScene::SceneType fromScene, BasicScene::SceneType toScene);
    void setSound(QSoundEffect* sound, QString soundPath);

    // add scene
    TampereScene* tampereScene = new TampereScene;
    AirportScene* airportScene = new AirportScene;
    CityScene* cityScene = new CityScene;
    UniversityScene* universityScene = new UniversityScene;
    HospitalScene* hospitalScene = new HospitalScene;
    StartScene* startScene = new StartScene;
    EndScene* endScene = new EndScene;

    // add all the scene to map
    QMap<BasicScene::SceneType, BasicScene*> gameScenes;

    // add sound
    QMediaPlaylist* playlist;
    QMediaPlayer* backGoundMusic;

};


#endif // GAMEVIEW_HH
