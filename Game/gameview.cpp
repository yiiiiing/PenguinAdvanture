#include "gameview.hh"

#include <QDebug>

GameView::GameView()
{

    // add all the scene to the map
    gameScenes.insert(BasicScene::SceneType::Airport, airportScene);
    gameScenes.insert(BasicScene::SceneType::University, universityScene);
    gameScenes.insert(BasicScene::SceneType::City, cityScene);
    gameScenes.insert(BasicScene::SceneType::Tampere, tampereScene);
    gameScenes.insert(BasicScene::SceneType::Hospital, hospitalScene);

    initView();

}

GameView::~GameView()
{
    this->close();
    // delete all scene objects
    QMap<BasicScene::SceneType, BasicScene*>::Iterator sceneIterator;
    sceneIterator = gameScenes.begin();
    while (sceneIterator != gameScenes.end())
    {
        delete sceneIterator.value();
        sceneIterator.value() = nullptr;
        ++sceneIterator;
    }

}

void GameView::initView()
{

    // add sound (background music)
    playlist = new QMediaPlaylist;
    // order: Start=0, End, Tampere, Airport, City, University, Hospital
    playlist->addMedia(QUrl("qrc:/music/music/startScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/endScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/tampereScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/airportScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/cityScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/schoolScene.mp3"));
    playlist->addMedia(QUrl("qrc:/music/music/hospitalScene.mp3"));

    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    playlist->setCurrentIndex(BasicScene::SceneType::Start);

    backGoundMusic =  new QMediaPlayer;
    backGoundMusic->setPlaylist(playlist);
    backGoundMusic->setVolume(50);

    this->setRenderHint(QPainter::Antialiasing);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // connect start scene with airports scene
    connect(startScene, &StartScene::startGame, [this](){
        setCurrentScene(BasicScene::SceneType::Airport);
    });

    // connect each scene in the game
    auto sceneIter = gameScenes.begin();
    while (sceneIter != gameScenes.end()) {
        connect(sceneIter.value(), &BasicScene::changeScene, this, &GameView::processChangeScene);
        connect(sceneIter.value(), &BasicScene::fellInTrap, [this](){
            hospitalScene->processDieWithTrap();
        });
        connect(sceneIter.value(), &BasicScene::collideWithEnemy, [this](){
            hospitalScene->processDieWithEnemy();
        });
        ++sceneIter;
    };

    // if at the tampereScene, the bus arrive at the destination, then change the current scene
    connect(tampereScene, &TampereScene::arriveAt, this, &GameView::setCurrentScene);

    // connect university scene(lase scene) with the end scene
    connect(universityScene, &UniversityScene::endView, [this](){
        setCurrentScene(BasicScene::SceneType::End);
    });

    // connect city scene and university scene to give bank card info
    connect(cityScene, &CityScene::hasGotBankCard, [this](){
        universityScene->mPlayer->ifBankCard = true;
    });

}

void GameView::startView()
{
    // set start scene is startScene
    setCurrentScene(BasicScene::SceneType::Start);

    // play background music
    backGoundMusic->play();

    this->show();


}

// this code is needed to be clean (enum class scene{})
void GameView::setCurrentScene(BasicScene::SceneType currentScene)
{
    playlist->setCurrentIndex(currentScene);
    switch (currentScene) {
    case BasicScene::SceneType::Start:
        setScene(startScene);
        setFixedSize(startScene->sceneRect().size().toSize());
        startScene->startPlayPrologue();
        //qDebug() << "start scene begine";
        return;
    case BasicScene::SceneType::End:
        setScene(endScene);
        setFixedSize(endScene->sceneRect().size().toSize());
        return;
    // currentScene is neither startScene nor endScene
    default:
        //qDebug() << "game scenes begine";
        setScene(gameScenes.value(currentScene));
        setFixedSize(gameScenes.value(currentScene)->sceneRect().size().toSize());
        gameScenes.value(currentScene)->surviveEnemys();
        return;
    }
}

void GameView::processChangeScene(BasicScene::SceneType fromScene, BasicScene::SceneType toScene)
{
    // if from Scene is hospital then directly set currentScene is to scene
    // if toScene is hospital then directly set currentScene is toScene, don't need go to tampereScene first
    if (fromScene == BasicScene::SceneType::Hospital || toScene == BasicScene::SceneType::Hospital){
        hospitalScene->setPreviousScene(fromScene);
        setCurrentScene(toScene);
        gameScenes.value(toScene)->reloadScene();
        return;
    }

    if (toScene == BasicScene::SceneType::City){
        // if to city center, player's position is at beginning of city
        cityScene->mPlayer->mCurrentPosition = cityScene->mPlayer->mCurrentMap->getPlayerStartPosition();
    }

    // if not from the hospital or to hospital scene, then now, current scene is tampereScene
    setCurrentScene(BasicScene::SceneType::Tampere);
    tampereScene->setStartAndEnd(fromScene, toScene);
    tampereScene->playAnimation();
}

void GameView::setSound(QSoundEffect *sound, QString soundPath)
{
    sound->setSource(QUrl(soundPath));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->setVolume(0.25f);
}

