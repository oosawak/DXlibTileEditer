//**************************************************************
// TileSetクラス(Singletonパターン)
// 作成日：2024/02/17
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "TileSet.h"
#include "Game.h"

TileSet* TileSet::_singleton = nullptr;
int     TileSet::mGHandles[kAllNum] = { 0 };

TileSet::~TileSet()
{
	DeleteInstance();
	_singleton = nullptr;
}

TileSet* TileSet::GetInstance()
{
	if (_singleton == nullptr) {
		_singleton = new TileSet();
		_singleton->_initialize();
	}
	return _singleton;
}

void TileSet::DeleteInstance()
{
	memset(mGHandles, -1, sizeof(mGHandles));
}

int TileSet::GetGhandle(int index)
{
	if (index >= 0 && index < kAllNum) {
		return mGHandles[index];
	}
	else {
		return -1;
	}
}

void TileSet::_initialize()
{
	const char* kTileSetFName = "IMAGE/BaseChip_pipo.png";

	if (LoadDivGraph(kTileSetFName, kAllNum, kXNum, kYNum, kXSize, kYSize, mGHandles) == -1) {
		printfDx("%sが読み込みできませんでした\n", kTileSetFName);
		memset(mGHandles, -1, sizeof(mGHandles));
	}
}
