//**************************************************************
// GameOverクラス(コンポーネント指向版)
// 作成日： 2024/01/19
// 作成者： 百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Actor.h"

class GameOver :
    public Actor
{
public:
    GameOver(class Game* game, ActorType type);
    ~GameOver();
};

