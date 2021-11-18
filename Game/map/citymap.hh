#ifndef CITYMAP_HH
#define CITYMAP_HH
#include <string>
#include <QString>
#include <QVector>
#include "basemap.hh"


class CityMap : public BaseMap
{
public:
    CityMap();
    std::string getMapName() override;

    QVector2D getPlayerStartPosition() const override;
    QVector2D getPlayerEndPosition() const override ;

    QVector2D getGraphicsItemPosition(std::string itemName) override;

    QVector<QVector2D> getEnemyPosition() const override;

private:
    // player starting position and end Position
    const QVector2D playerStartPosition = {2*TileWidth, 20*TileHeight-0.5*penguinStandHeight};
    const QVector2D playerEndPosition = {76*TileWidth, 20*TileHeight-0.5*penguinStandHeight};

    // enemy position
    QVector<QVector2D> enemyPosition;

    // bank position
    QVector2D bankPosition = {29*TileWidth, 12*TileHeight};
};

#endif // CITYMAP_HH
