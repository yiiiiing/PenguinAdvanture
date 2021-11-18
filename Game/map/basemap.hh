#ifndef BASEMAP_HH
#define BASEMAP_HH
#include <vector>
#include <iostream>
#include <string>
#include <QString>
#include <QFile>
#include <QVector2D>
#include <QVector>
#include "Constants.hh"

class BaseMap
{
public:
    BaseMap();

    // initialize map (store tile data from csv file to the variable "map")
    void initialMap(QString mapName);
    // get the map name
    virtual std::string getMapName();
    virtual QVector2D getGraphicsItemPosition(std::string itemName);

    virtual QVector2D getPlayerStartPosition() const;
    virtual QVector2D getPlayerEndPosition() const;

    // get enemyposition
    virtual QVector<QVector2D> getEnemyPosition() const;

    enum TileType{Empty=0, Block, OneWayPlatform};

    // convert coordinator from scence x, y to map's tile index
    std::vector<int> ScenePointToTileIndex(float scenePointX, float scenePointY);
    // convert cooridinator from map's tile index to scene point
    std::vector<float> tileIndexToScenePoint(const std::vector<int>& tileIndex);

    // get tile type, given the tile index
    TileType getTileType(int x, int y);

    // check if the tile is an obstacle
    bool isObstacle(int x, int y);
    // check if the tile is ground
    bool isGround(int x, int y);
    // check if the tile is one-way platform
    bool isOneWayPlatform(int x, int y);
    // check if the tile is ceiling
    bool isCeiling(int x, int y);

private:
    // array[rowNum][colNum]
    TileType map[MapHeight][MapWidth];

    TileType intToTileType(int tileIndex);

    void readCSV(QString mapName);
};

#endif // BASEMAP_HH
