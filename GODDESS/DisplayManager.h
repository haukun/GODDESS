/** 
 *	@file		DisplayManager.h
 *	@brief		ディスプレイ管理クラス
 *	@author		Hau-kun
 *	@date		2015/08/14
 *	@version	0.1
 */

#ifndef _DISPLAY_MANAGER_H_
#define _DISPLAY_MANAGER_H_
#pragma warning(disable:4482)

#include "stdafx.h"
#include <WinDef.h> 

/**
 *	ディスプレイデータクラス
 */
class DisplayData
{
private:
	int		nWidth;
	int		nHeight;
	int		nRatio;
	bool	fEnable;
public:
	void Set(int nWidth, int nHeight, int nRatio);
	void Enable(bool fFlg = true);
	bool IsEnable(void);
	RECT& GetRect(RECT* pRect);
};
void DisplayData::Set(int nWidth, int nHeight, int nRatio)
{
	this->nWidth = nWidth;
	this->nHeight = nHeight;
	this->nRatio = nRatio;
	this->fEnable = false;
}
void DisplayData::Enable(bool fFlg)
{
	this->fEnable = fFlg;
}
bool DisplayData::IsEnable(void)
{
	return this->fEnable;
}
RECT& DisplayData::GetRect(RECT* pRect)
{
	if(pRect != NULL)
	{
		SetRect(pRect, 0, 0, nWidth, nHeight);
	}

	return *pRect;
}


typedef enum DispType{
	IPHONE4x,
	IPHONE5x,
	IPHONE6,
	IPHONE6PLUS,
	VGA,
	SVGA,
	XGA,
	SXGA,
	HD,
	WXGA,
	FHD,
	WUXGA,
	XQXGA,
	D4K,
	D8K,
	MAX,
	MIN = 0,
}DispType;

/**
 *	ディスプレイ管理クラス
 */	
class DisplayManager
{
public:


private:
	DisplayData mDispDatas[DispType::MAX];

public:
	DisplayManager();
	void Enable(int type, bool fFlg = true);
	bool IsEnable(int type);
	RECT& GetRect(int type, RECT* pRect);

};


#endif