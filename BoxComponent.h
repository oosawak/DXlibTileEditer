//**************************************************************
// BoxComponent�N���X
// �쐬���F2024/02/17
// �쐬�ҁF�S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once

#include "Component.h"
#include "Vector2.h"

enum class BoxType { kElse, kTileList, kTileMap };

class BoxComponent : public Component
{
public:
    BoxComponent(class Actor* owner, BoxType type, int updateOrder = 100);
    ~BoxComponent();

    BoxType GetType() { return mType; }

    int  GetIndex() { return mIndex; }
    void SetIndex(int index) { mIndex = index; }

protected:
    friend bool Intersect(const BoxComponent& a, const BoxComponent& b);
    friend bool Intersect(const BoxComponent& a, const Vector2& b);

private:
    BoxType     mType;
    int         mIndex;
};

