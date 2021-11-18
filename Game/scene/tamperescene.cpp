#include "tamperescene.hh"

#include <cmath>
#include <iostream>
#include <QDebug>
#define _USE_MATH_DEFINES

TampereScene::TampereScene(QObject *parent):
    BasicScene(parent)
{

    initialScene();
    mPlayer->setVisible(false);
    connect(busTimeLine, &QTimeLine::frameChanged, this, &TampereScene::changeAngle);
    connect(busTimeLine, &QTimeLine::finished, this, &TampereScene::processArriveAtScene);
}


void TampereScene::setStartAndEnd(SceneType startName, SceneType endName)
{
    startName_ = startName;
    endName_ = endName;
}

void TampereScene::initialScene()
{
    // set fixed scene size
    setSceneRect(0,0,1200, 788);
    TampereMap = new BackgroundItem(QPixmap(":/mapImage/images/tampereMap.png"));
    TampereMap->setPos(0,0);
    addItem(TampereMap);

    // initial routes
    addAllRoute();

    // add bus
    QPixmap busPixel(":/otherImage/images/bus.png");
    bus = new BackgroundItem(busPixel);
    bus->setTransformOriginPoint(verticalPoint);
    bus->setOffset(-busPixel.width() / 2, -busPixel.height() / 2);
    addItem(bus);

    busTimeLine = new QTimeLine(15 * 1000);
    busTimeLine->setFrameRange(0,100);
    busAnimation = new QGraphicsItemAnimation;
}

void TampereScene::addAllRoute()
{
    QVector<QPointF> airportsToCity = {airPortsPosition, airportsToCityTurning1, airportsToCityTurning2, cityPosition};
    QVector<QPointF> airportsToUniversity = {airPortsPosition, airportsToUniversityTurning1, airportsToUniversityTurning2, universityPosition};
    QVector<QPointF> cityToUniversity = {cityPosition, cityToUniversityTurning, universityPosition};
    QVector<QPointF> universityToAirports = {universityPosition, airportsToUniversityTurning2, airportsToUniversityTurning1, airPortsPosition};
    Routes.insert(SceneType::Airport, {{SceneType::City, airportsToCity}});
    Routes.insert(SceneType::Airport, {{SceneType::University, airportsToUniversity}});
    Routes.insert(SceneType::City, {{SceneType::University, cityToUniversity}});
    Routes.insert(SceneType::University, {{SceneType::Airport, universityToAirports}});
}

void TampereScene::changeAngle()
{
    qreal interval = 1.0f / qreal((allPoints.size() - 1));
    for (int i = 1; i < allPoints.size()-1; ++i){
        if (distance(bus->pos(), allPoints.at(i)) < 5){
            angle = angleBetween2Line(allPoints.at(i), allPoints.at(i+1));
            busAnimation->setRotationAt(0,angle);
            busAnimation->setPosAt((i+1)*interval, allPoints.at(i+1));
            return;
        }
    }
}

void TampereScene::processArriveAtScene()
{
    busTimeLine->stop();
    busAnimation->clear();
    emit arriveAt(endName_);
}

void TampereScene::playAnimation()
{
    busTimeLine->start();
    for(auto endPoint : Routes.values(startName_)){
        if (endPoint.find(endName_) != endPoint.end()){
            allPoints = endPoint.value(endName_);
        }
    }
    bus->setPos(allPoints.at(0).x(), allPoints.at(0).y());

    // add animation (notice: set bus position first and then add bus into busAnimation)
    busAnimation->setItem(bus);
    busAnimation->setTimeLine(busTimeLine);
    //qDebug() << allPoints.size();
    angle = angleBetween2Line(allPoints.at(0), allPoints.at(1));
    busAnimation->setRotationAt(0,angle);
    qreal interval = 1.0f / qreal((allPoints.size() - 1));
    busAnimation->setPosAt(interval, allPoints.at(1));
}

qreal TampereScene::angleBetween2Line(QPointF point0, QPointF point1)
{
    qreal angle = 0.0f; // define angle between two lines

    // vector of point1 & point0
    QPointF vector1 = verticalPoint;

    // vector of point2 & point0
    QPointF vector2 = point1 - point0;

    // product of 2 vector
    double productValue = (vector1.x() * vector2.x()) + (vector1.y() * vector2.y());
    double vector1Len = std::sqrt(vector1.x() * vector1.x() + vector1.y() * vector1.y());
    double vector2Len = std::sqrt(vector2.x() * vector2.x() + vector2.y() * vector2.y());
    // cosine rule
    double cosValue = productValue / (vector1Len * vector2Len);

    // cosine value must be in [-1,1]
    if(cosValue < -1){
        cosValue = -1;
    }else if(cosValue > 1){
        cosValue = 1;
    }


    // convert to angle
    angle = 180 - std::acos(cosValue) * 180 / 3.14;

    if (point1.x() < point0.x()){
        angle = - angle;
    }
    //qDebug() << angle;

    return angle;

}

qreal TampereScene::distance(QPointF point1, QPointF point2)
{
    qreal dx = point1.x() - point2.x();
    qreal dy = point1.y() - point2.y();
    qreal distance = std::sqrt(dx*dx + dy*dy);
    return distance;

}

