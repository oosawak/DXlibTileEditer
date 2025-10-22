//**************************************************************
// TileMap�N���X
// �쐬���F2024/03/04
// �쐬�ҁF�S�t
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "TileMap.h"
#include "TileSpriteComponent.h"
#include "BoxComponent.h"
#include "Game.h"
#include "TileSet.h"

#include <fstream>
#include <string>
#include <sstream>

constexpr float kPosX = 288.0f, kPosY = 32.0f;
constexpr int kXNum = 20, kYNum = 15, kTileSize = 32;
const char* CSVfname = "MAP.csv";
int mBGHandle;


TileMap::TileMap(Game* game)
	: Actor(game)
{
	mPosition = Vector2(kPosX, kPosY);

	int index = 0;
	for (int i = 0; i < kYNum; i++) {
		for (int j = 0; j < kXNum; j++) {
			Vector2 offset = Vector2((j + 0.5f) * kTileSize, (i + 0.5f) * kTileSize);
			Vector2 size = Vector2(kTileSize, kTileSize);

			TileSpriteComponent* sc = new TileSpriteComponent(this);
			sc->SetSize(size);
			sc->SetOffset(offset);
			mTileSprites.emplace_back(sc);
			mTileIndexes.emplace_back(-1);

			BoxComponent* bc = new BoxComponent(this, BoxType::kTileMap);
			bc->SetOffset(offset);
			bc->SetSize(size);
			bc->SetIndex(index);

			index++;
		}
	}
	mBGHandle = LoadGraph("IMAGE/BG.png");
	this->Draw();
}

TileMap::~TileMap()
{
	
}

void TileMap::GetRange(Vector2 pos1, Vector2 pos2, Vector2* start, Vector2* end)
{
	if (pos1.X > 0) {
		start->X = min(pos1.X, pos2.X);
		end->X = max(pos1.X, pos2.X);

		start->Y = min(pos1.Y, pos2.Y);
		end->Y = max(pos1.Y, pos2.Y);

		_correctPosition(start);
		_correctPosition(end);

		*end = *end + Vector2(kTileSize, kTileSize);
	}
}

void TileMap::SetRange(Vector2 start, Vector2 end, int gh, int tileIndex)
{
	for (float y = start.Y; y < end.Y; y += (float)kTileSize) {
		for (float x = start.X; x < end.X; x += (float)kTileSize) {
			int index = (int)((x - kPosX) / kTileSize) + (int)((y - kPosY) / kTileSize) * kXNum;
			mTileSprites[index]->SetGhandle(gh);
			mTileIndexes[index] = tileIndex;
		}
	}
}

void TileMap::SaveCSV()
{
	std::ofstream csvFile(CSVfname);

	if (csvFile) {
		for (int i = 0; i < kYNum; i++) {
			for (int j = 0; j < kXNum; j++) {
				csvFile << mTileIndexes[i * kXNum + j] << ',';
			}
			csvFile << std::endl;
		}
		clsDx();
	}
	else {
		printfDx("%s���o�͂ł��܂���ł���\n", CSVfname);
	}
}

void TileMap::LoadCSV()
{
	std::ifstream csvFile(CSVfname);

	if (csvFile) {
		int i = 0;
		std::string lineString;

		while (getline(csvFile, lineString)) {

			std::istringstream lineStream(lineString);
			std::string tileIndexString;
			while (getline(lineStream, tileIndexString, ',')) {
				int tileIndex = stoi(tileIndexString);

				mTileSprites[i]->SetGhandle(TileSet::GetInstance()->GetGhandle(tileIndex));
				mTileIndexes[i] = tileIndex;

				i++;
			}
		}
		clsDx();
	}
	else {
		printfDx("%s�����͂ł��܂���ł���\n", CSVfname);
	}
}

void TileMap::SavePNG(const char* filename)
{
	// �ۑ��p�̉���ʂ��쐬�i�T�C�Y�̓}�b�v�S�́j
	int width = kXNum * kTileSize;
	int height = kYNum * kTileSize;
	int tempScreen = MakeScreen(width, height, TRUE);

	if (tempScreen == -1) {
		printfDx("����ʂ̍쐬�Ɏ��s���܂���\n");
		return;
	}

	// �`��������ʂɐ؂�ւ�
	SetDrawScreen(tempScreen);
	ClearDrawScreen();

	// �w�i�`��iBG.png�j
	for (int i = 0; i < kYNum; ++i) {
		for (int j = 0; j < kXNum; ++j) {
			int x = j * kTileSize;
			int y = i * kTileSize;
			DrawGraph(x, y, mBGHandle, TRUE);
		}
	}

	// �^�C���`��
	for (int i = 0; i < kYNum; ++i) {
		for (int j = 0; j < kXNum; ++j) {
			int index = i * kXNum + j;
			int gh = TileSet::GetInstance()->GetGhandle(mTileIndexes[index]);
			if (gh != -1) {
				int x = j * kTileSize;
				int y = i * kTileSize;
				DrawGraph(x, y, gh, TRUE);
			}
		}
	}

	// PNG�Ƃ��ĕۑ�
	if (SaveDrawScreen(0, 0, width, height, filename) == -1) {
		printfDx("%s �̕ۑ��Ɏ��s���܂���\n", filename);
	}
	else {
		printfDx("%s ��ۑ����܂���\n", filename);
		mBGHandle = LoadGraph("IMAGE/BG.png");
	}

	// �`�������ɖ߂�
	SetDrawScreen(DX_SCREEN_BACK);
	DeleteGraph(tempScreen);
}


void TileMap::_correctPosition(Vector2* pos)
{
	float maxPosX = kPosX + (kXNum - 1) * kTileSize;
	float maxPosY = kPosY + (kYNum - 1) * kTileSize;

	pos->X = (int)((pos->X - kPosX) / kTileSize) * kTileSize + kPosX;
	pos->Y = (int)((pos->Y - kPosY) / kTileSize) * kTileSize + kPosY;

	if (pos->X < kPosX) pos->X = kPosX;
	if (pos->Y < kPosY) pos->Y = kPosY;
	if (pos->X > maxPosX) pos->X = maxPosX;
	if (pos->Y > maxPosY) pos->Y = maxPosY;
}
void TileMap::Draw()
{
	// �w�i�摜��`��iTileMap�̍���ɍ��킹��j
	DrawGraph((int)kPosX, (int)kPosY, mBGHandle, TRUE);
}

