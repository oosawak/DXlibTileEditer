//**************************************************************
// MapMaker�N���X(State�p�^�[�����g��)
// �쐬���F2024/03/02
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Actor.h"

class MapMaker :
    public Actor
{
public:
    MapMaker(class Game* game);
    ~MapMaker();

    void ActorInput(const char keyStatus[])override;
    void ActorUpdate(float deltaTime)override;
    void Draw();

private:
    class TileSet* mTileSet;
    class TileMap* mTileMap;
    class StateComponent* mState;

    class SpriteComponent* mCursorSprite;
    class TileSpriteComponent* mMapRangeSprite;
};
