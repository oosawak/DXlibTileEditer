//**************************************************************
// Game�N���X(�R���|�[�l���g�w����)
// �쐬���F 2024/01/08
// �쐬�ҁF �S�t
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include <Dxlib.h>
#include <vector>
#include <map>
#include "MapMaker.h"

constexpr int kWindowW = 1000;					// �E�B���h�E�̕�
constexpr int kWindowH = 1000;					// �E�B���h�E�̍���

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

	bool		mIsRunning;		// true:�Q�[����, false:�Q�[���I��
	LONGLONG	mFpsTimer;		// FPS�\���p�^�C�}�[
	LONGLONG	mDeltaTimer;	// �f���^�^�C���v���p�^�C�}�[
	char		mKeyStatus[256];// �L�[�̓��͏��
	MapMaker*	mMapMaker;

	float		mScrollSpeed;
	float		mScrollDistance;
	int			mScore;								// ���_
	std::map<const char*, int> mSound;				// ���f�[�^�z��(�A�z�z��)
	std::map<const char*, int> mGraph;				// �摜�f�[�^�z��(�A�z�z��)

	bool mUpdatingActors;
	std::vector<class Actor*> mActors;				// �ʏ폈�����s��Actor�B
	std::vector<class Actor*> mPenActors;			// ���̃Q�[�����[�v�őΉ�����Actor�B
	std::vector<class SpriteComponent*> mSprites;	// �`��p
	std::vector<class BoxComponent*> mBoxs;			// �����蔻��p
};
