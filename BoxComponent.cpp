//**************************************************************
// BoxComponentクラス
// 作成日：2024/02/17
// 作成者：百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"

//==============================================================
// コンストラクタ
//==============================================================
BoxComponent::BoxComponent(class Actor* owner, BoxType type, int updateOrder)
	: Component(owner, updateOrder)
	, mType(type)
{
	mActor->GetGame()->AddBox(this);
}

//==============================================================
// デストラクタ
//==============================================================
BoxComponent::~BoxComponent()
{
	mActor->GetGame()->RemoveBox(this);
}

//==============================================================
// 矩形当たり判定
//==============================================================
bool Intersect(const BoxComponent& a, const BoxComponent& b)
{
	Vector2 posA = a.mActor->GetPosition() + a.mOffset;
	Vector2 posB = b.mActor->GetPosition() + b.mOffset;
	Vector2 diff = posA - posB;

	return (fabsf(diff.X) <= (a.mSize.X + b.mSize.X) * 0.5f &&
		fabsf(diff.Y) <= (a.mSize.Y + b.mSize.Y) * 0.5f);
}

bool Intersect(const BoxComponent& a, const Vector2& b)
{
	Vector2 posA = a.mActor->GetPosition() + a.mOffset;
	Vector2 diff = posA - b;

	return (fabsf(diff.X) <= (a.mSize.X) * 0.5f &&
		fabsf(diff.Y) <= (a.mSize.Y) * 0.5f);
}
