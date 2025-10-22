//**************************************************************
// ScrollComponentクラス(コンポーネント指向版)
// 作成日： 2024/01/12
// 作成者： 百春
// Copyright (c) 2023-4, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#include "ScrollComponent.h"
#include "Actor.h"
#include "Game.h"

ScrollComponent::ScrollComponent(Actor* owner, int order)
	: Component(owner, order)
{
}

ScrollComponent::~ScrollComponent()
{
}

void ScrollComponent::ComponentUpdate(float deltaTime)
{
	Vector2 pos = mActor->GetPosition();

	pos.Y += mActor->GetGame()->GetScrollSpeed() * deltaTime + 
		mActor->GetGame()->GetScrollDistance();
	mActor->SetPosition(pos);
}
