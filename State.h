//**************************************************************
// State�N���X(State�p�^�[��)
// �쐬���F2024/02/24
// �쐬�ҁF�S�t
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

