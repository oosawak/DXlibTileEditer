//**************************************************************
// Actor�N���X(�R���|�[�l���g�w����)
// �쐬���F2024/02/13
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include <DxLib.h>

//==============================================================
// �R���X�g���N�^
//==============================================================
Actor::Actor(class Game* game)
	: mGame(game)
	, mDead(false)
	, mPosition(Vector2(0,0))
{
	mGame->AddActor(this);
}

//==============================================================
// �f�X�g���N�^
//==============================================================
Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty()) {
		delete mComponents.back();
	}
}

//==============================================================
// ���͏���
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
// �X�V����
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
// Component�̒ǉ��ƍ폜
//==============================================================
//----------�ǉ�----------
void Actor::AddComponent(Component* component)
{
	// �}���ʒu(�������O�̍ŏ��̈ʒu)��������
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}
	mComponents.insert(iter, component);	// �C�e���[�^�̑O�̈ʒu�ɗv�f��}��
}
//----------�폜----------
void Actor::RemoveComponent(Component* component)
{
	mComponents.erase(
		std::remove(std::begin(mComponents), std::end(mComponents), component), 
		std::cend(mComponents));
}
