//**************************************************************
// Actorクラス(コンポーネント指向版)
// 作成日：2024/02/13
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include <DxLib.h>

//==============================================================
// コンストラクタ
//==============================================================
Actor::Actor(class Game* game)
	: mGame(game)
	, mDead(false)
	, mPosition(Vector2(0,0))
{
	mGame->AddActor(this);
}

//==============================================================
// デストラクタ
//==============================================================
Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

//==============================================================
// 入力処理
//==============================================================
void Actor::Input(const char keyStatus[])
{
	if (!mDead) {
		for (auto comp : mComponents) {
			comp->ComponentInput(keyStatus);
		}
		ActorInput(keyStatus);
	}
}

//==============================================================
// 更新処理
//==============================================================
void Actor::Update(float deltaTime)
{
	if (!mDead) {
		for (auto comp : mComponents) {
			comp->ComponentUpdate(deltaTime);
		}
		ActorUpdate(deltaTime);
	}
}

//==============================================================
// Componentの追加と削除
//==============================================================
//----------追加----------
void Actor::AddComponent(Component* component)
{
	// 挿入位置(自分より前の最初の位置)を見つける
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);	// イテレータの前の位置に要素を挿入
}
//----------削除----------
void Actor::RemoveComponent(Component* component)
{
	mComponents.erase(
		std::remove(std::begin(mComponents), std::end(mComponents), component), 
		std::cend(mComponents));
}
