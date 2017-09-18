/**
	@file		SbWindowManager.h
	@brief		�X�����ۃE�B���h�E�N���X�w�b�_�[
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
 *	�v���g�^�C�v�錾
 --------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/**
	@class		SbWindow
	@brief		�E�B���h�E�N���X
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
	HWND		m_hWnd;				//	�E�B���h�E�n���h��
	char*		m_szClassName;		//	�N���X��
	RECT		m_rectWindow;		//	�E�B���h�E�̑傫��

	boolean		m_fWindowCreated;	//	�E�B���h�E���쐬����Ă��邩�ǂ����̃t���O

	void (* m_pFunctionSetup)(void);	//	�����֐��ւ̃|�C���^
	void (* m_pFunctionExecute)(void);	//	���s�֐��ւ̃|�C���^
	

	LPSBLOGMANAGER			m_pSbLogManager;	//	�X�����ۃ��O�}�l�[�W���[
};

#endif