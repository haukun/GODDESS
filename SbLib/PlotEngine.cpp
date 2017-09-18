/**
	@file		PlotEngine.cpp
	@brief		�v���b�g�G���W���N���X
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1 alpha
*/

#include "stdafx.h"
#include "PlotEngine.h"
#include "config.h"

PlotEngine::PlotEngine(void)
{
	m_nSeedIndex = 1;
}

bool PlotEngine::Setup(void)
{
	bool fResult = true;

	//	�v���b�^�o�[�W�����擾
	int nMajor = PLOT_MAJOR;
	int nMinor = PLOT_MINOR;
	if(GENMODE)
	{
	}
	else
	{
		char sPath[255] = {0};
		sprintf(sPath, "seed\\seed (%d).txt", m_nSeedIndex);
		FILE* fp;
		if((fp = fopen(sPath, "r")) != NULL)
		{
			char buff[255] = {0};
			fscanf(fp, "%s", buff);	//	Header
			fscanf(fp, "%d", &nMajor);	//	Major
			fscanf(fp, "%d", &nMinor);	//	Minor
			fclose(fp);
		}
	}

	//	�v���b�^�擾
	m_plotter = PlotterBase::GetNewPlotter(nMajor, nMinor);

	//	�v���b�^�A���S���Y������
	if(m_plotter != NULL)
	{
		if(GENMODE)
		{
			m_plotter->ConstructAlgo(NULL);
		}
		else
		{
			fResult = m_plotter->ReadAlgo(NULL, m_nSeedIndex);
			m_nSeedIndex++;
		}
	}

	return fResult;
}

void PlotEngine::Save(const char* strFileName)
{
	m_plotter->SaveAlgo(strFileName);
}

double PlotEngine::Execute(LogicParam* pParam)
{
	return m_plotter->Operate(pParam);
}

void PlotEngine::PostExecute(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame)
{
	m_plotter->PostOperate(pParam1, pdX, pParam2, pdY, pParam3, pdZ, nFrame);
}

int PlotEngine::GetSeedIndex(void)
{
	return m_nSeedIndex;
}