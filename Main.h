//**************************************************************
// メモリリーク確認用ヘッダ
// 作成日： 2023/09/28
// 作成者： 百春
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define MYDEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new MYDEBUG_NEW
#endif
