//**************************************************************
// Component�N���X
// �쐬���F2023/10/30
// �쐬�ҁF�S�t
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Component.h"
#include "Actor.h"

//==============================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//==============================================================
Component::~Component()
{
	mActor->RemoveComponent(this);
}
