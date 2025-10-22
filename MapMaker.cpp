//**************************************************************
// MapMakerƒNƒ‰ƒX(Stateƒpƒ^[ƒ“‚ðŽg‚¤)
// ì¬“úF2024/03/04
// ì¬ŽÒF•St
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Game.h"
#include "MapMaker.h"
#include "TileList.h"
#include "TileMap.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include "TileSpriteComponent.h"
#include "StateComponent.h"
#include "StateNone.h"
#include "StateTileSelect.h"
#include "StateMapSelect.h"
#include "TileSet.h"

MapMaker::MapMaker(Game* game)
	: Actor(game)
{
	new TileList(game);
	mTileMap = new TileMap(game);
	mTileSet = TileSet::GetInstance();
	mState = new StateComponent(this);
	mState->RegisterState(new StateNone(mState));
	mState->RegisterState(new StateTileSelect(mState));
	mState->RegisterState(new StateMapSelect(mState));
	mState->ChangeState(StateType::kNone);

	mCursorSprite = new SpriteComponent(this);
	mMapRangeSprite = new TileSpriteComponent(this);
	mMapRangeSprite->SetColor(GetColor(255, 0, 255));
}

MapMaker::~MapMaker()
{
	delete mTileSet;
}

void MapMaker::ActorInput(const char keyStatus[])
{
	if (keyStatus[KEY_INPUT_DELETE]) {
		mState->SetUpdateRequest(true);
		mState->SetTileIndex(-1);
	}
	if ((keyStatus[KEY_INPUT_LCONTROL] || keyStatus[KEY_INPUT_RCONTROL]) && 
		keyStatus[KEY_INPUT_S] == (int)KeyStatus::kJustReleased) {
		mTileMap->SaveCSV();
	}
	if ((keyStatus[KEY_INPUT_LCONTROL] || keyStatus[KEY_INPUT_RCONTROL]) &&
		keyStatus[KEY_INPUT_L] == (int)KeyStatus::kJustReleased) {
		mTileMap->LoadCSV();
	}
	if ((keyStatus[KEY_INPUT_LCONTROL] || keyStatus[KEY_INPUT_RCONTROL]) &&
		keyStatus[KEY_INPUT_B] == (int)KeyStatus::kJustReleased) {
		mTileMap->SavePNG("IMAGE/BG.png");
	}
}

void MapMaker::ActorUpdate(float deltaTime)
{
	int tileIndex = mState->GetTileIndex();
	int gh = mTileSet->GetGhandle(tileIndex);



	mCursorSprite->SetGhandle(gh);
	mCursorSprite->SetOffset(mState->GetMousePos());

	Vector2 start, end;
	mTileMap->GetRange(mState->GetMapRangeStartPos(), mState->GetMapRangeEndPos(),
		&start, &end);
	mMapRangeSprite->SetOffset((start + end) * 0.5f);
	mMapRangeSprite->SetSize(end - start);

	if (mState->GetUpdateRequest()) {
		mState->SetUpdateRequest(false);

		mTileMap->SetRange(start, end, gh, tileIndex);

		mState->SetMapRangeStartPos(Vector2(0, 0));
		mState->SetMapRangeEndPos(Vector2(0, 0));
	}
}
void MapMaker::Draw()
{
	// ”wŒi‰æ‘œ‚ð•`‰æiTileMap‚Ì¶ã‚É‡‚í‚¹‚éj
	mTileMap->Draw();
}
