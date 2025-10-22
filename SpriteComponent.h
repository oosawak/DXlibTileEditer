//**************************************************************
// SpriteComponent�N���X(�摜�t�@�C���������p)
// �쐬���F2023/12/06
// �쐬�ҁF�S�t
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************

#pragma once
#include "Component.h"
#include "Vector2.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int order = 10);
	~SpriteComponent();

	virtual void SetGhandle(int gh);
	virtual void Draw();

	int GetSpriteOrder() const { return mSpriteOrder; }
	void SetAngle(float angle) { mAngle = angle; }

protected:
	int		mSpriteOrder;	// �`�揇��
	int		mGhandle;
	float	mAngle;
};
