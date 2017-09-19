/**
	@file		PlotEngine.h
	@brief		�v���b�g�G���W���w�b�_�[
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#ifndef		_PLOT_ENGINE_H_
#define		_PLOT_ENGINE_H_

#include "stdafx.h"
#include "SbLib\SbHeader.h"
#include "PlotterHeader.h"
#include "config.h"


//	�v���b�g���e
enum PLOT_PHASE
{
	BEGIN = 0,
	GENERATING,
	FINISH,
};


class PlotEngine
{
public:
	PlotEngine();

	bool Setup(void);
	void Save(const char* strFileName);
	double Execute(LogicParam* pParam);
	void PostExecute(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame);

	int GetSeedIndex(void);
	PlotterBase* m_plotter;
private:

	int m_nSeedIndex;

};

#endif	//	_PLOT_ENGINE_H_