//**************************************************************
// Stateクラス(Stateパターン)
// 作成日：2024/02/24
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "State.h"

State::State(StateComponent* owner)
	: mOwner(owner)
{
}

State::~State()
{
}
