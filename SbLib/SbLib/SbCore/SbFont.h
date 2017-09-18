/**
	@file		SbFont.h
	@brief		森羅万象フォントクラスヘッダー
	@author		Hau-kun
	@date		2010/05/09
	@version	0.1 alpha
*/

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#ifndef _SB_FONT_H_
#define _SB_FONT_H_

#define LPSBFONT SbFont*

/**
	@class		SbFont
	@brief		森羅万象フォントオブジェクト
	@note
	@date		2010/05/09
	@version	0.1	alpha
*/
class SbFont
{
public:
	SbFont(SbCore* pSbCore);


	~SbFont();
	
	HRESULT		Act(const LPCSTR szText, const LPRECT rect);
	HRESULT		Act(const LPCSTR szText, const LPRECT rect, const DWORD dwFormat, const D3DCOLOR color);
	HRESULT		SetFontSize(const UINT nWidth, const UINT nHeight);
	HRESULT		SetFontType(const boolean fBold, const boolean fItalic);
	HRESULT		SetFontName(LPCSTR strFontName);
	HRESULT		Create(void);

private:

	LPD3DXFONT			m_font;			//	フォントオブジェクト
	D3DXFONT_DESC		m_fontDesc;		//	フォント情報
	LPDIRECT3DDEVICE9	m_d3d9Device;	//	Direct3DDevice9オブジェクトへの参照
	boolean				m_fNeedCreate;	//	再生成が必要フラグ

};


#endif