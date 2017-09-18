/**
	@file		SbCore.h
	@brief		�X�����ۃR�A�N���X�w�b�_�[
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#ifndef _SB_CORE_H_
#define _SB_CORE_H_

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

typedef struct SbSetupInfo
{
}SbSetupInfo;

typedef struct SbExecuteInfo
{
}SbExecuteInfo;

typedef struct SbActionInfo
{
}SbActionInfo;

/**
	@class		SbCore
	@brief		�X�����ۃR�A�I�u�W�F�N�g
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
class SbCore
{
public:
	SbCore(void);
	SbCore(SbWindow* pWnd);
	~SbCore();

	virtual HRESULT Create(SbWindow* pWnd, int nWidth = 0, int nHeight = 0);

	HRESULT Action(SbActionInfo* pInfo);

	HRESULT Clear(const D3DCOLOR color);
	HRESULT Flip(void);

	LPDIRECT3DDEVICE9	GetDevice(void);
	LPD3DXSPRITE		GetSprite(void);

	HRESULT		BeginAct(void);
	HRESULT		EndAct(void);

	UINT		GetFps(void);

    HRESULT     SetRenderAlphaBlend(const bool bSwitch);    //  �A���t�@�u�����h�ݒ�
    HRESULT     SetRenderAlphaBlendMode(const DWORD dwBlendOperation, const DWORD dwSrcBlend, const DWORD dwDstBlend);
    HRESULT     SetRenderAlphaBlendModeAddComposition(void);//  ���Z����
    HRESULT     SetRenderAlphaBlendModeTransparent(void);   //  ������

	virtual HRESULT Setup(SbSetupInfo* pInfo) = 0;
	virtual HRESULT Execute(SbExecuteInfo* pInfo) = 0;

	HRESULT SaveCaptureBmp(char* strFilePath);
	HRESULT SaveCapturePng(char* strFilePath);

	D3DCOLOR HsvToRgb(double dAlpha, double dHue, double dSaturation, double dValue);
	D3DCOLOR RgbToGray(double dAlpha, double dRed, double dGreen, double dBlue);

protected:
	SbWindow*				m_pWnd;				//	�X�����ۃE�B���h�E

private:
	HRESULT	CreateDx9Object(void);
	HRESULT CreateDx9Device(HWND hWnd);
	HRESULT CreateDxSprite(void);


	LPDIRECT3D9				m_d3d9Object;		//	DirectX9�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_d3d9Device;		//	DirectX9�f�o�C�X
	LPD3DXSPRITE			m_d3dxSprite;		//	�X�v���C�g
	D3DPRESENT_PARAMETERS	m_d3dpp;			//	�v���[���e�[�V�����p�����[�^�[

	LPSBLOGMANAGER			m_pSbLogManager;	//	�X�����ۃ��O�}�l�[�W���[

	UINT					m_nFpsCurrent;		//	FPS�l
	UINT					m_nFpsCount;		//	FPS�J�E���g�l		
	time_t					m_timeFpsBase;		//	FPS�����

};


#endif