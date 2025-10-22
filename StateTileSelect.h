//**************************************************************
// StateTileSelectクラス(Stateパターン:タイル選択状態クラス)
// 作成日：2024/02/24
// 作成者：百春
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
