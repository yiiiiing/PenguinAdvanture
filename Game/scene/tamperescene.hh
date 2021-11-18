#ifndef TAMPERESCENE_HH
#define TAMPERESCENE_HH

#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QVector2D>
#include <QTimeLine>
#include <QVector>
#include <QMultiMap>
#include <QString>
#include <QPointF>
#include <QGraphicsItemAnimation>
#include "graphicsItem/backgrounditem.hh"
#include "basicscene.hh"
#include "Constants.hh"

using RouteType = QMultiMap<BasicScene::SceneType, QMap<BasicScene::SceneType, QVector<QPointF>>>;


class TampereScene : public BasicScene
{
    Q_OBJECT
public:
    explicit TampereScene(QObject *parent = 0);
    void setStartAndEnd(SceneType startName, SceneType endName);
    void playAnimation();

    RouteType Routes;

signals:
    BasicScene::SceneType arriveAt(SceneType arriveScene);

private:
    void initialScene();
    void addAllRoute();
    void changeAngle();
    void processArriveAtScene();
    qreal angleBetween2Line(QPointF point0, QPointF point1);
    qreal distance(QPointF point1, QPointF point2);

    QTimeLine* busTimeLine;
    QGraphicsItemAnimation* busAnimation;
    qreal angle;

    // add Tampere map
    BackgroundItem* TampereMap;

    // add bus
    BackgroundItem* bus;

    // define start point and end point
    SceneType startName_;
    SceneType endName_;
    QVector<QPointF> allPoints;

    // record points of area in Tampere Map and turning point
    const QPointF verticalPoint = {0,100};
    const QPointF airPortsPosition = {181, 714};
    const QPointF airportsToUniversityTurning1 = {288, 476};
    const QPointF airportsToUniversityTurning2 = {930, 350};

    const QPointF airportsToCityTurning1 = airportsToUniversityTurning1;
    const QPointF airportsToCityTurning2 = {700, 394};

    const QPointF cityToUniversityTurning = {870,205};

    const QPointF cityPosition = {718, 170};
    const QPointF universityPosition = {990,488};

};

#endif // TAMPERESCENE_HH
