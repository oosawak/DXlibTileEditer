//**************************************************************
// Game�N���X(�R���|�[�l���g�w����)
// �쐬���F 2024/02/17
// �쐬�ҁF �S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "Main.h"
#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "MapMaker.h"

//==============================================================
// �����֐��̃v���g�^�C�v�錾
//==============================================================
static void getKeyStatus(char status[]);
static void FpsDraw(LONGLONG* p);
static float getDeltaTime(LONGLONG* p);

//==============================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//==============================================================
Game::~Game()
{
}

//==============================================================
// ��������
//==============================================================
bool Game::Initialize()
{
#ifndef _DEBUG
	SetOutApplicationLogValidFlag(FALSE);
#endif

	ChangeWindowMode(TRUE);					// TRUE:Window���[�h
	SetGraphMode(kWindowW, kWindowH, 32);	// �E�B���h�E�T�C�Y�̐ݒ�

	SetMainWindowText("�^�C���}�b�v�쐬�c�[��");	// �E�B���h�E�^�C�g���Z�b�g

	if (DxLib_Init() == -1)		return false;

	LoadData();

	mFpsTimer = mDeltaTimer = GetNowHiPerformanceCount();

	return true;
}

//==============================================================
// �Q�[�����[�v
//==============================================================
void Game::RunLoop()
{
	SetDrawScreen(DX_SCREEN_BACK);			// �\����𗠉�ʂɐؑւ���(�_�u���o�b�t�@����)

	while (ProcessMessage() == 0 && mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();

		ScreenFlip();						// ����ʂƕ\��ʂ�ؑւ���
	}
}

//==============================================================
// �I������
//==============================================================
void Game::Shutdown()
{
	UnloadData();

	DxLib_End();
}

//==============================================================
// Actor�̒ǉ��ƍ폜
//==============================================================
//----------�ǉ�----------
using namespace std;
void Game::AddActor(Actor* actor)
{
	// �A�N�^�[�X�V���̏ꍇ�͕ۗ��ɒǉ�����
	if (mUpdatingActors) {
		mPenActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);			// �ʏ�̃A�N�^�[�ɒǉ�
	}
}
//----------�폜----------
void Game::RemoveActor(Actor* actor)
{
	// �ۗ����ɂ�������A��������폜
	mPenActors.erase(
		std::remove(std::begin(mPenActors), std::end(mPenActors), actor),
		std::cend(mPenActors)
	);

	// �ʏ��Ԃ�������A��������폜
	mActors.erase(
		std::remove(std::begin(mActors), std::end(mActors), actor),
		std::cend(mActors));
}

//==============================================================
// SpriteComponent(�`��p)�̒ǉ��ƍ폜
//==============================================================
//----------�ǉ�----------
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
//----------�폜----------
void Game::RemoveSprite(class SpriteComponent* sprite)
{
	mSprites.erase(
		std::remove(std::begin(mSprites), std::end(mSprites), sprite), 
		std::cend(mSprites));
}

//==============================================================
// BoxComponent(�Փˏ����p)�̒ǉ��ƍ폜
//==============================================================
//----------�ǉ�----------
void Game::AddBox(class BoxComponent* box)
{
	mBoxs.emplace_back(box);
}
//----------�폜----------
void Game::RemoveBox(class BoxComponent* box)
{
	mBoxs.erase(std::remove(std::begin(mBoxs), std::end(mBoxs), box), std::cend(mBoxs));
}

//==============================================================
// ���t�@�C���̃T�E���h�n���h�����擾
//==============================================================
int Game::LoadSound(const char* fname)
{
	int sh = -1;

	auto iter = mSound.find(fname);
	if (iter != mSound.end()) {
		sh = iter->second;					// �o�^�ς̏����擾
	}
	else {
		sh = LoadSoundMem(fname);			// �t�@�C�������[�h
		if (sh == -1) {
			printfDx("%s���ǂݍ��߂܂���\n", fname);
		}
		mSound.emplace(fname, sh);			// �T�E���h�z��ɒǉ�
	}
	return sh;
}

//==============================================================
// �摜�t�@�C���̃O���t�B�b�N�n���h�����擾
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
			printfDx("%s���ǂݍ��߂܂���ł���\n", fname);
		}
		mGraph.emplace(fname, gh);
	}
	return gh;
}

//==============================================================
// ���͏���
//==============================================================
void Game::ProcessInput()
{
	getKeyStatus(mKeyStatus);
	if (mKeyStatus[KEY_INPUT_ESCAPE]) {
		mIsRunning = false;
	}

	mUpdatingActors = true;	// �ȉ��̌J��Ԃ�����new���ꂽActor��mPenActors�ɒǉ�
	for (auto actor : mActors) {
		actor->Input(mKeyStatus);
	}
	mUpdatingActors = false;
}

//==============================================================
// �X�V����
//==============================================================
void Game::UpdateGame()
{
	float	deltaTime = getDeltaTime(&mDeltaTimer);

	mUpdatingActors = true;	// �ȉ��̌J��Ԃ�����new���ꂽActor��mPenActors�ɒǉ�
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// ���Q�[�����[�v�Œǉ����ꂽActor�͎��Q�[�����[�v�ŏ�������
	for (auto pending : mPenActors) {
		mActors.emplace_back(pending);
	}
	mPenActors.clear();

	// ���Q�[�����[�v�Ŏ��S����Actor��deadActors�ɑҔ�(�����Ȃ�폜�ł��Ȃ���)
	std::vector<Actor*> deadActors;
	for (auto actor : mActors) {
		if (actor->GetDead()) {
			deadActors.emplace_back(actor);
		}
	}

	// deadActors���폜(mActors����폜,deadActors�͎����̈�Ȃ̂Ŏ����I�ɏ���)
	for (auto actor : deadActors) {
		delete actor;
	}
}

//==============================================================
// �`�揈��
//==============================================================
void Game::GenerateOutput()
{
	ClearDrawScreen();					// ��ʃN���A

	mMapMaker->Draw();
	for (auto sprite : mSprites) {
		sprite->Draw();
	}

	FpsDraw(&mFpsTimer);				// FPS�̕\��
}

//==============================================================
// �f�[�^����
//==============================================================
void Game::LoadData()
{
	mMapMaker = new MapMaker(this);
}

//==============================================================
// �f�[�^��n��
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
// �L�[�X�e�[�^�X���쐬
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
// FPS�̌v���ƕ`��
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
// �f���^�^�C���̌v��
//==============================================================
static float getDeltaTime(LONGLONG* p)
{
	LONGLONG now = GetNowHiPerformanceCount();
	float    deltaTime = (float)(now - *p) / 1000000.0f;

	*p = now;
	return deltaTime;
}

