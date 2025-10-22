//**************************************************************
// TileSpriteComponentƒNƒ‰ƒX
// ì¬“úF2024/02/29
// ì¬ŽÒF•St
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "TileSpriteComponent.h"
#include "Actor.h"
#include "Game.h"

TileSpriteComponent::TileSpriteComponent(Actor* owner, int order)
	: SpriteComponent(owner, order)
{
	mColor = GetColor(255, 255, 255);
}

TileSpriteComponent::~TileSpriteComponent()
{
}

void TileSpriteComponent::Draw()
{
	Vector2 pos = mActor->GetPosition() + mOffset;
	if (mGhandle != -1) {
		DrawRotaGraph((int)pos.X, (int)pos.Y, 1, mAngle, mGhandle, TRUE);
	}
	else {
		Vector2 pos1 = pos - mSize * 0.5f;
		Vector2 pos2 = pos + mSize * 0.5f;

		DrawBoxAA(pos1.X, pos1.Y, pos2.X, pos2.Y, mColor, FALSE);
	}
}
