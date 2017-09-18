#include "stdafx.h"
#include "DisplayManager.h"

DisplayManager::DisplayManager()
{
	mDispDatas[DispType::IPHONE4x].Set(		640 / 2,	960 / 2,	50);
	mDispDatas[DispType::IPHONE5x].Set(		640 / 2,	1136 / 2,	58);
	mDispDatas[DispType::IPHONE6].Set(		750 / 2,	1334 / 2,	65);
	mDispDatas[DispType::IPHONE6PLUS].Set(	1080 / 2,	1920 / 2,	84);
	mDispDatas[DispType::VGA].Set(			640,		480,		50);
	mDispDatas[DispType::SVGA].Set			(800,		600,		62);
	mDispDatas[DispType::XGA].Set(			1024,		768,		80);
	mDispDatas[DispType::SXGA].Set(			1280,		1024,		106);
	mDispDatas[DispType::HD].Set(			1366,		768,		80);
	mDispDatas[DispType::WXGA].Set(			1440,		900,		93);
	mDispDatas[DispType::FHD].Set(			1920,		1080,		112);
	mDispDatas[DispType::WUXGA].Set(		1920,		1200,		125);
	mDispDatas[DispType::XQXGA].Set(		2560,		1600,		166);
	mDispDatas[DispType::D4K].Set(			4096,		2160,		225);
	mDispDatas[DispType::D8K].Set(			8192,		4320,		450);
}

void DisplayManager::Enable(int type, bool fFlg)
{
	mDispDatas[type].Enable(fFlg);
}
bool DisplayManager::IsEnable(int type)
{
	return mDispDatas[type].IsEnable();
}
RECT& DisplayManager::GetRect(int type, RECT* pRect)
{
	return mDispDatas[type].GetRect(pRect);
}