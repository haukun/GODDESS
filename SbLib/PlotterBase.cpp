/**
	@file		PlotterBase.cpp
	@brief		プロッタベース
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#include "stdafx.h"
#include "PlotterBase.h"
#include "PlotterHeader.h"

PlotterBase* PlotterBase::GetNewPlotter(int nMajor, int nMinor)
{
	PlotterBase* pResult = NULL;

	int nVersion = nMajor * 100 + nMinor;
	switch(nVersion)
	{
	case 1:
		pResult = new Plotter_v00_01();
		break;
	case 2:
		pResult = new Plotter_v00_02();
		break;
	case 3:
		pResult = new Plotter_v00_03();
		break;
	}

	return pResult;
}

void PlotterBase::PostOperate(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame)
{
	//	V00_02から実装
}

double PlotterBase::Calculate(char** ppAlgo, void* pInfo, int nDim)
{
	return Calculate(ppAlgo, pInfo);
}