//**************************************************************
// ScrollComponent�N���X(�R���|�[�l���g�w����)
// �쐬���F 2024/01/12
// �쐬�ҁF �S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Component.h"

class ScrollComponent :
    public Component
{
public:
    ScrollComponent(class Actor* owner, int order = 10);
    ~ScrollComponent();

    void ComponentUpdate(float deltaTime)override;
};

