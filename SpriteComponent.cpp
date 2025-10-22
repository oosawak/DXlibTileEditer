//**************************************************************
// SpriteComponent�N���X(�摜�t�@�C���������p)
// �쐬���F2024/02/15
// �쐬�ҁF�S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************

#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

//==============================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//==============================================================
SpriteComponent::~SpriteComponent()
{
	mActor->GetGame()->RemoveSprite(this);
}

//==============================================================
// �O���t�B�b�N�n���h���̃Z�b�g
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
// �`�揈��
//==============================================================
void SpriteComponent::Draw()
{
	if (mGhandle != -1) {
		Vector2 pos = mActor->GetPosition() + mOffset;

		DrawRotaGraph((int)pos.X, (int)pos.Y, 1, mAngle, mGhandle, TRUE);
	}
}
