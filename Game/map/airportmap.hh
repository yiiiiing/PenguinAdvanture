#ifndef AIRPORTMAP_HH
#define AIRPORTMAP_HH

#include <string>
#include <QVector2D>
#include <QVector>
#include "Constants.hh"
#include "basemap.hh"

class AirportMap : public BaseMap
{
public:
    AirportMap();
    std::string getMapName() override;
    QVector2D getGraphicsItemPosition(std::string itemName) override;

    QVector2D getPlayerStartPosition() const override;
    QVector2D getPlayerEndPosition() const override ;

    QVector<QVector2D> getEnemyPosition() const override;

private:
    // player starting position and end Position
    const QVector2D playerStartPosition = {5*TileWidth, 17*TileHeight-0.5*penguinStandHeight};
    const QVector2D playerEndPosition = {76*TileWidth, 21*TileHeight-0.5*penguinStandHeight};

    // enemy position
    QVector<QVector2D> enemyPosition;

    // tutor position
    const QVector2D tutorPosition = {33*TileWidth, 21*TileHeight-tutorHeight};

    // air crew position
    const QVector2D airCrewPosition = {10*TileWidth, 17*TileHeight-airCrewHeight};

    // ERP position
    const QVector2D erpPosition = {35*TileWidth, 7*TileHeight-erpHeight};

};

#endif // AIRPORTMAP_HH
