//**************************************************************
// ScoreComponentƒNƒ‰ƒX
// ì¬“úF2023/12/06
// ì¬ŽÒF•St
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "ScoreComponent.h"
#include "Actor.h"
#include "Game.h"

ScoreComponent::ScoreComponent(Actor* owner, unsigned int color, int fontHandle, int order)
	: SpriteComponent(owner, order)
	, mColor(color)
	, mFontHandle(fontHandle)
{
}

ScoreComponent::~ScoreComponent()
{
}

void ScoreComponent::Draw()
{
	int		score = mActor->GetGame()->GetScore();
	Vector2 pos = mActor->GetPosition() + mOffset;
	int		w = GetDrawFormatStringWidthToHandle(mFontHandle, "%d", score);

	DrawFormatStringToHandle(
		(int)(pos.X - w / 2.0f), (int)pos.Y, mColor, mFontHandle, "%d", score
	);
}
