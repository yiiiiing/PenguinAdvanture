#include "hospitalscene.hh"

#include <QDebug>

HospitalScene::HospitalScene(QObject *parent) : BasicScene(parent)
{
    initScene();
    mTimer.start();
    mTimer.setInterval(50);
    connect(&mTimer, &QTimer::timeout, this, &HospitalScene::updateScene);

    // connect npc timer and npc(npc don't need to update fast as player)
    animationTimer.setInterval(500);
    animationTimer.start();
    connect(&animationTimer, &QTimer::timeout, tutor, &SceneItem::playAnimation);
    connect(&animationTimer, &QTimer::timeout, gate, &SceneItem::playAnimation);

    // add message
    messageOfEnemy.append("Hi, Little Penguin, you encountered the gangster! And I sent you to the hospital.");
    messageOfEnemy.append("If you meet these guys again, press 'A' on keyborad to use your spear to attack them.");
    messageOfEnemy.append("Your magic power is embedded into your spear, so you can attack them from a distance.");
    messageOfEnemy.append("Now, you can use that green halo to go back! And you will return to the begining of previous map.");

    messageOfTrap.append("Hi, Little Penguin, you fell into the trap! And I sent you to the hospital.");
    messageOfTrap.append("City center is under construction now, Please be careful!");
    messageOfTrap.append("Now, you can ues that green halo to go back! And you will return to the begining of previous map.");

}

void HospitalScene::moveScene()
{
    // no scene move in the hospital scene
    mPlayer->setX(mPlayer->mCurrentPosition.x());

}

void HospitalScene::initScene()
{
    setSceneRect(0,0,SceneWidth, SceneHeight);

    hospitalTileImage = new BackgroundItem(QPixmap(":/mapImage/images/hospitalMap.png"));
    hospitalTileImage->setPos(0,0);
    addItem(hospitalTileImage);

    mPlayer->mCurrentMap = new HospitalMap;
    mPlayer->mCurrentPosition.setX(mPlayer->mCurrentMap->getPlayerStartPosition().x());
    mPlayer->mCurrentPosition.setY(mPlayer->mCurrentMap->getPlayerStartPosition().y());
    mPlayer->setPos(mPlayer->mCurrentPosition.x(), mPlayer->mCurrentPosition.y());

    // add tutor
    tutor = new Tutor();
    tutorPosition = mPlayer->mCurrentMap->getGraphicsItemPosition("tutor");
    tutor->setPos(tutorPosition.x(),tutorPosition.y());

    // add quest light for tutor
    questClickTutor = new QuestLight(QPixmap(":/otherImage/images/quest.png"));
    addItem(questClickTutor);
    questClickTutor->setParentItem(tutor);
    questClickTutor->setPos(10,-55);

    // add talk window
    tutorWindow = this->addWidget(tutor->tutorWindow);
    tutorWindow->setParentItem(tutor);
    tutorWindow->setPos(-30, -90);
    tutorWindow->setVisible(false);

    // add gate
    gate = new HospitalGate();
    gatePosition = mPlayer->mCurrentMap->getGraphicsItemPosition("gate");
    gate->setPos(gatePosition.x(),gatePosition.y());
    // add talk window for gate
    gateWindow = this->addWidget(gate->gateWindow);
    gateWindow->setParentItem(gate);
    gateWindow->setPos(-30, -90);
    gateWindow->setVisible(false);

    addItem(tutor);
    addItem(gate);
    addItem(mPlayer);

    connect(gate, &HospitalGate::leaveHospital, [this](){
        emit changeScene(SceneType::Hospital, previousScene);
    });

}

void HospitalScene::updateItemState()
{
    // set visible or invisible for gate window
    if(distanceBetweenPlayerAndItem(mPlayer->mCurrentMap->getGraphicsItemPosition("gate")) < 5*TileWidth){
        gateWindow->setVisible(true);
    }else {
        gateWindow->setVisible(false);
    }

    // click the light button of the tutor
    if (questClickTutor->isQuestClicked()){
        tutorWindow->setVisible(true);
        tutor->processCollideWithPlayer();
    }

}

BasicScene::SceneType HospitalScene::getPreviousScene() const
{
    return previousScene;
}

void HospitalScene::setPreviousScene(SceneType scene)
{
    previousScene = scene;
}

void HospitalScene::processDieWithEnemy()
{
    qDebug() << "change the message";
    this->tutor->setMessage(messageOfEnemy);

}

void HospitalScene::processDieWithTrap()
{
    this->tutor->setMessage(messageOfTrap);

}
