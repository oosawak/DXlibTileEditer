//**************************************************************
// TileMapクラス
// 作成日：2024/03/04
// 作成者：百春
// Copyright (c) 2024, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#include "Actor.h"
#include <vector>

class TileMap :
    public Actor
{
public:
    TileMap(class Game* game);
    ~TileMap();

    class TileSpriteComponent* GetTileSprite(int index) { return mTileSprites[index]; }

    void GetRange(Vector2 pos1, Vector2 pos2, Vector2* start, Vector2* end);
    void SetRange(Vector2 start, Vector2 end, int gh, int tileIndex);

    void SaveCSV();
    void LoadCSV();
    void SavePNG(const char* filename);

    void Draw();

private:
    std::vector<class TileSpriteComponent*> mTileSprites;
    std::vector<int> mTileIndexes;

    void _correctPosition(Vector2* pos);
};

