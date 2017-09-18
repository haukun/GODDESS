/**
	@file		SbCore.cpp
	@brief		�X�����ۃR�A�N���X�\�[�X
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "sbstdafx.h"
#include "SbCore.h"

SbCore::SbCore(void)
{
}

SbCore::SbCore(SbWindow* pWnd)
{
	Create(pWnd);
}


/**
	@fn			SbCore::SbCore()
	@brief		�R���X�g���N�^
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
HRESULT SbCore::Create(SbWindow* pWnd, int nWidth, int nHeight)
{
	if(pWnd != NULL)
	{
		m_d3d9Object = NULL;
		m_d3d9Device = NULL;	

		/*--------------------------------------------------
		 *	�v���[���e�[�V�����p�����[�^�̃f�t�H���g�l�̐ݒ�
		 --------------------------------------------------*/
		ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));
		m_d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;
		m_d3dpp.BackBufferCount				= 1;
		m_d3dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
		m_d3dpp.Windowed					= TRUE;
		m_d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
		m_d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;
		m_d3dpp.BackBufferHeight = nHeight;
		m_d3dpp.BackBufferWidth = nWidth;

		/*--------------------------------------------------
		 *	���̑��K�v�Ȃ��̂̐ݒ�
		 --------------------------------------------------*/
		m_pSbLogManager = new SbLogManager("_SbDefaultLog.txt");
		m_timeFpsBase	= 0;
		m_nFpsCurrent	= 0;
		m_nFpsCount		= 0;

		m_pWnd = pWnd;

		this->CreateDx9Object();
		this->CreateDx9Device(m_pWnd->GetWindowHandle());
		this->CreateDxSprite();
	}

	return S_OK;
}

/**
	@fn			SbCore::~SbCore()
	@brief		�f�X�g���N�^
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
SbCore::~SbCore()
{
	delete m_pSbLogManager;

	SAFE_RELEASE(m_d3dxSprite);
	SAFE_RELEASE(m_d3d9Device);
	SAFE_RELEASE(m_d3d9Object);
}


/**
	@fn			SbCore::CreateDx9Object(void)
	@brief		�X�����ۃI�u�W�F�N�g�쐬
	@return		HRESULT	S_OK:����	E_FAIL:���s
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
HRESULT SbCore::CreateDx9Object(void)
{
	HRESULT hr = S_OK;

	m_d3d9Object = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_d3d9Object == NULL)
	{
		hr = E_FAIL;
	}

	return hr;
}

/**
	@fn			SbCore::CreateDx9Device(HWND hWnd)
	@brief		�X�����ۃf�o�C�X�쐬
	@param		HWND	hWnd	�ΏۃE�B���h�E�n���h��
	@return		HRESULT	S_OK:����	E_HANDLE:D3D9�I�u�W�F�N�g����������Ă��܂���B
	@note
	@date		2010/05/09
	@versin		0.1	alpha
*/
HRESULT SbCore::CreateDx9Device(HWND hWnd)
{
	HRESULT hr = S_OK;

	if(m_d3d9Object == NULL)
	{
		hr = E_HANDLE;
		return hr;
	}

	//	HAL���[�h�E�n�[�h�E�F�A
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	//	HAL���[�h�E�\�t�g�E�F�A
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	//	REF���[�h�E�n�[�h�E�F�A
	hr = m_d3d9Object->CreateDevice(	D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
										D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dpp, &m_d3d9Device);

	if(SUCCEEDED(hr))
	{
		return S_OK;
	}

	return E_FAIL;
}

/**
	@fn			SbCore::CreateDxSprite(void)
	@brief		�X�v���C�g�C���^�[�t�F�[�X���쐬����
	@return		HRESULT	D3DXCreateSprite()�̖߂�l
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
HRESULT	SbCore::CreateDxSprite(void)
{
	HRESULT hr = S_OK;

	hr = D3DXCreateSprite(m_d3d9Device, &m_d3dxSprite);

	return hr;
}

/**
	@fn			SbCore::Action(SbActionInfo* pInfo)
	@brief		�X�����ۃR�A�G���W�����N������
	@return		HRESULT	���s����
	@note
	@date		2014/10/12
	@version	0.1	alpha
*/
HRESULT SbCore::Action(SbActionInfo* pInfo)
{
	HRESULT hr = S_OK;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	m_pWnd->Show();

	Setup(NULL);

	/*--------------------------------------------------
	 *	���b�Z�[�W���[�v
	 --------------------------------------------------*/
	boolean fLoop = true;
	while(fLoop)
	{
		switch(msg.message)
		{
		default:
			if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//	���s�֐�
				Execute(NULL);
			}
			break;
		case WM_QUIT:
			fLoop = FALSE;
			break;
		case WM_DESTROY:
			fLoop = FALSE;
			break;
		}
	}

	return hr;
}

/**
	@fn			SbCore::Clear(const D3DCOLOR color)
	@brief		��ʑS�̂��N���A����
	@param[in]	D3DCOLOR color	�S�̂�h��Ԃ��F
	@return		S_OK
	@note
	@date		2010/05/09
	@version	0.1 alpha
*/
HRESULT SbCore::Clear(const D3DCOLOR color)
{
	m_d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
	return S_OK;
}

/**
	@fn			SbCore::Flip(void);
	@brief		�t���b�s���O���s��
	@return		S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::Flip(void)
{
	/*--------------------------------------------------
	 *	FPS�v��
	 --------------------------------------------------*/
	time_t	t;
	time(&t);
	m_nFpsCount++;
	if (t != m_timeFpsBase) 
	{
		m_timeFpsBase = t;
		m_nFpsCurrent = m_nFpsCount;
		m_nFpsCount = 0;
	}


	/*--------------------------------------------------
	 *	�t���b�v����
	 --------------------------------------------------*/
	m_d3d9Device->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}


/**
	@fn			SbCore::GetDevice(void)
	@brief		DirectX9�f�o�C�X�𓾂�
	@return		LPDIRECT3DDEVICE9 DirectX9�f�o�C�X
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
LPDIRECT3DDEVICE9 SbCore::GetDevice(void)
{
	return m_d3d9Device;
}

/**
	@fn			SbCore::GetSprite(void)
	@brief		DirectX9�X�v���C�g�𓾂�
	@return		LPD3DXSPRITE DirectX9�X�v���C�g
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
LPD3DXSPRITE SbCore::GetSprite(void)
{
	return m_d3dxSprite;
}



/**
	@fn			SbCore::BeginAct(void)
	@brief		�`����J�n����
	@return		HRESULT S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::BeginAct(void)
{
	m_d3d9Device->BeginScene();

	if (m_d3dxSprite != NULL) 
	{
		m_d3dxSprite->Begin(NULL);
	}
	return S_OK;
}

/**
	@fn			SbCore::EndAct(void)
	@brief		�`����I������
	@return		HRESULT S_OK
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
HRESULT SbCore::EndAct(void)
{
	if (m_d3dxSprite != NULL) 
	{
		m_d3dxSprite->End();
	}
	m_d3d9Device->EndScene();
	return S_OK;
}

/**
	@fn			SbCore::GetFps(void)
	@brief		���݂�FPS���擾����
	@return		UINT	FPS�̒l
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
UINT	SbCore::GetFps()
{
	return	m_nFpsCurrent;
}

/**
    @fn         SbCore::SetRednerAlphaBlend
    @brief      �A���t�@�u�����h��ݒ肷��
    @param[in]  bool    bSwitch �A���t�@�u�����h���g�p���邩�ǂ����̃t���O
    @return     HRESULT SetREnderState()�̌���
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlend(const bool bSwitch)
{
    return m_d3d9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, bSwitch);
}

/**
    @fn         SbCore::SetRednerAlphaBlendMode
    @brief      �A���t�@�u�����h�̃��[�h���w�肷��
    @param[in]  DWORD dwBlendOperation  �A���t�@�u�����h���[�h
    @param[in]  DWORD dwSrcBlend        �`�挳�̃s�N�Z���ɓK�p����u�����h�W��
    @param[in]  DWORD dwDstBlend        �`���̃s�N�Z���ɓK�p����u�����h�W��
    @return     HRESULT S_OK ���� E_FAIL ���Z�����̐ݒ莞�ɃG���[����������
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendMode(const DWORD dwBlendOperation, const DWORD dwSrcBlend, const DWORD dwDstBlend)
{
    HRESULT hResult = S_OK;
    HRESULT hResult1 = m_d3d9Device->SetRenderState(D3DRS_BLENDOP, dwBlendOperation);
    HRESULT hResult2 = m_d3d9Device->SetRenderState(D3DRS_SRCBLEND , dwSrcBlend);
    HRESULT hResult3 = m_d3d9Device->SetRenderState(D3DRS_DESTBLEND , dwDstBlend);
    if(FAILED(hResult1 | hResult2 | hResult3))
    {
        hResult = E_FAIL;
    }

    return hResult;
}

/**
    @fn         SbCore::SetRednerAlphaBlendModeAddComposition
    @brief      �A���t�@�u�����h�̃��[�h�����Z�������[�h�ɂ���B
    @param[in]  �Ȃ�
    @return     HRESULT S_OK ���� E_FAIL ���Z�����̐ݒ莞�ɃG���[����������
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendModeAddComposition(void)
{
    return SetRenderAlphaBlendMode(D3DBLENDOP_ADD, D3DBLEND_SRCALPHA, D3DBLEND_DESTALPHA);
}

/**
    @fn         SbCore::SetRednerAlphaBlendModeTransparent
    @brief      �A���t�@�u�����h�̃��[�h�𔼓������[�h�ɂ���B
    @param[in]  �Ȃ�
    @return     HRESULT S_OK ���� E_FAIL ���Z�����̐ݒ莞�ɃG���[����������
    @note
    @date       2010/09/05
    @version    0.1 alpha
*/
HRESULT SbCore::SetRenderAlphaBlendModeTransparent(void)
{
    return SetRenderAlphaBlendMode(D3DBLENDOP_ADD, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);
}

HRESULT SbCore::SaveCaptureBmp(char* strFilePath)
{
	LPDIRECT3DSURFACE9 pSurface = NULL;
	HRESULT hr = GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	HRESULT hr2;
	hr2 = D3DXSaveSurfaceToFile(strFilePath, D3DXIFF_BMP, pSurface, NULL, NULL);

	return hr2;
}

HRESULT SbCore::SaveCapturePng(char* strFilePath)
{
	LPDIRECT3DSURFACE9 pSurface = NULL;
	HRESULT hr = GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	HRESULT hr2;
	hr2 = D3DXSaveSurfaceToFile(strFilePath, D3DXIFF_PNG, pSurface, NULL, NULL);

	return hr2;
}


/*	HsvToRgb
 *		Hsv�̒l��RGB�ɕϊ�����B
 */
D3DCOLOR SbCore::HsvToRgb(const double dAlpha, const double dHue, const double dSaturation, const double dValue)
{
	int nHue = (int)dHue;
	while(nHue >= 360)
	{
		nHue -= 360;
	}

	while(nHue < 0)
	{
		nHue += 360;
	}

	int nHi = nHue / 60 % 6;
	int nF =  nHue / 60 - nHi;
	double dP = dValue * (1 - dSaturation);
	double dQ = dValue * (1 - nF * dSaturation);
	double dT = dValue * (1 - ( 1 - nF) * dSaturation);

	double dR, dG, dB;

	switch(nHi)
	{
	case 0:
		dR = dValue;
		dG = dT;
		dB = dP;
		break;
	case 1:
		dR = dQ;
		dG = dValue;
		dB = dP;
		break;
	case 2:
		dR = dP;
		dG = dValue;
		dB = dT;
		break;
	case 3:
		dR = dP;
		dG = dQ;
		dB = dValue;
		break;
	case 4:
		dR = dT;
		dG = dP;
		dB = dValue;
		break;
	case 5:
		dR = dValue;
		dG = dP;
		dB = dQ;
		break;
	}

	dR *= 255;
	dG *= 255;
	dB *= 255;

	return D3DCOLOR_ARGB((int)dAlpha, (int)dR, (int)dG, (int)dB);
}

/*	RgbToGray
 *		RGB�̒l���O���[�X�P�[���ɂ���
 */
D3DCOLOR SbCore::RgbToGray(const double dAlpha, const double dRed, const double dGreen, const double dBlue)
{
	double dGray =0;

	//	NTSC�ł�YIQ�J���[���f���Ɋ�Â�����TV�p�̐F�ϊ��̐���
	dGray = (0.299 * dRed) + (0.587 * dGreen) + (0.114 * dBlue);

	return D3DCOLOR_ARGB((int)dAlpha, (int)dGray, (int)dGray, (int)dGray);
}