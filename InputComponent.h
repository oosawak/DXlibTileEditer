//**************************************************************
// InputComponentクラス
// 作成日：2023/12/17
// 作成者：百春
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "MoveComponent.h"

class InputComponent :
    public MoveComponent
{
public:
    InputComponent(class Actor* owner, float speed);
    ~InputComponent();

    void ComponentInput(const char keyStatus[])override;

private:
    float   mSpeed;
};

