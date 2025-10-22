//**************************************************************
// Actorクラス(コンポーネント指向版)
// 作成日：2024/02/13
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include <vector>
#include "Vector2.h"

class Actor
{
public:
	Actor(class Game* game);
	virtual ~Actor();

	void Input(const char keyStatus[]);
	virtual void ActorInput(const char keyStatus[]) {}

	void Update(float deltaTime);
	virtual void ActorUpdate(float deltaTime) {}

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	class Game* GetGame() { return mGame; }

	bool GetDead() { return mDead; }

	void SetPosition(Vector2 pos) { mPosition = pos; }
	Vector2 GetPosition() { return mPosition; }

protected:
	class Game* mGame;							// Actorが所有するGame(集約の関係)
	std::vector<class Component*> mComponents;	// Actorが所有するComponet(コンポジションの関係)

	bool        mDead;

	Vector2		mPosition;
};
