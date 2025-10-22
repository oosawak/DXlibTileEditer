//**************************************************************
// Stateクラス(Stateパターン)
// 作成日：2024/02/24
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once

enum class StateType { kNone, kTileSelect, kMapSelect };

class State
{
public:
	State(class StateComponent* owner);
	~State();

	virtual void Update(float deltaTime) = 0;
	virtual StateType GetType() = 0;

protected:
	class StateComponent* mOwner;
};

