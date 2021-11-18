#ifndef HOSPITALMAP_HH
#define HOSPITALMAP_HH
#include <string>
#include <QString>
#include <QVector>
#include "basemap.hh"

class HospitalMap : public BaseMap
{
public:
    HospitalMap();
    std::string getMapName() override;

    QVector2D getPlayerStartPosition() const override;

    QVector2D getGraphicsItemPosition(std::string itemName) override;

private:
    // player starting position and end Position
    const QVector2D playerStartPosition = {11*TileWidth, 22*TileHeight-0.5*penguinStandHeight};

    // tutor position
    const QVector2D tutorPosition = {14*TileWidth, 22*TileHeight-tutorHeight};

    // gate position
    const QVector2D gatePosition = {1*TileWidth, 22*TileHeight-gateHeight};
};

#endif // HOSPITALMAP_HH
