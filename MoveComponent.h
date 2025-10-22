//**************************************************************
// MoveComponent�N���X(�������x�����^���̃W�����v)
// �쐬���F2024/01/12
// �쐬�ҁF�S�t
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

