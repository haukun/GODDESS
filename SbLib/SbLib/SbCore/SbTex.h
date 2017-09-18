/**
	@file		SbTex.h
	@brief		森羅万象テクスチャクラスヘッダー
	@author		Hau-kun
	@date		2010/05/16
	@version	0.1 alpha
*/

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#ifndef _SB_TEX_H_
#define _SB_TEX_H_

#define LPSBTEX SbTex*

/**
	@class		SbTex
	@brief		森羅万象テクスチャオブジェクト
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
class SbTex
{
public:
	SbTex(SbCore* pSbCore, LPCSTR strFilePath, const UINT nWidth, const UINT nHeight);
	~SbTex();
	   
	HRESULT Act(const UINT nX, const UINT nY, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dAngle, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colPaUINT, const BOOL bAbsolutePosition = FALSE);
    HRESULT Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colPaUINT, const RECT rectArea, const BOOL bAbsolutePosition = FALSE);

	LPDIRECT3DTEXTURE9	m_pDxTex;

private:
	UINT				m_nHeight;
	UINT				m_nWidth;
	LPD3DXSPRITE		m_pDxSprite;

	HRESULT _Act(const LPSBSPRITEPARAM pParam);
};


#endif