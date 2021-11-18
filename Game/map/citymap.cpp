#include "citymap.hh"

CityMap::CityMap()
{
    initialMap(":/mapData/mapData/cityMap.csv");
    // add enemy position
    enemyPosition.append({29*TileWidth,20*TileHeight-0.5*enemyHeight});
    enemyPosition.append({61*TileWidth, 20*TileHeight-0.5*enemyHeight});
    enemyPosition.append({68*TileWidth, 20*TileHeight-0.5*enemyHeight});
}

std::string CityMap::getMapName()
{
    return "CityMap";
}

QVector2D CityMap::getPlayerStartPosition() const
{
    return playerStartPosition;
}

QVector2D CityMap::getPlayerEndPosition() const
{
    return playerEndPosition;
}

QVector2D CityMap::getGraphicsItemPosition(std::string itemName)
{
    if (itemName == "bank"){
        return bankPosition;
    }
    return {0,0};
}

QVector<QVector2D> CityMap::getEnemyPosition() const
{
    return enemyPosition;
}
