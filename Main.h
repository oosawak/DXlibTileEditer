//**************************************************************
// ���������[�N�m�F�p�w�b�_
// �쐬���F 2023/09/28
// �쐬�ҁF �S�t
// Copyright (c) 2023, momoharu(Naoko Ueda) All rights reserved.
//**************************************************************
#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define MYDEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new MYDEBUG_NEW
#endif
