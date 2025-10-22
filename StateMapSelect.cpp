//**************************************************************
// StateMapSelectクラス(Stateパターン:無マップ選択状態クラス)
// 作成日：2024/02/29
// 作成者：百春
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
