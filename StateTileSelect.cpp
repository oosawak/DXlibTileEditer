//**************************************************************
// StateTileSelectクラス(Stateパターン:タイル選択状態クラス)
// 作成日：2024/03/02
// 作成者：百春
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
		; // 何もしない
	}
	else {
		BoxComponent* box = mOwner->GetHitBox();
		if (box != nullptr && box->GetType() == BoxType::kTileMap) {
			mOwner->SetUpdateRequest(true);

			mOwner->SetMapRangeStartPos(mOwner->GetMousePos());
			mOwner->SetMapRangeEndPos(mOwner->GetMousePos());
		}
		else {
			; // 何もしない
		}
		mOwner->ChangeState(StateType::kNone);
	}
}
