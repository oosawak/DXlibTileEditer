//**************************************************************
// TileSet�N���X(Singleton�p�^�[��)
// �쐬���F2024/03/04
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once

class TileSet
{
public:
	~TileSet();
	static class TileSet* GetInstance();
	static void DeleteInstance();

	// �Ǝ��̃��\�b�h
	int GetGhandle(int index);

	static const int kXNum = 8, kYNum = 249, kXSize = 32, kYSize = 32;
	static const int kAllNum = kXNum * kYNum;

private:
	static class TileSet* _singleton;

	TileSet() {}
	TileSet(const class TileSet&) = delete;
	TileSet& operator=(const class TileSet&) = delete;

	void _initialize();

	static int     mGHandles[kAllNum];
};
