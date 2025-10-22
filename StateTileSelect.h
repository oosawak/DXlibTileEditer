//**************************************************************
// StateTileSelect�N���X(State�p�^�[��:�^�C���I����ԃN���X)
// �쐬���F2024/02/24
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "State.h"

class StateTileSelect :
    public State
{
public:
    StateTileSelect(class StateComponent* owner);
    ~StateTileSelect();

    void Update(float deltaTime) override;

    StateType GetType() override { return StateType::kTileSelect; }


};
