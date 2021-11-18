#ifndef HOSPITALSCENE_HH
#define HOSPITALSCENE_HH

#include <QGraphicsProxyWidget>
#include <QWidget>
#include "basicscene.hh"
#include "map/hospitalmap.hh"
#include "graphicsItem/sceneitem.hh"
#include "graphicsItem/questlight.hh"
#include "graphicsItem/tutor.hh"
#include "graphicsItem/hospitalgate.hh"
#include "window/talkwindow.hh"
#include "Constants.hh"

class HospitalScene : public BasicScene
{
    Q_OBJECT

public:
    explicit HospitalScene(QObject *parent = 0);

    void moveScene() override;
    void initScene() override;
    void updateItemState() override;

    SceneType getPreviousScene() const;
    void setPreviousScene(SceneType scene);

    // define two functions to process the death of player
    void processDieWithEnemy();
    void processDieWithTrap();

private:
    // define which scene is previous to the hospital scene
    // (which scene player is from)
    SceneType previousScene;

    // define player initial position
    BackgroundItem* hospitalTileImage;
    QTimer mTimer;
    QTimer animationTimer;

    // add tutor in hospital scene
    Tutor* tutor;
    QuestLight* questClickTutor;
    QVector2D tutorPosition;
    QGraphicsProxyWidget* tutorWindow = NULL;

    // define different message for tutor
    QVector<QString> messageOfEnemy;
    QVector<QString> messageOfTrap;

    // add gate in hospital scene
    HospitalGate* gate;
    QVector2D gatePosition;
    QGraphicsProxyWidget* gateWindow = NULL;

};
#endif // HOSPITALSCENE_HH
