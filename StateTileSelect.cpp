//**************************************************************
// StateTileSelect�N���X(State�p�^�[��:�^�C���I����ԃN���X)
// �쐬���F2024/03/02
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "StateTileSelect.h"
#include "StateComponent.h"
#include "BoxComponent.h"

StateTileSelect::StateTileSelect(StateComponent* owner)
	: State(owner)
{
}

StateTileSelect::~StateTileSelect()
{
}

void StateTileSelect::Update(float deltaTime)
{
	if (mOwner->GetMousePressed()) {
		; // �������Ȃ�
	}
	else {
		BoxComponent* box = mOwner->GetHitBox();
		if (box != nullptr && box->GetType() == BoxType::kTileMap) {
			mOwner->SetUpdateRequest(true);

			mOwner->SetMapRangeStartPos(mOwner->GetMousePos());
			mOwner->SetMapRangeEndPos(mOwner->GetMousePos());
		}
		else {
			; // �������Ȃ�
		}
		mOwner->ChangeState(StateType::kNone);
	}
}
