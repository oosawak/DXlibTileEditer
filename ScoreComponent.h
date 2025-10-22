//**************************************************************
// ScoreComponent�N���X
// �쐬���F2023/12/06
// �쐬�ҁF�S�t
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "SpriteComponent.h"

class ScoreComponent :
    public SpriteComponent
{
public:
    ScoreComponent(class Actor* owner, unsigned int color, int fontHandle, int order = 50);
    ~ScoreComponent();

    void Draw()override;

private:
    int         mColor;
    int         mFontHandle;
};
