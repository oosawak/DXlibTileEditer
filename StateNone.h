//**************************************************************
// StateNone�N���X(State�p�^�[��:���I����ԃN���X)
// �쐬���F2024/02/24
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "State.h"

class StateNone :
    public State
{
public:
    StateNone(class StateComponent* owner);
    ~StateNone();

    void Update(float deltaTime) override;
    
    StateType GetType() override { return StateType::kNone; }

};

