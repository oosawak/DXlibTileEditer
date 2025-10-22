//**************************************************************
// InputComponentクラス
// 作成日：2024/02/14
// 作成者：百春
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
