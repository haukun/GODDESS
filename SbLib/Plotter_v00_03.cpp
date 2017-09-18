/**
	@file		Plotter_v00_03.cpp
	@brief		プロッタ v00.03
	@author		Hau-kun
	@date		2014/10/12
	@version	1.0
*/

#include "stdafx.h"
#include "MathUtil.h"
#include "Plotter_v00_03.h"

double Plotter_v00_03::Operate(LogicParam* pParam)
{
	//	座標取得
	CalculateInfo_v00_03 calInfo;
	calInfo.vec.dx = pParam->vec.dx;
	calInfo.vec.dy = pParam->vec.dy;
	calInfo.vec.dz = pParam->vec.dz;
	calInfo.add.dx = m_param.P;
	calInfo.add.dy = m_param.Q;
	calInfo.add.dz = m_param.R;

	double dResult = 0;

	char* pArg = NULL;

	//	アドレス取得（char[1024]とchar*が型が合わないので）
	char* pDest = NULL;
	char** pDestAdd = NULL;

	switch(pParam->nDim)
	{
	case 1:
		pDest = (char*)m_param.strArg1;
		pDestAdd = (char**)&pDest;
		break;
	case 2:
		pDest = (char*)m_param.strArg2;
		pDestAdd = (char**)&pDest;
		break;
	case 3:
		pDest = (char*)m_param.strArg3;
		pDestAdd = (char**)&pDest;
		break;
	}

	dResult = Calculate(pDestAdd, &calInfo);

	return dResult;

}
void Plotter_v00_03::PostOperate(LogicParam* pParam1, double* pdX, LogicParam* pParam2, double* pdY, LogicParam* pParam3, double* pdZ, int nFrame)
{
	double rad = atan2(*pdY, *pdX);
	double len = sqrt((*pdX * *pdX) + (*pdY * *pdY));

	rad += (1 * 3.14159265 * (m_param.P));
	len *= m_param.Q;

	*pdX = cos(rad) * len;
	*pdY = sin(rad) * len;
	*pdZ += (m_param.R * 0.001);

}

double Plotter_v00_03::Calculate(char** ppAlgo, void* pInfo)
{
	CalculateInfo_v00_03 info = *(CalculateInfo_v00_03*)pInfo;

	double d = 0;
	double d2 = 0;

	char* pAlgo = (char*)*ppAlgo;
	
	if(!strncmp(pAlgo, "ADD", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d2 = Calculate(ppAlgo, pInfo);
		d += d2;
		return d;
	}
	else if(!strncmp(pAlgo, "SUB", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d2 = Calculate(ppAlgo, pInfo);
		d -= d2;
		return d;
	}
	else if(!strncmp(pAlgo, "MUL", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d2 = Calculate(ppAlgo, pInfo);
		d *= d2;
		return d;
	}
	else if(!strncmp(pAlgo, "DIV", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d2 = Calculate(ppAlgo, pInfo);
		if(d2 != 0)
		{
			d /= d2;
		}
		return d;
	}
	else if(!strncmp(pAlgo, "SIN", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d = sin(d);
		return d;
	}
	else if(!strncmp(pAlgo, "COS", 3))
	{
		*ppAlgo += 3;
		d = Calculate(ppAlgo, pInfo);
		d = cos(d);
		return d;
	}
	else if(!strncmp(pAlgo, "PAA", 3))
	{
		*ppAlgo += 3;
		d = m_param.A;
		return d;
	}
	else if(!strncmp(pAlgo, "PAB", 3))
	{
		*ppAlgo += 3;
		d = m_param.B;
		return d;
	}
	else if(!strncmp(pAlgo, "PAC", 3))
	{
		*ppAlgo += 3;
		d = m_param.C;
		return d;
	}
	else if(!strncmp(pAlgo, "PAD", 3))
	{
		*ppAlgo += 3;
		d = m_param.D;
		return d;
	}
	else if(!strncmp(pAlgo, "POX", 3))
	{
		*ppAlgo += 3;
		d = info.vec.dx;
		return d;
	}
	else if(!strncmp(pAlgo, "POY", 3))
	{
		*ppAlgo += 3;
		d = info.vec.dy;
		return d;
	}
	else if(!strncmp(pAlgo, "POZ", 3))
	{
		*ppAlgo += 3;
		d = info.vec.dz;
		return d;
	}
	else if(!strncmp(pAlgo, "POP", 3))
	{
		*ppAlgo += 3;
		d = info.add.dx;
		return d;
	}
	else if(!strncmp(pAlgo, "POQ", 3))
	{
		*ppAlgo += 3;
		d = info.add.dy;
		return d;
	}
	else if(!strncmp(pAlgo, "POR", 3))
	{
		*ppAlgo += 3;
		d = info.add.dz;
		return d;
	}
	else if(pAlgo[1] ==  '.')
	{
		d = (pAlgo[0] - '0') + (pAlgo[2] - '0') * 0.1;
		pAlgo += 3;
		return d;
	}

	return d;
}

char* Plotter_v00_03::ConstructAlgo(void* AlgoInfo)
{
	m_param.A = (rand() / (double)RAND_MAX) * 40 - 20;
	m_param.B = (rand() / (double)RAND_MAX) * 40 - 20;
	m_param.C = (rand() / (double)RAND_MAX) * 40 - 20;
	m_param.D = (rand() / (double)RAND_MAX) * 40 - 20;
	m_param.P = (rand() / (double)RAND_MAX) * 100 - 50;
	m_param.Q = (rand() / (double)RAND_MAX) * 4 - 2;
	m_param.R = (rand() / (double)RAND_MAX) * 100 - 50;



	ExpInfo_v00_03 info1;
	info1.nDim = 1;
	SetExp(m_param.strArg1, &info1);

	ExpInfo_v00_03 info2;
	info2.nDim = 2;
	SetExp(m_param.strArg2, &info2);

	ExpInfo_v00_03 info3;
	info3.nDim = 1;
	SetExp(m_param.strArg3, &info3);

	return 0;
}

bool Plotter_v00_03::ReadAlgo(void* AlgoInfo, int nSeedIndex)
{
	bool fFind = false;

	char sPath[255] = {0};
	sprintf(sPath, "seed\\seed (%d).txt", nSeedIndex++);
	FILE* fp;
	if((fp = fopen(sPath, "r")) != NULL)
	{
		char buff[255] = {0};
		fscanf(fp, "%s", buff);	//	Header
		fscanf(fp, "%s", buff);	//	Major
		fscanf(fp, "%s", buff);	//	Minor

		double buffp;
		fscanf(fp, "%lf", &buffp);
		m_param.A = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.B = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.C = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.D = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.P = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.Q = buffp;

		fscanf(fp, "%lf", &buffp);
		m_param.R = buffp;

		fscanf(fp, "%s", buff);
		strcpy(m_param.strArg1, buff);

		fscanf(fp, "%s", buff);
		strcpy(m_param.strArg2, buff);

		fscanf(fp, "%s", buff);
		strcpy(m_param.strArg3, buff);
		fclose(fp);

		fFind = true;
	}

	return fFind;
}

char* Plotter_v00_03::SetExp(char* pDest, void* pInfo)
{
	ExpInfo_v00_03 info = *(ExpInfo_v00_03*)pInfo;
	memset(pDest, 0x00, 1024);

	if(info.nDim <= 2)
	{
		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "ADD");
		}
		else
		{
			strcat(pDest, "SUB");
		}
		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "ADD");
		}
		else
		{
			strcat(pDest, "SUB");
		}

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "SIN");
		}
		else
		{
			strcat(pDest, "COS");
		}

		if(MathUtil::Rand() < 0.5)
		{
			strcat(pDest, "MUL");
		}
		else
		{
			strcat(pDest, "DIV");
		}
		SetParam(pDest, NULL);

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "POX");
		}
		else
		{
			strcat(pDest, "POY");
		}

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "SIN");
		}
		else
		{
			strcat(pDest, "COS");
		}

		if(MathUtil::Rand() < 0.5)
		{
			strcat(pDest, "MUL");
		}
		else
		{
			strcat(pDest, "DIV");
		}
		SetParam(pDest, NULL);

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "POX");
		}
		else
		{
			strcat(pDest, "POY");
		}


		if(MathUtil::Rand() < 0.5)
		{
			strcat(pDest, "MUL");
		}
		else
		{
			strcat(pDest, "DIV");
		}
		strcat(pDest, "MUL");
		SetParam(pDest, NULL);
		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "COS");
		}
		else
		{
			strcat(pDest, "SIN");
		}
		strcat(pDest, "MUL");
		SetParam(pDest, NULL);
		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "POX");
		}
		else
		{
			strcat(pDest, "POY");
		}

			strcat(pDest, "PAQ");

	}
	else
	{
		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "ADD");
		}
		else
		{
			strcat(pDest, "SUB");
		}

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "SIN");
		}
		else
		{
			strcat(pDest, "COS");
		}

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "MUL");
		}
		else
		{
			strcat(pDest, "DIV");
		}
		SetParam(pDest, NULL);

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "POX");
		}
		else
		{
			strcat(pDest, "POY");
		}

				if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "SIN");
		}
		else
		{
			strcat(pDest, "COS");
		}

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "MUL");
		}
		else
		{
			strcat(pDest, "DIV");
		}
		SetParam(pDest, NULL);

		if(MathUtil::Rand() > 0.5)
		{
			strcat(pDest, "POX");
		}
		else
		{
			strcat(pDest, "POY");
		}


	}

	return pDest;
}


char* Plotter_v00_03::SetParam(char* pDest, void* pInfo)
{
	int n = (int)(MathUtil::Rand() * 11);

	switch(n)
	{
	case 0:
		strcat(pDest, "PAA");
		pDest += 3;
		break;
	case 1:
		strcat(pDest, "PAB");
		pDest += 3;
		break;
	case 2:
		strcat(pDest, "PAC");
		pDest += 3;
		break;
	case 3:
		strcat(pDest, "PAD");
		pDest += 3;
		break;
	case 4:
		strcat(pDest, "POX");
		pDest += 3;
		break;
	case 5:
		strcat(pDest, "POY");
		pDest += 3;
		break;
	case 6:
		strcat(pDest, "POZ");
		pDest += 3;
		break;
	case 7:
		char pTemp[10];
		sprintf(pTemp, "%1.1lf", MathUtil::Rand());
		strcat(pDest, pTemp);
		pDest += 3;
		break;
	case 8:
		strcat(pDest, "POP");
		pDest += 3;
		break;
	case 9:
		strcat(pDest, "POQ");
		pDest += 3;
		break;
	case 10:
		strcat(pDest, "POR");
		pDest += 3;
		break;
	}

	return pDest;
}

char* Plotter_v00_03::SetArg(char* pDest, void* pInfo)
{
	ArgInfo_v00_03 info = *(ArgInfo_v00_03*)pInfo;
	int n = (int)(MathUtil::Rand() * 2 * info.dMulp);
	switch(n)
	{
	case 0:
		pDest = SetOp(pDest, NULL);
		break;
	case 1:
	case 2:
		pDest = SetParam(pDest, NULL);
		break;
	}

	return pDest;
}

char* Plotter_v00_03::SetOp(char* pDest, void* pInfo)
{
	ArgInfo_v00_03 info;

	int n = (int)(MathUtil::Rand() * 6);
	switch(n)
	{
	case 0:
		strcpy(pDest, "ADD");
		pDest += 3;
		break;
	case 1:
		strcpy(pDest, "SUB");
		pDest += 3;
		break;
	case 2:
		strcpy(pDest, "MUL");
		pDest += 3;
		break;
	case 3:
		strcpy(pDest, "DIV");
		pDest += 3;
		break;
	case 4:
		strcpy(pDest, "SIN");
		pDest += 3;
		info.dMulp = 1.5;
		pDest = SetArg(pDest, &info);
		break;
	case 5:
		strcpy(pDest, "COS");
		pDest += 3;
		info.dMulp = 1.5;
		pDest = SetArg(pDest, &info);
		break;
	}

	return pDest;
}

void Plotter_v00_03::SaveAlgo(const char* strFileName)
{
	FILE* fp;
	if((fp = fopen(strFileName, "w")) != NULL)
	{
		fprintf(fp, "COCGEN\n0\n2\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", m_param.A, m_param.B, m_param.C, m_param.D, m_param.P, m_param.Q, m_param.R);
		fprintf(fp, "%s\n%s\n%s\n", m_param.strArg1, m_param.strArg2, m_param.strArg3);
		fclose(fp);
	}

}
