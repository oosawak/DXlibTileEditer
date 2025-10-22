//**************************************************************
// TileMapクラス
// 作成日：2024/03/04
// 作成者：百春
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
		printfDx("%sが出力できませんでした\n", CSVfname);
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
		printfDx("%sが入力できませんでした\n", CSVfname);
	}
}

void TileMap::SavePNG(const char* filename)
{
	// 保存用の仮画面を作成（サイズはマップ全体）
	int width = kXNum * kTileSize;
	int height = kYNum * kTileSize;
	int tempScreen = MakeScreen(width, height, TRUE);

	if (tempScreen == -1) {
		printfDx("仮画面の作成に失敗しました\n");
		return;
	}

	// 描画先を仮画面に切り替え
	SetDrawScreen(tempScreen);
	ClearDrawScreen();

	// 背景描画（BG.png）
	for (int i = 0; i < kYNum; ++i) {
		for (int j = 0; j < kXNum; ++j) {
			int x = j * kTileSize;
			int y = i * kTileSize;
			DrawGraph(x, y, mBGHandle, TRUE);
		}
	}

	// タイル描画
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

	// PNGとして保存
	if (SaveDrawScreen(0, 0, width, height, filename) == -1) {
		printfDx("%s の保存に失敗しました\n", filename);
	}
	else {
		printfDx("%s を保存しました\n", filename);
		mBGHandle = LoadGraph("IMAGE/BG.png");
	}

	// 描画先を元に戻す
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
	// 背景画像を描画（TileMapの左上に合わせる）
	DrawGraph((int)kPosX, (int)kPosY, mBGHandle, TRUE);
}

