//**************************************************************
// Component�N���X
// �쐬���F2023/10/30
// �쐬�ҁF�S�t
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
	class Actor* mActor;		// Component�����L����Actor(�W��̊֌W)
	int			 mUpdateOrder;	// �X�V����(���������ɍX�V)
	Vector2		 mOffset;		// Actor�̈ʒu����̕ψ�
	Vector2		 mSize;         // �T�C�Y
};
