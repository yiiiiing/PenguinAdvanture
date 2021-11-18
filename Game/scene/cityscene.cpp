#include "cityscene.hh"
#include <QDebug>

CityScene::CityScene(QObject *parent) : BasicScene(parent)
{

    initScene();
    mTimer.start();
    mTimer.setInterval(50);
    connect(&mTimer, &QTimer::timeout, this, &CityScene::updateScene);
    connect(&mTimer, &QTimer::timeout, this, &CityScene::updateEnemy);

    mCurrentScene = SceneType::City;

}

void CityScene::moveScene()
{
    changeWorldShift();
    // move all graphicItems and backgroundItems
    mPlayer->setX(mPlayer->mCurrentPosition.x() - m_worldShift);
    const qreal ratio = qreal(m_worldShift) / MaxWorldShift;
    applyParallax(ratio, cityBackground);
    applyParallax(ratio, cityTileImage);



}

void CityScene::initScene()
{
    setSceneRect(0,0,SceneWidth, SceneHeight);
    cityBackground = new BackgroundItem(QPixmap(":/backgroundImage/images/cityBackground.png"));
    cityBackground->setPos(0,0);
    addItem(cityBackground);

    cityTileImage = new BackgroundItem(QPixmap(":/mapImage/images/cityMap.png"));
    cityTileImage->setPos(0,0);
    addItem(cityTileImage);

    mPlayer->mCurrentMap = new CityMap;
   // std::cout <<mPlayer->mCurrentMap->getMapName() <<std::endl;
    mPlayer->mCurrentPosition.setX(mPlayer->mCurrentMap->getPlayerStartPosition().x());
    mPlayer->mCurrentPosition.setY(mPlayer->mCurrentMap->getPlayerStartPosition().y());
    mPlayer->setPos(mPlayer->mCurrentPosition.x(), mPlayer->mCurrentPosition.y());

    // add enemys
    initEnemys(":/animation/animation/enemyGirl/");

    addItem(mPlayer);

    // add bus window for taking bus
    busWindow = this->addWidget(busTalkWindow);
    busWindow->setParentItem(mPlayer);
    busWindow->setPos(-30, -150);
    busWindow->setVisible(false);
    busWindow->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    connect(busTalkWindow, &BusWindow::selectedBus,this, &CityScene::processBusWindow);

    // add bank window
    bank = new Bank;
    bankWindow = this->addWidget(bank->bankWindow);
    bankWindow->setParentItem(mPlayer);
    bankWindow->setPos(-30, -150);
    bankWindow->setVisible(true);
    bankWindow->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    connect(bank->bankWindow, &TalkWindow::windowReturnAnswer, this, &CityScene::processBankWindowResponse);

}

void CityScene::updateItemState()
{
    // set visible or invisible for bus window
    if(distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerEndPosition()) < TileWidth){
        busWindow->setVisible(true);
    }else if (distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerEndPosition()) > 5*TileWidth){
        busWindow->setVisible(false);
    }

    // set visible or invisible for bank window
    if(distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getGraphicsItemPosition("bank")) < TileWidth){
        bankWindow->setVisible(true);
    }else if (distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getGraphicsItemPosition("bank")) > 5*TileWidth){
        bankWindow->setVisible(false);
        // if bank's window automatically close, then set bank window from begining to display
        bank->processCollideWithPlayer();
    }

}

void CityScene::processBusWindow(QString busNumber)
{
    //surviveEnemys();
    busWindow->setVisible(false);
    if (busNumber=="6B"){
        emit changeScene(SceneType::City, SceneType::University);
        //emit goToUniversity("city");
        return;
    }
}

void CityScene::processBankWindowResponse(bool answer)
{
    // if answer is true, then change the bank card info
    if (answer){
        mPlayer->ifBankCard = true;
        emit hasGotBankCard();
        qDebug() << "If has bank card in city scene: true";
       // setIfGetBankCard(true);
    }

}

