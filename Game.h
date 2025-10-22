//**************************************************************
// Gameクラス(コンポーネント指向版)
// 作成日： 2024/01/08
// 作成者： 百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include <Dxlib.h>
#include <vector>
#include <map>
#include "MapMaker.h"

constexpr int kWindowW = 1000;					// ウィンドウの幅
constexpr int kWindowH = 1000;					// ウィンドウの高さ

enum class KeyStatus { kReleased, kJustPressed, kJustReleased, kPressed };

class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	float	GetScrollSpeed() { return mScrollSpeed; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float	GetScrollDistance() { return mScrollDistance; }
	void SetScrollDistance(float distance) { mScrollDistance = distance; }

	int	GetScore() { return mScore; }
	void SetScore(int score) { mScore = score; }

	int LoadSound(const char* fname);
	int LoadGraph(const char* fname);

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);

	std::vector<class BoxComponent*>GetBoxs() { return mBoxs; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	bool		mIsRunning;		// true:ゲーム中, false:ゲーム終了
	LONGLONG	mFpsTimer;		// FPS表示用タイマー
	LONGLONG	mDeltaTimer;	// デルタタイム計測用タイマー
	char		mKeyStatus[256];// キーの入力状態
	MapMaker*	mMapMaker;

	float		mScrollSpeed;
	float		mScrollDistance;
	int			mScore;								// 得点
	std::map<const char*, int> mSound;				// 音データ配列(連想配列)
	std::map<const char*, int> mGraph;				// 画像データ配列(連想配列)

	bool mUpdatingActors;
	std::vector<class Actor*> mActors;				// 通常処理を行うActor達
	std::vector<class Actor*> mPenActors;			// 次のゲームループで対応するActor達
	std::vector<class SpriteComponent*> mSprites;	// 描画用
	std::vector<class BoxComponent*> mBoxs;			// 当たり判定用
};
