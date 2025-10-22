//**************************************************************
// StateComponentクラス(Stateパターン)
// 作成日：2024/02/29
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Component.h"
#include "State.h"
#include <unordered_map>

class StateComponent :
    public Component
{
public:
    StateComponent(class Actor* owner, int order = 10);
    ~StateComponent();

    void ComponentUpdate(float deltaTime)override;

    void ChangeState(StateType type);
    void RegisterState(class State* state);

    class BoxComponent* GetHitBox() { return mHitBox; }

    bool GetMousePressed() { return mMousePressed; }

    int  GetTileIndex() { return mTileIndex; }
    void SetTileIndex(int index) { mTileIndex = index; }

    bool GetUpdateRequest() { return mUpdateRequest; }
    void SetUpdateRequest(bool flag) { mUpdateRequest = flag; }

    Vector2 GetMousePos() { return mMousePos; }

    Vector2 GetMapRangeStartPos() { return mMapRangeStartPos; }
    void SetMapRangeStartPos(Vector2 pos) { mMapRangeStartPos = pos; }

    Vector2 GetMapRangeEndPos() { return mMapRangeEndPos; }
    void SetMapRangeEndPos(Vector2 pos) { mMapRangeEndPos = pos; }

private:
    std::unordered_map<StateType, class State*> mStateMap;
    class State* mCurrentState;

    class BoxComponent* mHitBox;
    bool    mMousePressed;
    int     mTileIndex;
    bool    mUpdateRequest;

    Vector2 mMousePos;

    Vector2 mMapRangeStartPos;
    Vector2 mMapRangeEndPos;
};

