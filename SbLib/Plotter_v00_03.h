/**
	@file		Plotter_v00_03.h
	@brief		プロッタバージョン00_03
	@author		Hau-kun
	@date		2017/09/19
	@version	0.1
*/

#ifndef		_PLOTTER_V00_03_H_
#define		_PLOTTER_V00_03_H_

#include "stdafx.h"
#include "PlotterBase.h"

//	ジェネレートパラメータ
typedef struct GenParam_v00_03
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
	int nDiv;	//	形状回転数
	int nLop;	//	ループ数
	int nRot;	//	回転数

}GenParam_v00_03;

typedef struct ExpInfo_v00_03
{
	int nDim;	//	次元(1=x 2=y, 3=z)
}ExpInfo_v00_03;

typedef struct ParamInfo_v00_03
{
}ParamInfo_v00_03;

typedef struct ArgInfo_v00_03
{
	double dMulp;
}ArgInfo_v00_03;

typedef struct OpInfo_v00_03
{
}OpInfo_v00_03;

typedef struct OperateInfo_v00_03
{
	int nDim;	//	次元(1=x 2=y, 3=z)
	Vector3 vec;
}OperateInfo_v00_03;

typedef struct CalculateInfo_v00_03
{
	Vector3 vec;
	Vector3 add;
}CalculateInfo_v00_03;

class Plotter_v00_03 : public PlotterBase
{
public:
	virtual char* ConstructAlgo(void* AlgoInfo);
	virtual bool ReadAlgo(void* AlgoInfo, int nSeedIndex);
	virtual void SaveAlgo(const char* strFileName);
	virtual double Operate(LogicParam* pParam);
	virtual void PostOperate(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame);

	int GetDiv(void);
	int GetLop(void);
	int GetRot(void);

private:
	GenParam_v00_03 m_param;

	virtual char* SetExp(char* pDest, void* pInfo);
	virtual char* SetParam(char* pDest, void* pInfo);
	virtual char* SetArg(char* pDest, void* pInfo);
	virtual	char* SetOp(char* pDest, void* pInfo);

	virtual double Calculate(char** pAlgo, void* pInfo);

};

#endif	//	_PLOTTER_V00_03_H_