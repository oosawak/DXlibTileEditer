//**************************************************************
// Componentクラス
// 作成日：2023/10/30
// 作成者：百春
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Vector2.h"

class Component
{
public:
	Component(class Actor* owner, int order = 10);
	virtual ~Component();

	virtual void ComponentInput(const char keyStatus[]) {}
	virtual void ComponentUpdate(float deltaTime) {}

	class Actor* GetActor() const { return mActor; }
	int GetUpdateOrder() const { return mUpdateOrder; }
	void SetOffset(Vector2 offset) { mOffset = offset; }
	void SetSize(Vector2 size) { mSize = size; }
	Vector2 GetSize() { return mSize; }

protected:
	class Actor* mActor;		// Componentが所有するActor(集約の関係)
	int			 mUpdateOrder;	// 更新順序(小さい順に更新)
	Vector2		 mOffset;		// Actorの位置からの変位
	Vector2		 mSize;         // サイズ
};
