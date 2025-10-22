//**************************************************************
// StateComponentƒNƒ‰ƒX(Stateƒpƒ^[ƒ“)
// ì¬“úF2024/02/24
// ì¬ÒF•St
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "StateComponent.h"
#include "Game.h"
#include "Actor.h"
#include "BoxComponent.h"

StateComponent::StateComponent(Actor* owner, int order)
	: Component(owner, order)
	, mCurrentState(nullptr)
	, mHitBox(nullptr)
	, mMousePressed(false)
	, mTileIndex(-1)
	, mUpdateRequest(false)
	, mMousePos(Vector2(0,0))
{
}

StateComponent::~StateComponent()
{
	for (auto x : mStateMap) {
		delete x.second;
	}
}

void StateComponent::ComponentUpdate(float deltaTime)
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	mMousePos = Vector2((float)mouseX, (float)mouseY);

	mMousePressed = GetMouseInput() & MOUSE_INPUT_LEFT;

	mHitBox = nullptr;
	for (auto box : mActor->GetGame()->GetBoxs()) {
		if (Intersect(*box, mMousePos)) {
			mHitBox = box;
			break;
		}
	}

	if (mCurrentState) {
		mCurrentState->Update(deltaTime);
	}
}

void StateComponent::ChangeState(StateType type)
{
	auto it = mStateMap.find(type);
	if (it != mStateMap.end()) {
		mCurrentState = it->second;
	}
	else {
		printfDx("%d‚Ìó‘Ô‚ª“o˜^‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ\n", (int)type);
		mCurrentState = nullptr;
	}
}

void StateComponent::RegisterState(State* state)
{
	mStateMap.emplace(state->GetType(), state);
}
