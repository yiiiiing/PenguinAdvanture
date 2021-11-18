#include "universityscene.hh"

#include <QDebug>

UniversityScene::UniversityScene(QObject *parent) : BasicScene(parent)
{


    initScene();

    // connect scene timer and updating scene
    mTimer.start();
    mTimer.setInterval(50);
    connect(&mTimer, &QTimer::timeout, this, &UniversityScene::updateScene);

    // connect npc timer and npc(npc don't need to update fast as player)
    animationTimer.setInterval(500);
    animationTimer.start();
    connect(&animationTimer, &QTimer::timeout, teacher, &SceneItem::playAnimation);
    connect(&animationTimer, &QTimer::timeout, cleaner, &SceneItem::playAnimation);

    // connect teacher with this scene to check if player has bank card
    connect(teacher, &Teacher::checkBankCard, this, &UniversityScene::returnBankCardInfo);
    // in the returnBankCardInfo, emit the signal (ifPlayerHasBankCard)
    connect(this, &UniversityScene::ifPlayerHasBankCard, teacher, &Teacher::getIfHasBankCard);


    connect(teacher, &Teacher::endGame, this, &UniversityScene::endView);

    mCurrentScene = SceneType::University;

}

void UniversityScene::moveScene()
{
    changeWorldShift();
    // move all graphicItems and backgroundItems
    mPlayer->setX(mPlayer->mCurrentPosition.x() - m_worldShift);
    teacher->setX(teacherPosition.x() - m_worldShift);
    cleaner->setX(cleanerPosition.x() - m_worldShift);

    const qreal ratio = qreal(m_worldShift) / MaxWorldShift;
    applyParallax(ratio, universityBackground);
    applyParallax(ratio, universityTileImage);

}

void UniversityScene::initScene()
{
    // set scene width and height
    setSceneRect(0,0,SceneWidth, SceneHeight);

    // add background image
    universityBackground = new BackgroundItem(QPixmap(":/backgroundImage/images/universityBackground.png"));
    universityBackground->setPos(0,0);
    addItem(universityBackground);

    // add map image
    universityTileImage = new BackgroundItem(QPixmap(":/mapImage/images/universityMap.png"));
    universityTileImage->setPos(0,0);
    addItem(universityTileImage);

    // add player
    mPlayer->mCurrentMap = new UniversityMap;
    mPlayer->mCurrentPosition.setX(mPlayer->mCurrentMap->getPlayerStartPosition().x());
    mPlayer->mCurrentPosition.setY(mPlayer->mCurrentMap->getPlayerStartPosition().y());
    mPlayer->setPos(mPlayer->mCurrentPosition.x(), mPlayer->mCurrentPosition.y());

    // add NPC and talk window, quest light for NPC
    // add teacher
    teacher = new Teacher();
    teacherPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("teacher");
    teacher->setPos(teacherPosition.x(),teacherPosition.y());
    teacher->setTeacherState(Teacher::TeacherState::Stand);
    addItem(teacher);
    teacher->setVisible(true);
    // add quest light
    questClickTeacher = new QuestLight(QPixmap(":/otherImage/images/quest.png"));
    addItem(questClickTeacher);
    questClickTeacher->setParentItem(teacher);
    questClickTeacher->setPos(10,-55);
    // add talk window
    teacherWindow = this->addWidget(teacher->teacherWindow);
    teacherWindow->setParentItem(teacher);
    teacherWindow->setPos(-30, -90);
    teacherWindow->setVisible(false);

    // add cleaner
    cleaner = new Cleaner();
    cleanerPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("cleaner");
    cleaner->setPos(cleanerPosition.x(),cleanerPosition.y());
    addItem(cleaner);
    cleaner->setVisible(true);
    // add quest light
    questClickCleaner = new QuestLight(QPixmap(":/otherImage/images/quest.png"));
    addItem(questClickCleaner);
    questClickCleaner->setParentItem(cleaner);
    questClickCleaner->setPos(10,-55);
    // add talk window for airCrew
    cleanerWindow = this->addWidget(cleaner->cleanerWindow);
    cleanerWindow->setParentItem(cleaner);
    cleanerWindow->setPos(-30, -90);
    cleanerWindow->setVisible(false);


    // last add mPlayer, so that player is in front of other items
    addItem(mPlayer);
    // add bus window for taking bus
    busWindow = this->addWidget(busTalkWindow);
    busWindow->setParentItem(mPlayer);
    busWindow->setPos(-30, -150);
    busWindow->setVisible(false);
    busWindow->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    connect(busTalkWindow, &BusWindow::selectedBus,this, &UniversityScene::processBusWindow);

}

void UniversityScene::updateItemState()
{
    // set if bus window should be visible
    if(distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerStartPosition()) < TileWidth){
        busWindow->setVisible(true);
    }else if (distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getPlayerEndPosition()) > 5*TileWidth){
        busWindow->setVisible(false);
    }

    // check if NPC should be visible
    if (teacher->x() < SceneWidth && teacher->x() > 0){
        teacher->setVisible(true);
    }else{
        teacher->setVisible(false);
        teacherWindow->setVisible(false);
        teacher->teacherWindow->close();
        teacher->setTeacherState(Teacher::TeacherState::Stand);
    }

    if (cleaner->x() < SceneWidth && cleaner->x() >0){
        cleaner->setVisible(true);
    }else{
        cleaner->setVisible(false);
        cleanerWindow->setVisible(false);
        cleaner->cleanerWindow->close();
    }

    // click the the light button of teacher
    if (questClickTeacher->isQuestClicked()){
        teacher->setTeacherState(Teacher::TeacherState::Say);
        teacherWindow->setVisible(true);
        teacher->processCollideWithPlayer();
    }

    // click the light button of cleaner
    if (questClickCleaner->isQuestClicked()){
        cleanerWindow->setVisible(true);
    }
}

void UniversityScene::processBusWindow(QString busNumber)
{
    busWindow->setVisible(false);
    if (busNumber=="6B"){
        emit changeScene(SceneType::University, SceneType::Airport);
        //emit goToAirports("university");
        return;
    }
}

void UniversityScene::returnBankCardInfo()
{
   //emit ifPlayerHasBankCard(getIfGetBankCard());
   qDebug() << "If has bank card in university: " << QString::number(BasicScene::mPlayer->ifBankCard);
   emit ifPlayerHasBankCard(BasicScene::mPlayer->ifBankCard);
}

