/**
	@file		Plotter_v00_02.h
	@brief		プロッタバージョン00_02
	@author		Hau-kun
	@date		2016/06/23
	@version	0.1
*/

#ifndef		_PLOTTER_V00_02_H_
#define		_PLOTTER_V00_02_H_

#include "stdafx.h"
#include "PlotterBase.h"

//	ジェネレートパラメータ
typedef struct GenParam_v00_02
{
	double A;
	double B;
	double C;
	double D;

	char	strArg1[1024];
	char	strArg2[1024];
	char	strArg3[1024];

	double P;
	double Q;
	double R;
}GenParam_v00_02;

typedef struct ExpInfo_v00_02
{
	int nDim;	//	次元(1=x 2=y, 3=z)
}ExpInfo_v00_02;

typedef struct ParamInfo_v00_02
{
}ParamInfo_v00_02;

typedef struct ArgInfo_v00_02
{
	double dMulp;
}ArgInfo_v00_02;

typedef struct OpInfo_v00_02
{
}OpInfo_v00_02;

typedef struct OperateInfo_v00_02
{
	int nDim;	//	次元(1=x 2=y, 3=z)
	Vector3 vec;
}OperateInfo_v00_02;

typedef struct CalculateInfo_v00_02
{
	Vector3 vec;
	Vector3 add;
}CalculateInfo_v00_02;

class Plotter_v00_02 : public PlotterBase
{
public:
	virtual char* ConstructAlgo(void* AlgoInfo);
	virtual bool ReadAlgo(void* AlgoInfo, int nSeedIndex);
	virtual void SaveAlgo(const char* strFileName);
	virtual double Operate(LogicParam* pParam);
	virtual void PostOperate(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame);


private:
	GenParam_v00_02 m_param;

	virtual char* SetExp(char* pDest, void* pInfo);
	virtual char* SetParam(char* pDest, void* pInfo);
	virtual char* SetArg(char* pDest, void* pInfo);
	virtual	char* SetOp(char* pDest, void* pInfo);

	virtual double Calculate(char** pAlgo, void* pInfo);

};

#endif	//	_PLOTTER_V00_02_H_