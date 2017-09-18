/**
	@file		UserMain.h
	@brief		ユーザーメインソースのヘッダー
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#ifndef		_USER_MAIN_H_
#define		_USER_MAIN_H_

#include "stdafx.h"
#include "UserHeader.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szStr, INT iCmdShow);
typedef struct DisplayData
{
	int nWidth;
	int nHeight;
	int nRatio;
	char strFormat[255];
}DisplayData;

extern DisplayData* pNowDisp;

#endif		//	_USER_MAIN_H_