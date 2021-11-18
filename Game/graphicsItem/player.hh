#ifndef PLAYER_HH
#define PLAYER_HH

#include <algorithm>
#include <QVector2D>
#include <iostream>
#include "penguin.hh"
#include "map/basemap.hh"


class Player: public Penguin
{
public:
    // constructor
    Player();

    // keyInput
    enum KeyInput {GoLeft=0, GoRight, Jump, Attack, End};
    bool mInputs[KeyInput::End] = {false, false, false, false};
    bool mPreviousInputs[KeyInput::End] ={false, false, false, false};

    // define player's position
    QVector2D mCurrentPosition = QVector2D(0,0);

    // update the player according to player's current state
    void updatePlayer();

    // define player's direction
    enum PlayerDirection {Left, Right};
    void changeDirection(PlayerDirection direction);


    // define player's state
    enum class PlayerState {Stand, Walk, Jump, Attack, Die};
    void changeState(PlayerState state);

    // player's currentMap
    BaseMap* mCurrentMap;

    // if player is alive
    //bool mAlive = true;
    // if player has bank card
    bool ifBankCard = false;

    PlayerDirection currentDirection() const;

private:
    // player's size
    float playerWidth = 80;
    float playerHeight = 64;

    // check if the key is current pressed
    bool keyState(KeyInput input);
    // check if the key is first pressed
    bool keyFirstState(KeyInput input);

    PlayerState mCurrentState = PlayerState::Stand;

    PlayerDirection mCurrentDirection = PlayerDirection::Right;

    // define the transform
    QTransform mTransform;

    // update previous input
    void updatePreviousInput();
    // check physics collision
    void updatePhysics();
    // process collision
    void collisionDectect();
    // check if character collides with a ground tile
    bool hasGround(float bottomY, float leftX, float rightX);
    bool hasRightObtacle(float bottomY, float headY, float rightX);
    bool hasLeftObtacle(float bottomY, float headY, float leftX);
    bool hasCeiling(float headY, float leftX, float rightX);

    // define player's speed
    float const mJumpSpeed = -300;
    float const mWalkSpeed = 60;
    float const cGravity = 20;
    float const cMaxFallingSpeed = 150;
    float const cMinJumpSpeed = -100;
    QVector2D mCurrentSpeed = QVector2D(0,0);

    // if player will get stuck (whether next to the right wall, left wall, on the ground, at the ceiling)
    bool mPushesRightWall = false;
    bool mPushesLeftWall = false;
    bool mOnGround = true;
    bool mAtCeiling = false;
};

#endif // PLAYER_HH
