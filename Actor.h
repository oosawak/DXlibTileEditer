//**************************************************************
// Actor�N���X(�R���|�[�l���g�w����)
// �쐬���F2024/02/13
// �쐬�ҁF�S�t
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
	class Game* mGame;							// Actor�����L����Game(�W��̊֌W)
	std::vector<class Component*> mComponents;	// Actor�����L����Componet(�R���|�W�V�����̊֌W)

	bool        mDead;

	Vector2		mPosition;
};
