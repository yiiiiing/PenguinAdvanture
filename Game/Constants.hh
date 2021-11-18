#ifndef CONSTANTS_HH
#define CONSTANTS_HH

// this file defines the constant used in game

// tile size
const int TileWidth = 64;
const int TileHeight = 27;

// map size
const int MapWidth = 80;
const int MapHeight = 25;

// scene size
const int SceneHeight = MapHeight * TileHeight;
const int SceneWidth = int(SceneHeight * 16 / 9);

// parameter for shifting scene
const int ShiftBorder = SceneWidth  / 3;
const int MaxWorldShift = MapWidth*TileWidth - SceneWidth;

// size of player(stand state)
const int penguinStandWidth = 107;
const int penguinStandHeight = 64;


// size of NPC
const int npcStandFrame = 3;

const int tutorWidth = 55;
const int tutorHeight = 73;


const int airCrewWidth = 54;
const int airCrewHeight = 75;

const int cleanerWidth = 58;
const int cleanerHeight = 85;


const int teacherWidth = 58;
const int teacherHeight = 71;
const int teacherSayFrame=11;


const int erpWidth = 242;
const int erpHeight = 172;
const int erpFrame = 13;

const int gateHeight = 156;
const int gateFrame = 7;

// size of enemy
const int enemyHeight = 77;

#endif // CONSTANTS_HH
