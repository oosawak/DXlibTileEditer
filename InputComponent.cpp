//**************************************************************
// InputComponent�N���X
// �쐬���F2024/02/14
// �쐬�ҁF�S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "InputComponent.h"
#include <DxLib.h>

InputComponent::InputComponent(Actor* owner, float speed)
	: MoveComponent(owner)
	, mSpeed(speed)
{
}

InputComponent::~InputComponent()
{
}

void InputComponent::ComponentInput(const char keyStatus[])
{
	if (keyStatus[KEY_INPUT_DOWN]) {
		mVelocity.Y = -mSpeed;
	}
	else if (keyStatus[KEY_INPUT_UP]) {
		mVelocity.Y = mSpeed;
	}
	else {
		mVelocity.Y = 0;
	}
}
