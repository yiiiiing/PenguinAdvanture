#include "player.hh"

#include <vector>
#include <iostream>

Player::Player(){
    mTransform.scale(-1,1);

}
void Player::updatePlayer()
{
    switch (mCurrentState) {
    case PlayerState::Stand:
        // set current speed to zeros
        mCurrentSpeed = {0,0};
        Penguin::standAnimation(mTransform);
        // process stand
        // if player is not on the ground, then change current state to Jump
        if (! mOnGround){
            mCurrentState = PlayerState::Jump;
            break;
        }
        if (keyState(KeyInput::GoLeft) != keyState(KeyInput::GoRight)){
            mCurrentState = PlayerState::Walk;
            break;
        } else if (keyState(KeyInput::Jump)){
            mCurrentState = PlayerState::Jump;
            mCurrentSpeed.setY(mJumpSpeed);
            break;
        }
        break;
    case PlayerState::Walk:
        // player walk animation...
        Penguin::walkAnimation(mTransform);
        // press or not press go left or go right at the same time
        if (keyState(KeyInput::GoLeft) == keyState(KeyInput::GoRight)){
            mCurrentState = PlayerState::Stand;
            mCurrentSpeed = {0,0};
            break;
        }
        else if(keyState(KeyInput::GoRight)){
            if (mPushesRightWall){
                mCurrentSpeed.setX(0);
            }else{
                mCurrentSpeed.setX(mWalkSpeed);

            }
        }
        else if(keyState(KeyInput::GoLeft)){
            if (mPushesLeftWall){
                mCurrentSpeed.setX(0);
            }else{
                mCurrentSpeed.setX(-mWalkSpeed);

            }
        }
        if (keyState(KeyInput::Jump)){
            mCurrentSpeed.setY(mJumpSpeed);
            mCurrentState = PlayerState::Jump;
            break;
        }
        else if(!mOnGround){
            mCurrentState = PlayerState::Jump;
            break;
        }
        break;

    case PlayerState::Jump:
        // play jump animation
        Penguin::jumpAnimation(mTransform);
        mCurrentSpeed.setY(mCurrentSpeed.y() + cGravity);
        // limit the falling speed
        mCurrentSpeed.setY(std::min(mCurrentSpeed.y(), cMaxFallingSpeed));
        // if short press the jump key
        if(!keyState(KeyInput::Jump) && mCurrentSpeed.y() < 0){
            mCurrentSpeed.setY(std::max(mCurrentSpeed.y(), cMinJumpSpeed));

        }
        if (keyState(KeyInput::GoLeft) == keyState(KeyInput::GoRight)){
            mCurrentSpeed.setX(0);
        }
        else if(keyState(KeyInput::GoRight)){
            if (mPushesRightWall){
                mCurrentSpeed.setX(0);
            }else{
                mCurrentSpeed.setX(mWalkSpeed);

            }
        }
        else if(keyState(KeyInput::GoLeft)){
            if (mPushesLeftWall){
                mCurrentSpeed.setX(0);
            }else{
                mCurrentSpeed.setX(-mWalkSpeed);

            }
        }
        // if hit the ground
        if (mOnGround){
            // if no movement, then state equals to stand
            if (keyState(KeyInput::GoLeft) == keyState(KeyInput::GoRight)){
                mCurrentState = PlayerState::Stand;
                mCurrentSpeed = {0,0};
                // play the music of hitting the ground...

            }else{
                mCurrentState = PlayerState::Walk;
                mCurrentSpeed.setY(0);
            }
        }
        // if hit the ceiling, immediately change vertical speed to zero and fall
        if (mAtCeiling){
            mCurrentSpeed.setY(cGravity);
        }
        break;
    case PlayerState::Attack:
        if (Penguin::mFrameIndex > Penguin::ATTACK_FRAME -1){
            changeState(PlayerState::Jump);
        }
        Penguin::attackAnimation(mTransform);
        break;
    case PlayerState::Die:
        Penguin::dieAnimation(mTransform);
        if (Penguin::mFrameIndex > Penguin::DIE_FRAME -1){
            changeState(PlayerState::Jump);
        }
        break;
    }

    // check collision and update physics info ...
    updatePhysics();

    updatePreviousInput();

}

void Player::changeDirection(Player::PlayerDirection direction)
{
    if (direction != mCurrentDirection){
        mCurrentDirection = direction;
        mTransform.scale(-1,1);
    }

}

void Player::changeState(Player::PlayerState state)
{
    if(state != mCurrentState){
        mCurrentState = state;
        Penguin::mFrameIndex = 0;
    }

}

bool Player::keyState(Player::KeyInput input)
{
    // current frame has the input
    return mInputs[input];
}

bool Player::keyFirstState(Player::KeyInput input)
{
    return mInputs[input] && !mPreviousInputs[input];
}

Player::PlayerDirection Player::currentDirection() const
{
    return mCurrentDirection;
}

void Player::updatePreviousInput()
{
    int count = KeyInput::End;
    for (int i=0; i<count; ++i){
        mPreviousInputs[i] = mInputs[i];
    }
}

void Player::updatePhysics()
{
    mCurrentPosition += mCurrentSpeed * 0.1;
    collisionDectect();
}

void Player::collisionDectect()
{
    // the bottom of player bounding box is player.y + 1/2 player.size
    float bottomY = mCurrentPosition.y() + 0.5 * playerHeight;
    // the head of player bounding  box
    float headY = mCurrentPosition.y() - 0.5 * playerHeight;
    // the left of player bounding box
    float leftX = mCurrentPosition.x() - 0.5 * playerWidth;
    // the right of player bounding box
    float rightX = mCurrentPosition.x() + 0.5 * playerWidth;

    mOnGround = hasGround(bottomY, leftX, rightX);
    mPushesRightWall = hasRightObtacle(bottomY, headY, rightX);
    mPushesLeftWall = hasLeftObtacle(bottomY, headY, leftX);
    mAtCeiling = hasCeiling(headY, leftX, rightX);
}

bool Player::hasGround(float bottomY, float leftX, float rightX)
{
    float checkedTileX = leftX;
    std::vector<int> tileIndex;
    while(checkedTileX <= rightX){
        tileIndex = mCurrentMap->ScenePointToTileIndex(checkedTileX, bottomY);
        if (mCurrentMap->isGround(tileIndex[0], tileIndex[1])){
            // here, set the y position, so there character can stand on tiles accurately
            mCurrentPosition.setY(int(bottomY / TileHeight) * TileHeight - 0.5 * playerHeight);
            return true;
        }
        checkedTileX += TileWidth;
    }
    return false;
}

bool Player::hasRightObtacle(float bottomY, float headY, float rightX)
{
    float checkedTileY = headY;
    std::vector<int> tileIndex;
    while(checkedTileY <= bottomY){
        tileIndex = mCurrentMap->ScenePointToTileIndex(rightX, checkedTileY);
        if (mCurrentMap->isObstacle(tileIndex[0], tileIndex[1])){
            return true;
        }
        checkedTileY += TileHeight;
    }
    return false;

}

bool Player::hasLeftObtacle(float bottomY, float headY, float leftX)
{
    float checkedTileY = headY;
    std::vector<int> tileIndex;
    while(checkedTileY <= bottomY){
        tileIndex = mCurrentMap->ScenePointToTileIndex(leftX, checkedTileY);
        if (mCurrentMap->isObstacle(tileIndex[0], tileIndex[1])){
            return true;
        }
        checkedTileY += TileHeight;
    }
    return false;

}

bool Player::hasCeiling(float headY, float leftX, float rightX)
{
    float checkedTileX = leftX;
    std::vector<int> tileIndex;
    while(checkedTileX <= rightX){
        tileIndex = mCurrentMap->ScenePointToTileIndex(checkedTileX, headY);
        if (mCurrentMap->isCeiling(tileIndex[0], tileIndex[1])){
            return true;
        }
        checkedTileX += TileWidth;
    }
    return false;

}

