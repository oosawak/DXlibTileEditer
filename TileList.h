//**************************************************************
// TileListクラス(コンポーネント指向版)
// 作成日：2024/02/19
// 作成者：百春
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
