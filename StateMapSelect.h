//**************************************************************
// StateMapSelect�N���X(State�p�^�[��:���}�b�v�I����ԃN���X)
// �쐬���F2024/02/29
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "State.h"

class StateMapSelect :
    public State
{
public:
    StateMapSelect(class StateComponent* owner);
    ~StateMapSelect();

    void Update(float deltaTime) override;

    StateType GetType() override { return StateType::kMapSelect; }
};
