//**************************************************************
// C++初歩編　Chapter06 タイルマップ作成ツール(コンポーネント指向)
// (11) タイルマップのCSVファイル出力
// 作成日： 2024/03/04
// 作成者： 百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Main.h"
#include "Game.h"

void GameMain()
{
	Game game;

	if (game.Initialize()) {
		game.RunLoop();
		game.Shutdown();
	}
}

//==============================================================
// 主処理
//==============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	GameMain();

	return _CrtDumpMemoryLeaks();	// メモリリークのログダンプ
}
