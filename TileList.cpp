//**************************************************************
// TileListクラス(コンポーネント指向版)
// 作成日：2024/03/04
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "TileList.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "BoxComponent.h"
#include "TileSet.h"

TileList::TileList(Game* game)
	: Actor(game)
{
	int		index = 0;
	TileSet* tileSet = TileSet::GetInstance();

	for (int i = 0; i < TileSet::kYNum; i++) {
		for (int j = 0; j < TileSet::kXNum; j++) {
			Vector2 offset = Vector2(((float)j + 0.5f) * TileSet::kXSize, ((float)i + 0.5f) * TileSet::kYSize);

			SpriteComponent* sc = new SpriteComponent(this);
			sc->SetGhandle(tileSet->GetGhandle(index));
			sc->SetOffset(offset);

			BoxComponent* bc = new BoxComponent(this, BoxType::kTileList);
			bc->SetOffset(offset);
			bc->SetSize(sc->GetSize());
			bc->SetIndex(index);

			index++;
		}
	}
	new InputComponent(this, 300.0f);
}

TileList::~TileList()
{
}

void TileList::ActorInput(const char keyStatus[])
{
	if(keyStatus[KEY_INPUT_PGUP] == (int)KeyStatus::kJustReleased) {
		mPosition.Y += kWindowH - TileSet::kYSize;
	}
	if (keyStatus[KEY_INPUT_PGDN] == (int)KeyStatus::kJustReleased) {
		mPosition.Y -= kWindowH - TileSet::kYSize;
	}
	if (keyStatus[KEY_INPUT_HOME]) {
		mPosition.Y = 0;
	}
	if (keyStatus[KEY_INPUT_END]) {
		mPosition.Y = -(TileSet::kYNum * TileSet::kYSize - kWindowH);
	}
}

void TileList::ActorUpdate(float deltaTime)
{
	mPosition.Y += GetMouseWheelRotVol() * 1800.0f * deltaTime;

	if (mPosition.Y < -(TileSet::kYNum * TileSet::kYSize - kWindowH)) {
		mPosition.Y = -(TileSet::kYNum * TileSet::kYSize - kWindowH);
	}
	else if (mPosition.Y > 0) {
		mPosition.Y = 0;
	}
}
