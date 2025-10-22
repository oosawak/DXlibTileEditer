//**************************************************************
// Gameクラス(コンポーネント指向版)
// 作成日： 2024/02/17
// 作成者： 百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Main.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MapMaker.h"

//==============================================================
// 内部関数のプロトタイプ宣言
//==============================================================
static void getKeyStatus(char status[]);
static void FpsDraw(LONGLONG* p);
static float getDeltaTime(LONGLONG* p);

//==============================================================
// コンストラクタ
//==============================================================
Game::Game()
	: mIsRunning(true)
	, mFpsTimer(0)
	, mDeltaTimer(0)
	, mKeyStatus{ 0 }
	, mScore(0)
{
}

//==============================================================
// デストラクタ
//==============================================================
Game::~Game()
{
}

//==============================================================
// 初期処理
//==============================================================
bool Game::Initialize()
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(FALSE);
#endif

	ChangeWindowMode(TRUE);					// TRUE:Windowモード
	SetGraphMode(kWindowW, kWindowH, 32);	// ウィンドウサイズの設定

	SetMainWindowText("タイルマップ作成ツール");	// ウィンドウタイトルセット

	if (DxLib_Init() == -1)		return false;

	LoadData();

	mFpsTimer = mDeltaTimer = GetNowHiPerformanceCount();

	return true;
}

//==============================================================
// ゲームループ
//==============================================================
void Game::RunLoop()
{
	SetDrawScreen(DX_SCREEN_BACK);			// 表示先を裏画面に切替える(ダブルバッファ方式)

	while (ProcessMessage() == 0 && mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();

		ScreenFlip();						// 裏画面と表画面を切替える
	}
}

//==============================================================
// 終了処理
//==============================================================
void Game::Shutdown()
{
	UnloadData();

	DxLib_End();
}

//==============================================================
// Actorの追加と削除
//==============================================================
//----------追加----------
using namespace std;
void Game::AddActor(Actor* actor)
{
	// アクター更新中の場合は保留に追加する
	if (mUpdatingActors) {
		mPenActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);			// 通常のアクターに追加
	}
}
//----------削除----------
void Game::RemoveActor(Actor* actor)
{
	// 保留中にあったら、そこから削除
	mPenActors.erase(
		std::remove(std::begin(mPenActors), std::end(mPenActors), actor),
		std::cend(mPenActors)
	);

	// 通常状態だったら、そこから削除
	mActors.erase(
		std::remove(std::begin(mActors), std::end(mActors), actor),
		std::cend(mActors));
}

//==============================================================
// SpriteComponent(描画用)の追加と削除
//==============================================================
//----------追加----------
void Game::AddSprite(class SpriteComponent* sprite)
{
	int myOrder = sprite->GetSpriteOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter) {
		if (myOrder < (*iter)->GetSpriteOrder()) {
			break;
		}
	}
	mSprites.insert(iter, sprite);
}
//----------削除----------
void Game::RemoveSprite(class SpriteComponent* sprite)
{
	mSprites.erase(
		std::remove(std::begin(mSprites), std::end(mSprites), sprite), 
		std::cend(mSprites));
}

//==============================================================
// BoxComponent(衝突処理用)の追加と削除
//==============================================================
//----------追加----------
void Game::AddBox(class BoxComponent* box)
{
	mBoxs.emplace_back(box);
}
//----------削除----------
void Game::RemoveBox(class BoxComponent* box)
{
	mBoxs.erase(std::remove(std::begin(mBoxs), std::end(mBoxs), box), std::cend(mBoxs));
}

//==============================================================
// 音ファイルのサウンドハンドルを取得
//==============================================================
int Game::LoadSound(const char* fname)
{
	int sh = -1;

	auto iter = mSound.find(fname);
	if (iter != mSound.end()) {
		sh = iter->second;					// 登録済の情報を取得
	}
	else {
		sh = LoadSoundMem(fname);			// ファイルをロード
		if (sh == -1) {
			printfDx("%sが読み込めません\n", fname);
		}
		mSound.emplace(fname, sh);			// サウンド配列に追加
	}
	return sh;
}

//==============================================================
// 画像ファイルのグラフィックハンドルを取得
//==============================================================
int Game::LoadGraph(const char* fname)
{
	int		gh = -1;

	auto iter = mGraph.find(fname);
	if (iter != mGraph.end()) {
		gh = iter->second;
	}
	else {
		gh = DxLib::LoadGraph(fname);
		if (gh == -1) {
			printfDx("%sが読み込めませんでした\n", fname);
		}
		mGraph.emplace(fname, gh);
	}
	return gh;
}

//==============================================================
// 入力処理
//==============================================================
void Game::ProcessInput()
{
	getKeyStatus(mKeyStatus);
	if (mKeyStatus[KEY_INPUT_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;	// 以下の繰り返し中にnewされたActorはmPenActorsに追加
	for (auto actor : mActors) {
		actor->Input(mKeyStatus);
	}
	mUpdatingActors = false;
}

//==============================================================
// 更新処理
//==============================================================
void Game::UpdateGame()
{
	float	deltaTime = getDeltaTime(&mDeltaTimer);

	mUpdatingActors = true;	// 以下の繰り返し中にnewされたActorはmPenActorsに追加
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 現ゲームループで追加されたActorは次ゲームループで処理する
	for (auto pending : mPenActors) {
		mActors.emplace_back(pending);
	}
	mPenActors.clear();

	// 現ゲームループで死亡したActorをdeadActorsに待避(いきなり削除できない為)
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetDead()) {
			deadActors.emplace_back(actor);
		}
	}

	// deadActorsを削除(mActorsから削除,deadActorsは自動領域なので自動的に消滅)
	for (auto actor : deadActors) {
		delete actor;
	}
}

//==============================================================
// 描画処理
//==============================================================
void Game::GenerateOutput()
{
	ClearDrawScreen();					// 画面クリア

	mMapMaker->Draw();
	for (auto sprite : mSprites) {
		sprite->Draw();
	}

	FpsDraw(&mFpsTimer);				// FPSの表示
}

//==============================================================
// データ準備
//==============================================================
void Game::LoadData()
{
	mMapMaker = new MapMaker(this);
}

//==============================================================
// データ後始末
//==============================================================
void Game::UnloadData()
{
	while (!mActors.empty()) {
		delete mActors.back();
	}
	InitGraph();
	mGraph.clear();
	InitSoundMem();
	mSound.clear();
}

//==============================================================
// キーステータスを作成
//==============================================================
static void getKeyStatus(char status[])
{
	static char preKeys[256] = { 0 };
	char		nowKeys[256];

	GetHitKeyStateAll(nowKeys);
	for (size_t i = 0; i < 256; i++) {
		status[i] = (preKeys[i] << 1) | nowKeys[i];
		preKeys[i] = nowKeys[i];
	}
}

//==============================================================
// FPSの計測と描画
//==============================================================
static void FpsDraw(LONGLONG* p)
{
#ifdef _DEBUG
	static int Fps = 0, FpsCnt = 0;
	LONGLONG now = GetNowHiPerformanceCount();

	FpsCnt++;
	if (now - *p > 1000000) {
		Fps = FpsCnt;
		FpsCnt = 0;
		*p = now;
	}
	DrawFormatString(0, 0, GetColor(128, 128, 128), "FPS: %d", Fps);
#endif
}

//==============================================================
// デルタタイムの計測
//==============================================================
static float getDeltaTime(LONGLONG* p)
{
	LONGLONG now = GetNowHiPerformanceCount();
	float    deltaTime = (float)(now - *p) / 1000000.0f;

	*p = now;
	return deltaTime;
}

