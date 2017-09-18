/**
	@file		SbWindow.cpp
	@brief		�X�����ۃE�B���h�E�N���X�\�[�X
	@author		Hau-kun
	@date		2014/10/12
	@version	0.2
*/

#include "sbstdafx.h"
#include "SbWindow.h"

/**
	@fn			SbWindow::Create(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
	@brief		�E�B���h�E�̍쐬
	@param[in]	HINSTANCE	hInst			(Windows����)
	@param[in]	HINSTANCE	hPrevInst		(Windows����)
	@param[in]	LPSTR		szStr			(Windows����)
	@param[in]	INT			iCmdShow		(Windows����)
	@return		HREULT S_OK
	@date		2010/05/08
	@version	0.1	alpha
*/
SbWindow::SbWindow(RECT& rect, HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
	HRESULT hr = NULL;

	/*--------------------------------------------------
	�ϐ��̏�����
	--------------------------------------------------*/
	m_hWnd				= NULL;
	m_szClassName		= DEFAULT_CLASS_NAME;
	memcpy(&m_rectWindow, &rect ,sizeof(RECT));
	m_fWindowCreated	= false;
	
    m_pSbLogManager = new SbLogManager("_SbWindowLog.txt");


	/*--------------------------------------------------
	 *	�E�B���h�E�̏�����
	 --------------------------------------------------*/
	WNDCLASSEX wndclass;
	wndclass.cbSize			= sizeof(wndclass);			//	�\���̂̑傫��
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;	//	�㉺�ɃT�C�Y���ύX���ꂽ��ĕ`�悷��
	wndclass.lpfnWndProc	= WndProc;					//	�E�B���h�E�v���V�[�W���ւ̎Q��
	wndclass.cbClsExtra		= 0;						//	�N���X�̒ǉ��T�C�Y
	wndclass.cbWndExtra		= 0;						//	�E�B���h�E�̒ǉ��T�C�Y
	wndclass.hInstance		= hInst;					//	�v���O�����̃n���h��
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	//	�A�C�R��
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);		//	�J�[�\��
	wndclass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);	//	�u���V
	wndclass.lpszMenuName	= NULL;						//	���j���[��
	wndclass.lpszClassName	= m_szClassName;			//	�N���X��	
	wndclass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);	//	���A�C�R��

	/*--------------------------------------------------
	 *	�E�B���h�E�X�^�C���̐ݒ�
	 --------------------------------------------------*/
	DWORD dwStyle = NULL;
	dwStyle = WS_OVERLAPPEDWINDOW& ~WS_THICKFRAME;

	/*--------------------------------------------------
	 *	�E�B���h�E�̍쐬
	 --------------------------------------------------*/
    RECT rectWindow;
    SetRect(&rectWindow, 0, 0, m_rectWindow.right, m_rectWindow.bottom);
    AdjustWindowRect(&rectWindow, dwStyle, false);

	int nWidth = (rectWindow.right - rectWindow.left) * (1024.0 / (rectWindow.right - rectWindow.left)) ;
	int nHeight = (rectWindow.bottom - rectWindow.top) * (768.0 / (rectWindow.bottom - rectWindow.top));

	RegisterClassEx(&wndclass);
	m_hWnd = CreateWindow(	m_szClassName,			//	�N���X��
							m_szClassName,			//	�E�B���h�E��
							dwStyle,				//	�E�B���h�E�X�^�C��
							m_rectWindow.left,	m_rectWindow.top,	//	�E�B���h�E�\���ʒu
							nWidth,					//	�E�B���h�E�̉���
							nHeight,				  //	�E�B���h�E�̏c��
							NULL,					//	�e�E�B���h�E�n���h��
							NULL,					//	���j���[�̃n���h��
							hInst,					//	�v���O�����̃n���h��
							NULL					//	�p�����[�^
							);			

	m_fWindowCreated = true;
}

/**
	@fn			SbWindowManager::~SbWindowManager
	@brief		�f�X�g���N�^
	@date		2010/05/08
	@version	0.1 alpha
*/
SbWindow::~SbWindow()
{
}

/**
	@fn			HRESULT SbWindowManager::Show(int nCmdShow)
	@brief		�E�B���h�E��\������
	@param		int nCmdShow		�\�����@
	@return		HRESULT S_OK
	@note		
	@date		2010/05/09
	@version	0,1 alpha
*/
HRESULT SbWindow::Show(int nCmdShow)
{
	HRESULT hr = S_OK;

	if(m_fWindowCreated)
	{
		ShowWindow(m_hWnd, nCmdShow);
		UpdateWindow(m_hWnd);
	}
	else
	{
		hr = E_HANDLE;
	}

	return hr;
}

/**
	@fn			HRESULT SbWindowManager::SetSize(const int nWidth, constint nHeight)
	@brief		�E�B���h�E�̑傫����ύX����
	@param[in]	int	nWidth	����
	@param[in]	int	nHeight	�c��
	@return		S_OK
	@note		
	@date		2010/09/20
	@version	0.0 GoddessProject
*/
HRESULT SbWindow::SetSize(const int nWidth, const int nHeight)
{
	HRESULT hr = S_OK;

	RECT	rectWindow;
	GetWindowRect(m_hWnd, &rectWindow);

	int	nLeft = rectWindow.left;
	int	nTop = rectWindow.top;

	RECT	rectNewTemp;
	ZeroMemory(&rectNewTemp, sizeof(RECT));
	
	rectNewTemp.right = nWidth;
	rectNewTemp.bottom = nHeight;
	AdjustWindowRect(&rectNewTemp, WS_OVERLAPPEDWINDOW, false);

	RECT	rectNew;
	ZeroMemory(&rectNew, sizeof(RECT));
	SetRect(&rectNew, nLeft, nTop, rectNewTemp.right - rectNewTemp.left, rectNewTemp.bottom - rectNewTemp.top);

	SetWindowPos(m_hWnd, NULL, rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, NULL);

	return hr;
}

/**
	@fn			HRESULT SbWindowManager::MoveWindowCenter(void)
	@brief		�E�B���h�E�𒆉��Ɉړ�����
	@return		S_OK
	@note
	@date		2010/09/20
	@version	0.0 GoddessProject����
*/
HRESULT SbWindow::MoveWindowCenter(void)
{
	HRESULT	hr = S_OK;

	RECT	rectWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, NULL, &rectWorkArea, NULL);

	RECT	rectWindow;
	GetWindowRect(m_hWnd, &rectWindow);

	RECT	rectNew;
	ZeroMemory(&rectNew, sizeof(RECT));

	rectNew.left = ((rectWorkArea.right - rectWorkArea.left) - (rectWindow.right - rectWindow.left)) / 2;
	rectNew.top = ((rectWorkArea.bottom - rectWorkArea.top) - (rectWindow.bottom - rectWindow.top)) / 2;

	rectNew.right = rectWindow.right - rectWindow.left;
	rectNew.bottom = rectWindow.bottom - rectWindow.top;


	SetWindowPos(m_hWnd, NULL, rectNew.left, rectNew.top, rectNew.right, rectNew.bottom, NULL);

	return hr;
}

HRESULT SbWindow::SetTitle(LPSTR pstr)
{
	HRESULT hr = S_OK;
	SetWindowText(m_hWnd, pstr);
	return hr;
}




/**
	@fn			LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg WPARAM wParam, LPARAM lParam)
	@brief		�E�B���h�E�v���V�[�W��
	@param[in]	HWND	hWnd	�E�B���h�E�̃n���h��	(Windows����)
	@param[in]	UINT	iMsg	���b�Z�[�W				(Windows����)
	@param[in]	WPARAM	wparam	�p�����[�^				(Windows����)
	@param[in]	LPARAM	lparam	�p�����[�^				(Windows����)
	@result		HRESULT DefWindowProc�̖߂�l
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_DESTROY:			//	�E�B���h�E�j��
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:			//	�L�[�C�x���g
		switch((CHAR)wParam)
		{
		case VK_ESCAPE:			//	�G�X�P�[�v
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}



/**
	@fn			SbWindowManager::GetWindowHandle(void)
	@brief		�E�B���h�E�n���h���𓾂�
	@return		�E�B���h�E�n���h��
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HWND	SbWindow::GetWindowHandle(void)
{
	return m_hWnd;
}