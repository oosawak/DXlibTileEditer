//**************************************************************
// InputComponent�N���X
// �쐬���F2023/12/17
// �쐬�ҁF�S�t
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

