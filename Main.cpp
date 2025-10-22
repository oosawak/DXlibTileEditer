//**************************************************************
// C++�����ҁ@Chapter06 �^�C���}�b�v�쐬�c�[��(�R���|�[�l���g�w��)
// (11) �^�C���}�b�v��CSV�t�@�C���o��
// �쐬���F 2024/03/04
// �쐬�ҁF �S�t
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
// �又��
//==============================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	GameMain();

	return _CrtDumpMemoryLeaks();	// ���������[�N�̃��O�_���v
}
