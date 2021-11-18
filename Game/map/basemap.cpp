#include "basemap.hh"

BaseMap::BaseMap()
{

}

void BaseMap::initialMap(QString mapName)
{
    readCSV(mapName);

}

std::string BaseMap::getMapName()
{
    return "BaseMap";

}

QVector2D BaseMap::getGraphicsItemPosition(std::string itemName)
{
    if (itemName != ""){
        return QVector2D{0,0};
    }
    return QVector2D{0,0};
}

QVector2D BaseMap::getPlayerStartPosition() const
{
    return QVector2D{0.5*penguinStandWidth,0};
}

QVector2D BaseMap::getPlayerEndPosition() const
{
    return QVector2D{MapWidth*TileWidth-0.5*penguinStandWidth,0};
}

QVector<QVector2D> BaseMap::getEnemyPosition() const
{
    QVector<QVector2D> vec;
    return vec;
}

std::vector<int> BaseMap::ScenePointToTileIndex(float scenePointX, float scenePointY)
{
    std::vector<int> tileIndex = {0,0};
    tileIndex[0] = int(scenePointX / TileWidth);
    tileIndex[1] = int(scenePointY / TileHeight);

    return tileIndex;
}

BaseMap::TileType BaseMap::getTileType(int x, int y)
{
    // if index is out of bound, then return block
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight){
        return TileType::Block;
    }
    return map[y][x];

}

bool BaseMap::isObstacle(int x, int y)
{
    // if index is out of bound, then return true
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight){
        return true;
    }

    return (map[y][x] == TileType::Block);
}

bool BaseMap::isGround(int x, int y)
{
    // if index is out of bound, then return false
    if (x < 0 || x >= MapWidth || y < 0 || y >= MapHeight){
        return false;
    }

    return (map[y][x] == TileType::Block || map[y][x] == TileType::OneWayPlatform);

}

bool BaseMap::isCeiling(int x, int y)
{
    // if index is out of bound, then return false
    if (x < 0 || x >= MapWidth || y >= MapHeight){
        return false;
    }
    if (y < 0){
        return true;
    }

    return (map[y][x] == TileType::Block || map[y][x] == TileType::OneWayPlatform);

}

BaseMap::TileType BaseMap::intToTileType(int tileIndex)
{
    switch(tileIndex){
    case 0:
        return TileType::Empty;
    case 1:
        return TileType::Block;
    case 2:
        return TileType::OneWayPlatform;
    }
    return TileType::Empty;
}

void BaseMap::readCSV(QString mapName)
{
    // using qt to read file instead of sstream
    //std::ifstream input(mapFileName);
    QFile file(mapName);
    //if (!input.is_open())
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        std::cout << "cannot open file" << std::endl;
        return;
    }
    QByteArray line;
    std::string lineList;

    for (int row = 0; row < MapHeight; ++row){
        //std::getline(input, line);
        line = file.readLine();
        QString lineList = QString::fromStdString(line.toStdString());
        QStringList stringList = lineList.split(QLatin1Char(','));
        //std::istringstream iss(line);
        //std::string num;
        for (int col = 0; col < MapWidth; ++col){
            //std::getline(iss, num, ',');
            //std::cout << num << std::endl;
            //map[row][col] = intToTileType(std::stoi(num));
            map[row][col] = intToTileType(stringList.at(col).toInt());
        }
    }

}
