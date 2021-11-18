#include "airportmap.hh"

AirportMap::AirportMap()
{
    initialMap(":/mapData/mapData/airportsMap.csv");
    // add enemy position
    enemyPosition.append({45*TileWidth,21*TileHeight-0.5*enemyHeight});
    enemyPosition.append({61*TileWidth, 21*TileHeight-0.5*enemyHeight});
}

std::string AirportMap::getMapName()
{
    return "AirportMap";
}

QVector2D AirportMap::getGraphicsItemPosition(std::string itemName)
{
    if (itemName=="tutor"){
        return tutorPosition;
    }
    else if(itemName=="erp"){
        return erpPosition;
    }
    else if(itemName=="airCrew"){
        return airCrewPosition;
    }
    return QVector2D{0,0};

}

QVector2D AirportMap::getPlayerStartPosition() const
{
    return playerStartPosition;
}

QVector2D AirportMap::getPlayerEndPosition() const
{
    return playerEndPosition;
}

QVector<QVector2D> AirportMap::getEnemyPosition() const
{
    return enemyPosition;
}
