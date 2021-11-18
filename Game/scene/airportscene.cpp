#include "airportscene.hh"

#include <QTransform>
#include <QDebug>

AirportScene::AirportScene(QObject *parent): BasicScene(parent)
{

    initScene();

    // connect scene timer and updating scene
    mTimer.start();
    mTimer.setInterval(50);
    connect(&mTimer, &QTimer::timeout, this, &AirportScene::updateScene);

    // connect train timer and train animation
    trainTimer.stop();
    trainTimer.setInterval(100);
    connect(&trainTimer, &QTimer::timeout, this, &AirportScene::trainAnimation);

    // connect npc timer and npc(npc don't need to update fast as player)
    animationTimer.setInterval(500);
    animationTimer.start();
    connect(&animationTimer, &QTimer::timeout, tutor, &SceneItem::playAnimation);
    connect(&animationTimer, &QTimer::timeout, airCrew, &SceneItem::playAnimation);
    connect(&animationTimer, &QTimer::timeout, erp, &SceneItem::playAnimation);
    connect(&mTimer, &QTimer::timeout, this, &AirportScene::updateEnemy);

    mCurrentScene = SceneType::Airport;

}

void AirportScene::moveScene()
{
    changeWorldShift();
    // move all graphicItems and backgroundItems
    mPlayer->setX(mPlayer->mCurrentPosition.x() - m_worldShift);
    tutor->setX(tutorPosition.x() - m_worldShift);
    airCrew->setX(airCrewPosition.x() - m_worldShift);
    erp->setX(erpPosition.x() - m_worldShift);
    train->setX(trainPosition.x() - m_worldShift);

    const qreal ratio = qreal(m_worldShift) / MaxWorldShift;
    applyParallax(ratio, airportsBackground);
    applyParallax(ratio, airportsTileImage);

}

void AirportScene::initScene()
{
    setSceneRect(0,0,SceneWidth, SceneHeight);
    airportsBackground = new BackgroundItem(QPixmap(":/backgroundImage/images/airportsBackground.png"));
    airportsBackground->setPos(0,0);
    addItem(airportsBackground);

    airportsTileImage = new BackgroundItem(QPixmap(":/mapImage/images/airportsMap.png"));
    airportsTileImage->setPos(0,0);
    addItem(airportsTileImage);

    mPlayer->mCurrentMap = new AirportMap;
    mPlayer->mCurrentPosition.setX(mPlayer->mCurrentMap->getPlayerStartPosition().x());
    mPlayer->mCurrentPosition.setY(mPlayer->mCurrentMap->getPlayerStartPosition().y());
    mPlayer->setPos(mPlayer->mCurrentPosition.x(), mPlayer->mCurrentPosition.y());


    // add enemys
    initEnemys(":/animation/animation/enemyBoy/");

    // add tutor
    tutor = new Tutor();
    tutorPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("tutor");
    tutor->setPos(tutorPosition.x(),tutorPosition.y());
    // add quest light
    questClickTutor = new QuestLight(QPixmap(":/otherImage/images/quest.png"));
    addItem(questClickTutor);
    questClickTutor->setParentItem(tutor);
    questClickTutor->setPos(10,-55);
    // add talk window
    tutorWindow = this->addWidget(tutor->tutorWindow);
    tutorWindow->setParentItem(tutor);
    tutorWindow->setPos(-30, -90);
    tutorWindow->setVisible(false);

    // add airCrew
    airCrew = new AirCrew();
    airCrewPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("airCrew");
    airCrew->setPos(airCrewPosition.x(),airCrewPosition.y());
    // add quest light
    questClickAirCrew = new QuestLight(QPixmap(":/otherImage/images/quest.png"));
    addItem(questClickAirCrew);
    questClickAirCrew->setParentItem(airCrew);
    questClickAirCrew->setPos(10,-55);
    // add talk window for airCrew
    airCrewWindow = this->addWidget(airCrew->airCrewWindow);
    airCrewWindow->setParentItem(airCrew);
    airCrewWindow->setPos(-30, -90);
    airCrewWindow->setVisible(false);

    // add erp
    erp = new SceneItem(":/animation/animation/erp/erp", erpFrame);
    erpPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("erp");
    erp->setPos(erpPosition.x(),erpPosition.y());

    // add train
    train =  new Train();
    train->setVisible(false);
    train->setY(train->trainBeginPosition.y());
    trainPosition = train->trainBeginPosition;

    // add talk window for train
    trainWindow = this->addWidget(train->trainWindow);
    trainWindow->setParentItem(mPlayer);
    trainWindow->setPos(-30, -150);
    trainWindow->setVisible(false);
    trainWindow->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    connect(train->trainWindow, &TalkWindow::windowReturnAnswer, this, &AirportScene::trainWindowResponse);

    // add bus window for taking bus
    busWindow = this->addWidget(busTalkWindow);
    busWindow->setParentItem(mPlayer);
    busWindow->setPos(-30, -150);
    busWindow->setVisible(false);
    // bus window will not transform as its parent item player
    busWindow->setFlag(QGraphicsItem::ItemIgnoresTransformations);

    connect(busTalkWindow, &BusWindow::selectedBus,this, &AirportScene::processBusWindow);

    addItem(tutor);
    addItem(airCrew);
    addItem(erp);
    addItem(mPlayer);
    addItem(train);

}

void AirportScene::updateItemState()
{
    if (tutor->x() < SceneWidth && tutor->x() > 0){
        tutor->setVisible(true);
    }else{
        tutor->setVisible(false);
        tutorWindow->setVisible(false);
        tutor->tutorWindow->close();
    }
    //qDebug() <<airCrew->x();

    if (airCrew->x() < SceneWidth && airCrew->x() >0){
        airCrew->setVisible(true);
    }else{
        airCrew->setVisible(false);
        airCrewWindow->setVisible(false);
        airCrew->airCrewWindow->close();
    }

    if (erp->x() < SceneWidth && erp->x() >0){
        erp->setVisible(true);
    }else{
        erp->setVisible(false);
    }

    if (train->x()> SceneWidth && train->x() <0){
        train->setVisible(false);
        trainWindow->setVisible(false);
        train->trainWindow->close();
    }

    // click the the light button of the air crews
    if (questClickAirCrew->isQuestClicked()){
        airCrewWindow->setVisible(true);
        airCrew->processCollideWithPlayer();
    }

    // click the light button of the tutor
    if (questClickTutor->isQuestClicked()){
        tutorWindow->setVisible(true);
        tutor->processCollideWithPlayer();
    }

    // if player is at  train starting position
    if (std::abs(mPlayer->mCurrentPosition.x()-train->trainBeginPosition.x()) < 10
        && mPlayer->y() < (train->y() + train->trainHeight)){
        //qDebug() << "at train starting postion";
        // now train's pos is mPlayer's pos
        trainPosition = train->trainBeginPosition;
        trainWindow->setVisible(true);
        QTransform transform;
        trainWindow->setTransform(transform);
    }

    // if player is at train ending button
    if (std::abs(mPlayer->mCurrentPosition.x()-train->trainEndPosition.x())<10
        && mPlayer->y() < (train->y() + train->trainHeight)){
        //qDebug() << "at train end postion";
        // now train's pos is mPlayer's pos
        trainPosition = train->trainEndPosition;
        trainWindow->setVisible(true);
        QTransform transform;
        trainWindow->setTransform(transform);
    }

    // if player is not on the train platform but not close the trainWindow, then system automatically close
    if (trainWindow->isVisible() && mPlayer->y() > (train->y() + train->trainHeight)){
        trainWindow->close();
        train->trainWindow->close();
    }
    // check if player collides with bus window
    if(distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerEndPosition()) < TileWidth){
        busWindow->setVisible(true);
    }else if (distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerEndPosition()) > 5*TileWidth){
        busWindow->setVisible(false);
    }

}


void AirportScene::trainWindowResponse(bool answer)
{
    train->trainWindow->close();
    trainWindow->setVisible(false);
    if (answer){
        mPlayer->setVisible(false);
        train->setVisible(true);
        // if take the train,
        // check where is the train (begin or end)
        if (std::abs(trainPosition.x() - train->trainBeginPosition.x()) < 30){
            trainDirection = 1;
            trainEndPosition = train->trainEndPosition;
        }else if(std::abs(trainPosition.x() - train->trainEndPosition.x()) < 30){
            trainDirection = -1;
            trainEndPosition = train->trainBeginPosition;
        }
        trainTimer.start();
    }else{
        // if don't take the train
        mPlayer->setVisible(true);
        train->setVisible(false); // make sure that train is invisible
    }

}

void AirportScene::trainAnimation()
{
    // if train move to right
    if(trainDirection > 0){
        if (trainPosition.x() > trainEndPosition.x()){
            // stop
            trainDirection = 0;
            trainEndPosition = {0,0};
            trainTimer.stop();
            mPlayer->setVisible(true);
            trainPosition = train->trainEndPosition;
        }
        trainPosition.setX(trainPosition.x() + 20);
        mPlayer->mCurrentPosition.setX(trainPosition.x() + 0.5 * train->trainWidth);


        return;
    }

    // if train move to left
    if(trainDirection < 0){
        if (trainPosition.x() < trainEndPosition.x()){
            // stop
            trainDirection = 0;
            trainEndPosition = {0,0};
            trainTimer.stop();
            mPlayer->setVisible(true);
            trainPosition = train->trainBeginPosition;
        }
        trainPosition.setX(trainPosition.x() - 20);
        mPlayer->mCurrentPosition.setX(trainPosition.x());
        return;
    }

}

void AirportScene::processBusWindow(QString busNumber)
{
    busWindow->setVisible(false);
    //surviveEnemys();
    if (busNumber=="6B"){
        emit changeScene(SceneType::Airport, SceneType::University);
        //emit goToUniversity("airports");
        return;
    }
    else if (busNumber=="1A"){
        emit changeScene(SceneType::Airport, SceneType::City);
        //emit goToCity("airports");
        //qDebug() << "go to city";
        return;
    }
}
