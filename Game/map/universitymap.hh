#ifndef UNIVERSITYMAP_HH
#define UNIVERSITYMAP_HH
#include <string>
#include <QVector2D>
#include "Constants.hh"
#include "basemap.hh"

class UniversityMap : public BaseMap
{
public:
    UniversityMap();
    std::string getMapName() override;
    QVector2D getGraphicsItemPosition(std::string itemName) override;

    QVector2D getPlayerStartPosition() const override;
    QVector2D getPlayerEndPosition() const override ;

private:
    // player starting position and end Position
    const QVector2D playerStartPosition = {2*TileWidth, 20*TileHeight-0.5*penguinStandHeight};
    const QVector2D playerEndPosition = {76*TileWidth, 20*TileHeight-0.5*penguinStandHeight};

    // enemy position
    QVector2D enemyPosition;

    // cleaner position
    const QVector2D cleanerPosition = {53*TileWidth, 10*TileHeight-cleanerHeight};

    // teacher position
    const QVector2D teacherPosition = {72*TileWidth, 20*TileHeight-teacherHeight};
};

#endif // UNIVERSITYMAP_HH
