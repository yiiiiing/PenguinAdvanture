#include "hospitalmap.hh"

HospitalMap::HospitalMap()
{
    initialMap(":/mapData/mapData/hospitalMap.csv");

}

std::string HospitalMap::getMapName()
{
    return "HospitalMap";
}

QVector2D HospitalMap::getPlayerStartPosition() const
{
    return playerStartPosition;
}

QVector2D HospitalMap::getGraphicsItemPosition(std::string itemName)
{
    if (itemName == "tutor"){
        return tutorPosition;
    }
    else if(itemName == "gate"){
        return gatePosition;
    }
    return {0,0};
}
