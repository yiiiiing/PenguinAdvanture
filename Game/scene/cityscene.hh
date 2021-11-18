#ifndef CITYSCENE_HH
#define CITYSCENE_HH

#include <QGraphicsProxyWidget>
#include <QWidget>
#include "basicscene.hh"
#include "map/citymap.hh"
#include "graphicsItem/sceneitem.hh"
#include "graphicsItem/questlight.hh"
#include "graphicsItem/bank.hh"
#include "window/talkwindow.hh"
#include "window/buswindow.hh"
#include "Constants.hh"

class CityScene : public BasicScene
{
    Q_OBJECT

public:
    explicit CityScene(QObject *parent = 0);

    void moveScene() override;
    void initScene() override;
    void updateItemState() override;

signals:
    void hasGotBankCard();

private:
    void processBusWindow(QString busNumber);
    // define player initial position
    BackgroundItem* cityTileImage;
    BackgroundItem* cityBackground;
    QTimer mTimer;

    // define talk windows in city Scene
    Bank* bank;
    QGraphicsProxyWidget* bankWindow = NULL;
    // process response of bank window
    void processBankWindowResponse(bool answer);

    BusWindow* busTalkWindow = new BusWindow("city");
    QGraphicsProxyWidget* busWindow = NULL;

};

#endif // CITYSCENE_HH
