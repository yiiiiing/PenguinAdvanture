#ifndef AIRPORTSCENE_HH
#define AIRPORTSCENE_HH

#include <QGraphicsProxyWidget>
#include <QWidget>
#include <QMessageBox>
#include "basicscene.hh"
#include "map/airportmap.hh"
#include "graphicsItem/sceneitem.hh"
#include "graphicsItem/aircrew.hh"
#include "graphicsItem/tutor.hh"
#include "graphicsItem/questlight.hh"
#include "graphicsItem/train.hh"
#include "window/talkwindow.hh"
#include "window/buswindow.hh"
#include "Constants.hh"

class AirportScene : public BasicScene
{
    Q_OBJECT

public:
    AirportScene(QObject *parent = 0);
    void moveScene() override;
    void initScene() override;
    void updateItemState() override;

private:
    void trainWindowResponse(bool answer);
    void trainAnimation();
    void processBusWindow(QString busNumber);

    int trainDirection = 0;
    QVector2D trainEndPosition = {0,0};
    // define player initial position
    BackgroundItem* airportsTileImage;
    BackgroundItem* airportsBackground;

    // define NPC and npc's position
    Tutor* tutor;
    AirCrew* airCrew;
    SceneItem* erp;
    Train* train;
    QVector2D tutorPosition;
    QVector2D airCrewPosition;
    QVector2D erpPosition;
    QVector2D trainPosition;

    // define Timers for NPC, scene update and trains
    QTimer mTimer;
    QTimer trainTimer;
    QTimer animationTimer;

    // add quest light for airCrew and tutor
    QuestLight* questClickAirCrew;
    QuestLight* questClickTutor;

    // define talk windows for NPC
    QGraphicsProxyWidget* airCrewWindow = NULL;
    QGraphicsProxyWidget* tutorWindow = NULL;
    QGraphicsProxyWidget* trainWindow = NULL;

    // define bus window
    BusWindow* busTalkWindow = new BusWindow("airport");
    QGraphicsProxyWidget* busWindow = NULL;

};

#endif // AIRPORTSCENE_HH
