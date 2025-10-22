//**************************************************************
// MoveComponent�N���X(�������x�����^���̃W�����v)
// �쐬���F2024/01/12
// �쐬�ҁF�S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int order)
	: Component(owner, order)
	, mVelocity(Vector2(0,0))
	, mGravity(0)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::ComponentUpdate(float deltaTime)
{
	Vector2 pos = mActor->GetPosition();

	pos.X += mVelocity.X * deltaTime;

	pos.Y += mVelocity.Y * deltaTime + (mGravity / 2.0f) * deltaTime * deltaTime;
	mVelocity.Y += mGravity * deltaTime;

	mActor->SetPosition(pos);
}
