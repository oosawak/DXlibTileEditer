//**************************************************************
// GameOver�N���X(�R���|�[�l���g�w����)
// �쐬���F 2024/01/19
// �쐬�ҁF �S�t
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

