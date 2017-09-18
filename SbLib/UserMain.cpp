/**
	@file		UserMain.cpp
	@brief		ユーザーメインソース
	@author		Hau-kun
	@date		2010/05/08
	@version	1.0
*/

#include "stdafx.h"
#include "UserMain.h"
#include "Goddess.h"

int nDispIndex = 0;
DisplayData dispData[] = {
//							Width			Height			Ratio	Format							//	Target
							//{(640 / 2),		(960 / 2),		50,		"Postella_v01_%03d_00"},		//	iPhone4x
							//{(640 / 2),		(1136 / 2),		58,		"Postella_v01_%03d_01"},		//	iPhone5x
							//{(750 / 2),		(1334 / 2),		65,		"Postella_v01_%03d_02"},		//	iPhone6
							//{(1080 / 2),	(1920 / 2),		84,		"Postella_v01_%03d_03"},		//	iPhone6Plus
							{(640),			(480),			50,		"Wallpaper_v02_%04d_00"},		//	VGA
							//{(800),			(600),			62,		"Wallpaper_v02_%04d_01"},		//	WVGA
							//{(1024),		(768),			80,		"Wallpaper_v02_%04d_02"},		//	XGA
							//{(1280),		(1024),		   106,		"Wallpaper_v02_%04d_03"},		//	SXGA
							//{(1366),		(768),			80,		"Wallpaper_v02_%04d_04"},		//	HD FWXGA(11' MBA)
							//{(1440),		(900),			93,		"Wallpaper_v02_%04d_05"},		//	WXGA+(13' MBA)
							//{(1920),		(1080),		   112,		"Wallpaper_v02_%04d_06"},		//	FullHD
							//{(1920),		(1200),		   125,		"Wallpaper_v02_%04d_07"},		//	WUXGA
							//{(2560),		(1600),		   166,		"Wallpaper_v02_%04d_08"},		//	XQXGA
							//{(4096),		(2160),		   225,		"Wallpaper_v02_%04d_09"},		//	4K
							//{(8192),		(4320),		   450,		"Wallpaper_v01_%04d_10"},		//	8K
					};
DisplayData* pNowDisp;

/**
	@fn			INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
	@brief		エントリーポイント
	@param[in]	HINSTANCE	hInst		(Windows既定)
	@param[in]	HINSTANCE	hPrevInst	(Windows既定)
	@param[in]	LPSTR		szStr		(Windows既定)
	@param[in]	INT			iCmdShow	(Windows既定)
	@note		プログラムのエントリーポイントです。
	@date		2010/05/08
	@version	1.0
*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szStr, INT iCmdShow)
{
	int nLoop = sizeof(dispData) / sizeof(DisplayData);
	for(nDispIndex = 0; nDispIndex < nLoop; nDispIndex++)
	{
		pNowDisp = &dispData[nDispIndex];

		RECT rect;
		SetRect(&rect, 0, 0, pNowDisp->nWidth, pNowDisp->nHeight);
	
		SbWindow* pWnd = new SbWindow(rect, hInst, hPrev, szStr, iCmdShow);

		Goddess goddess(pWnd);

		goddess.Action(NULL);
    
		delete pWnd;
	}


}
