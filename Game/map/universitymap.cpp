#include "universitymap.hh"

UniversityMap::UniversityMap()
{
    initialMap(":/mapData/mapData/universityMap.csv");

}

std::string UniversityMap::getMapName()
{
    return "UniversityMap";

}

QVector2D UniversityMap::getGraphicsItemPosition(std::string itemName)
{
    if(itemName == "cleaner"){
        return cleanerPosition;
    }
    if(itemName == "teacher"){
        return teacherPosition;
    }
    return {0,0};
}

QVector2D UniversityMap::getPlayerStartPosition() const
{
    return playerStartPosition;
}

QVector2D UniversityMap::getPlayerEndPosition() const
{
    return playerEndPosition;
}
