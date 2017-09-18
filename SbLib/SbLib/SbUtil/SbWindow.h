/**
	@file		SbWindowManager.h
	@brief		森羅万象ウィンドウクラスヘッダー
	@author		Hau-kun
	@date		2010/05/08
	@version	0.1
*/

#ifndef _SB_WINDOW_H_
#define _SB_WINDOW_H_

#include "..\sbstdafx.h"
#include "SbLogManager.h"

#define DEFAULT_CLASS_NAME "SbLib Class Name"

/*--------------------------------------------------
 *	プロトタイプ宣言
 --------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
	@class		SbWindow
	@brief		ウィンドウクラス
	@note
	@date		2014/10/12
	@version	0.2	alpha
*/class SbWindow
{
public:
	SbWindow(RECT& rect, HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdSHow);
	~SbWindow();

	HRESULT Show(int nCmdShow = SW_SHOW);

	HRESULT MoveWindowCenter(void);
	HRESULT SetSize(int nWidth, int nHeight);
	HRESULT SetTitle(LPSTR szStr);

	HWND	GetWindowHandle(void);

private:
	HWND		m_hWnd;				//	ウィンドウハンドル
	char*		m_szClassName;		//	クラス名
	RECT		m_rectWindow;		//	ウィンドウの大きさ

	boolean		m_fWindowCreated;	//	ウィンドウが作成されているかどうかのフラグ

	void (* m_pFunctionSetup)(void);	//	準備関数へのポインタ
	void (* m_pFunctionExecute)(void);	//	実行関数へのポインタ
	

	LPSBLOGMANAGER			m_pSbLogManager;	//	森羅万象ログマネージャー
};

#endif