//**************************************************************
// TileSpriteComponent�N���X
// �쐬���F2024/02/29
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "SpriteComponent.h"

class TileSpriteComponent :
    public SpriteComponent
{
public:
    TileSpriteComponent(class Actor* owner, int order = 10);
    ~TileSpriteComponent();

    void Draw()override;

    void SetColor(unsigned int color) { mColor = color; }

private:
    unsigned int mColor;
};

