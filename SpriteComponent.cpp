//**************************************************************
// SpriteComponentクラス(画像ファイルを扱う用)
// 作成日：2024/02/15
// 作成者：百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

//==============================================================
// コンストラクタ
//==============================================================
SpriteComponent::SpriteComponent(Actor* owner, int order)
	: Component(owner)
	, mSpriteOrder(order)
	, mGhandle(-1)
	, mAngle(0)
{
	mActor->GetGame()->AddSprite(this);
}

//==============================================================
// デストラクタ
//==============================================================
SpriteComponent::~SpriteComponent()
{
	mActor->GetGame()->RemoveSprite(this);
}

//==============================================================
// グラフィックハンドルのセット
//==============================================================
void SpriteComponent::SetGhandle(int gh)
{
	mGhandle = gh;
	if (gh != -1) {
		int		width, height;

		GetGraphSize(gh, &width, &height);
		SetSize(Vector2((float)width, (float)height));
	}
}

//==============================================================
// 描画処理
//==============================================================
void SpriteComponent::Draw()
{
	if (mGhandle != -1) {
		Vector2 pos = mActor->GetPosition() + mOffset;

		DrawRotaGraph((int)pos.X, (int)pos.Y, 1, mAngle, mGhandle, TRUE);
	}
}
