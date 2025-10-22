//**************************************************************
// StateMapSelect�N���X(State�p�^�[��:���}�b�v�I����ԃN���X)
// �쐬���F2024/02/29
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "StateMapSelect.h"
#include "StateComponent.h"

StateMapSelect::StateMapSelect(StateComponent* owner)
	: State(owner)
{
}

StateMapSelect::~StateMapSelect()
{
}

void StateMapSelect::Update(float deltaTime)
{
	if (mOwner->GetMousePressed()) {
		mOwner->SetMapRangeEndPos(mOwner->GetMousePos());
	}
	else {
		mOwner->ChangeState(StateType::kNone);
	}
}
