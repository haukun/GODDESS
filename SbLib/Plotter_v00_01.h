/**
	@file		Plotter_v00_01.h
	@brief		プロッタバージョン00_01
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#ifndef		_PLOTTER_V00_01_H_
#define		_PLOTTER_V00_01_H_

#include "stdafx.h"
#include "PlotterBase.h"

//	ジェネレートパラメータ
typedef struct GenParam_v00_01
{
	double A;
	double B;
	double C;
	double D;

	char	strArg1[1024];
	char	strArg2[1024];
	char	strArg3[1024];
}GenParam;

typedef struct ExpInfo_v00_01
{
	int nDim;	//	次元(1=x 2=y, 3=z)
}ExpInfo_v00_01;

typedef struct ParamInfo_v00_01
{
}ParamInfo_v00_01;

typedef struct ArgInfo_v00_01
{
	double dMulp;
}ArgInfo_v00_01;

typedef struct OpInfo_v00_01
{
}OpInfo_v00_01;

typedef struct OperateInfo_v00_01
{
	int nDim;	//	次元(1=x 2=y, 3=z)
	Vector3 vec;
}OperateInfo_v00_01;

typedef struct CalculateInfo_v00_01
{
	Vector3 vec;
}CalculateInfo_v00_01;

class Plotter_v00_01 : public PlotterBase
{
public:
	virtual char* ConstructAlgo(void* AlgoInfo);
	virtual bool ReadAlgo(void* AlgoInfo, int nSeedIndex);
	virtual void SaveAlgo(const char* strFileName);
	virtual double Operate(LogicParam* pParam);


private:
	GenParam_v00_01 m_param;

	virtual char* SetExp(char* pDest, void* pInfo);
	virtual char* SetParam(char* pDest, void* pInfo);
	virtual char* SetArg(char* pDest, void* pInfo);
	virtual	char* SetOp(char* pDest, void* pInfo);

	virtual double Calculate(char** pAlgo, void* pInfo);

};

#endif	//	_PLOTTER_V00_01_H_