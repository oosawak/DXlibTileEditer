//**************************************************************
// Componentクラス
// 作成日：2023/10/30
// 作成者：百春
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Component.h"
#include "Actor.h"

//==============================================================
// コンストラクタ
//==============================================================
Component::Component(Actor* owner, int order)
	: mActor(owner)
	, mUpdateOrder(order)
	, mOffset(Vector2(0,0))
	, mSize(Vector2(0, 0))
{
	mActor->AddComponent(this);
}

//==============================================================
// デストラクタ
//==============================================================
Component::~Component()
{
	mActor->RemoveComponent(this);
}
