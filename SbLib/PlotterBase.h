/**
	@file		PlotterBase.h
	@brief		プロッタベース
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#ifndef		_PLOTTER_BASE_H_
#define		_PLOTTER_BASE_H_

#include "stdafx.h"
#include "UserHeader.h"

typedef struct Vector3
{
	double dx;
	double dy;
	double dz;
}Vector3;

//	ロジックパラメータ
typedef struct LogicParam
{
	LogicParam(int dim, double x, double y, double z)
	{
		nDim = dim;
		vec.dx = x;
		vec.dy = y;
		vec.dz = z;
	}
	int nDim;
	Vector3 vec;
}LogicParam;

typedef struct AlgoInfo
{
}AlogInfo;

typedef struct ExpInfo
{
}ExpInfo;

typedef struct ParamInfo
{
}ParamInfo;

typedef struct ArgInfo
{
}ArgInfo;

typedef struct OpInfo
{
}OpInfo;

class PlotterBase
{
public:
	static PlotterBase* GetNewPlotter(int nMajor, int Minor);
	virtual char* ConstructAlgo(void* AlgoInfo) = 0;
	virtual bool ReadAlgo(void* AlgoInfo, int nSeedIndex) = 0;
	virtual void SaveAlgo(const char* strFileName) = 0;
	virtual double Operate(LogicParam* pParam) = 0;
	virtual void PostOperate(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame);

private:
	virtual char* SetExp(char* pDest, void* ExpInfo) = 0;
	virtual char* SetParam(char* pDest, void* ParamInfo) = 0;
	virtual char* SetArg(char* pDest, void* pArgInfo) = 0;
	virtual char* SetOp(char* pDest, void* pOpInfo) = 0;
	virtual double Calculate(char** ppAlgo, void* pInfo) = 0;
	virtual double Calculate(char** ppAlgo, void* pInfo, int nDim);
};

#endif