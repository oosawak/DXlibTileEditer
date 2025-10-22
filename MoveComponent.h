//**************************************************************
// MoveComponentクラス(等加速度直線運動のジャンプ)
// 作成日：2024/01/12
// 作成者：百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Component.h"
#include "Vector2.h"

class MoveComponent :
    public Component
{
public:
    MoveComponent(class Actor* owner, int order = 10);
    ~MoveComponent();

    void ComponentUpdate(float deltaTime)override;

    Vector2 GetVelocity() { return mVelocity; }
    void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

    void SetGravity(float gravity) { mGravity = gravity; }

protected:
    Vector2 mVelocity;
    float   mGravity;
};

