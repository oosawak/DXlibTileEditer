//**************************************************************
// TileList�N���X(�R���|�[�l���g�w����)
// �쐬���F2024/02/19
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Actor.h"

class TileList :
    public Actor
{
public:
    TileList(class Game* game);
    ~TileList();

    void ActorInput(const char keyStatus[])override;
    void ActorUpdate(float deltaTime)override;
};
