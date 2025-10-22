//**************************************************************
// StateNoneクラス(Stateパターン:無選択状態クラス)
// 作成日：2024/02/24
// 作成者：百春
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

