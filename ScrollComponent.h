//**************************************************************
// ScrollComponentクラス(コンポーネント指向版)
// 作成日： 2024/01/12
// 作成者： 百春
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

