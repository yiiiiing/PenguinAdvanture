#ifndef UNIVERSITYSCENE_HH
#define UNIVERSITYSCENE_HH

#include "basicscene.hh"
#include <QGraphicsProxyWidget>
#include <QWidget>
#include "map/universitymap.hh"
#include "graphicsItem/sceneitem.hh"
#include "graphicsItem/questlight.hh"
#include "graphicsItem/cleaner.hh"
#include "graphicsItem/teacher.hh"
#include "window/talkwindow.hh"
#include "window/buswindow.hh"
#include "Constants.hh"

class UniversityScene : public BasicScene
{
    Q_OBJECT

public:
    explicit UniversityScene(QObject *parent = 0);

    void moveScene() override;
    void initScene() override;
    void updateItemState() override;

signals:
    void endView();
    bool ifPlayerHasBankCard(bool answer);
private:
    void processBusWindow(QString busNumber);
    //
    void returnBankCardInfo();
    // define player initial position
    BackgroundItem* universityTileImage;
    BackgroundItem* universityBackground;

    // define timer for update scene and NPC
    QTimer mTimer;
    QTimer animationTimer;

    // define cleaner and teacher
    Teacher* teacher;
    Cleaner* cleaner;

    // define position for NPC
    QVector2D teacherPosition;
    QVector2D cleanerPosition;

    // define quest light for teacher and cleaner
    QuestLight* questClickTeacher;
    QuestLight* questClickCleaner;

    // define talk windows in university scene
    QGraphicsProxyWidget* cleanerWindow = NULL;
    QGraphicsProxyWidget* teacherWindow = NULL;

    BusWindow* busTalkWindow = new BusWindow("university");
    QGraphicsProxyWidget* busWindow = NULL;
};



#endif // UNIVERSITYSCENE_HH
