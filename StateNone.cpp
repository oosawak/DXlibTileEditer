//**************************************************************
// StateNoneクラス(Stateパターン:無選択状態クラス)
// 作成日：2024/03/02
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "StateNone.h"
#include "StateComponent.h"
#include "BoxComponent.h"

StateNone::StateNone(StateComponent* owner)
	: State(owner)
{
}

StateNone::~StateNone()
{
}

void StateNone::Update(float deltaTime)
{
	if (mOwner->GetMousePressed()) {
		BoxComponent* box = mOwner->GetHitBox();
		if (box != nullptr && box->GetType() == BoxType::kTileList) {
			mOwner->SetUpdateRequest(true);

			mOwner->SetTileIndex(box->GetIndex());
			mOwner->ChangeState(StateType::kTileSelect);
		}
		else if (box != nullptr && box->GetType() == BoxType::kTileMap) {
			mOwner->SetMapRangeStartPos(mOwner->GetMousePos());
			mOwner->SetMapRangeEndPos(mOwner->GetMousePos());
			mOwner->ChangeState(StateType::kMapSelect);
		}
		else {
			mOwner->SetMapRangeStartPos(Vector2(0, 0));
			mOwner->SetMapRangeEndPos(Vector2(0, 0));
		}
	}
	else {
		mOwner->SetTileIndex(-1);
	}
}
