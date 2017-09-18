/**
	@file		GoddessWindow.h
	@brief		GODDESSウィンドウヘッダー
	@author		Hau-kun
	@date		2014/10/12
	@version	0.1
*/

#ifndef		_GODDESS_WINDOW_H_
#define		_GODDESS_WINDOW_H_

#include "stdafx.h"
#include "SbLib\SbHeader.h"
#include "PlotEngine.h"

enum DRAW_STATE
{
	DRAW_STATE_SETUP = 0,
	DRAW_STATE_DRAW,
	DRAW_STATE_SAVE,
	DRAW_STATE_FINISH,
};

class Goddess : public SbCore
{
public:
	Goddess(void);
	Goddess(SbWindow* pWnd);
	~Goddess(void);
	HRESULT Setup(SbSetupInfo* pInfo);
	HRESULT Execute(SbExecuteInfo* pInfo);

	bool SetParam(void);
	void ConstructArg(char* pDest, int n);
	char* GetArg(char* pDest, double dB);
	char* GetParam(char* pDest);
	char* GetOp(char* pDest);

	void	Init(void);
	void	Plot(void);
	void	Save(void);

	void	CocSpreadBasic(void);

	double LogicExec(char* logic, double dx, double dy, double dz);
	double	LogicOp(LogicParam& pa);



protected:
	SbTex*	m_pDotTex;

private:
	double m_dX, m_dY, m_dZ;	//	カオス打点の座標
	DRAW_STATE m_nState;

	PlotEngine m_plot;

};

#endif	//	_GODDESS_WINDOW_H_