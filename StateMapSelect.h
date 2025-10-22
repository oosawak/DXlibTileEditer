//**************************************************************
// StateMapSelectクラス(Stateパターン:無マップ選択状態クラス)
// 作成日：2024/02/29
// 作成者：百春
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
