/**
	@file		SbTex.cpp
	@brief		森羅万象テクスチャクラスソース
	@author		Hau-kun
	@date		2010/05/16
	@version	0.1 alpha
*/

#include "sbstdafx.h"
#include "SbTex.h"

/**
	@fn			SbTex::SbTex(void)
	@brief		コンストラクタ
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
SbTex::SbTex(SbCore* pSbCore, LPCSTR strFilePath, const UINT nWidth, const UINT nHeight)
{
	m_nWidth	= 0;
	m_nHeight	= 0;

	m_pDxTex	= NULL;
	m_pDxSprite = NULL;

	m_nWidth  = nWidth;
	m_nHeight = nHeight;

	m_pDxSprite = pSbCore->GetSprite();

	//	テクスチャの作成
	HRESULT hr = D3DXCreateTextureFromFileEx(pSbCore->GetDevice(), strFilePath, nWidth, nHeight, 0, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		0xff000000, NULL, NULL, &m_pDxTex);

	SBLOG_HR(strFilePath, hr);
}

/**
	@fn			SbTex::~SbTex(void)
	@brief		デストラクタ
	@note
	@date		2010/05/16
	@version	0.1	alpha
*/
SbTex::~SbTex(void)
{
	if (m_pDxTex != NULL)
	{
		m_pDxTex->Release();
	}
}


/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

	SbSpriteParam param;

	param.SetPosition(nX, nY);
    param.SetCenter((m_nWidth) / 2, (m_nHeight) / 2);
	param.SetRect(0, 0, m_nWidth, m_nHeight);

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
	param.m_rectArea = rectArea;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dAngle					回転の角度
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
	param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;
    
    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dAngle					回転角度
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;
    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dAngle					回転角度
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dAngle					回転角度
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
	param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;
    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  BOOL        bAbsolutePosition		左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DCOLOR    colorPaint				 配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  double      dAngle					回転角度
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  double      dAngle					回転角度
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition        左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  double      dAngle					回転角度
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  double      dAngle					回転角度
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const double dAngle, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = D3DXVECTOR3(0, 0, (FLOAT)dAngle);
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), "Z");
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter(m_nWidth / 2, m_nHeight / 2);
    param.SetRect(0, 0, m_nWidth, m_nHeight);
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}

/**
    @fn         HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
    @overload
    @brief      スプライト描画
    @param[in]  UINT        nX						描画する位置のX座標
    @param[in]  UINT        nY						描画する位置のY座標
    @param[in]  double      dScaleX					横方向の拡大率
    @param[in]  double      dScaleY					縦方向の拡大率
    @param[in]  D3DXVECTOR3 vec3Angle				XYZ軸のそれぞれの回転角度
    @param[in]  Cstring     strRotatePhase			XYZの回転する順番祖表す文字列
    @param[in]  D3DCOLOR    colorPaint				配色
    @param[in]  RECT        rectArea				描画に使う領域
    @param[in]  BOOL        bAbsolutePosition       左上を基準点とするフラグ。
    @retval     HRESULT     _Act()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::Act(const UINT nX, const UINT nY, const double dScaleX, const double dScaleY, const D3DXVECTOR3 vec3Angle, LPCSTR strRotatePhase, const D3DCOLOR colorPaint, const RECT rectArea, const BOOL bAbsolutePosition)
{
    HRESULT hr = S_OK;

    SbSpriteParam param;

    param.SetPosition(nX, nY);    
    param.SetCenter((rectArea.right - rectArea.left) / 2, (rectArea.bottom - rectArea.top) / 2);
    param.m_rectArea = rectArea;
    param.SetScale(dScaleX, dScaleY);
    param.m_vec3Angle = vec3Angle;
	strcpy_s(param.m_strRotatePhase, sizeof(param.m_strRotatePhase), strRotatePhase);
    param.m_colorPaint = colorPaint;
    param.m_bAbsolutePosition = bAbsolutePosition;

    hr = _Act(&param);

    return hr;
}


/**
    @fn         HRESULT SbTex::Act_ORIG(const LPSBSPRITEPARAM pParam)
    @brief      スプライト描画本体
    @param[in]  LPSBSPRITEPARAM		pLPSBSPRITEPARAM       スプライト描画情報クラス
    @retval     HRESULT				Draw()の戻り値
    @note
    @date       2010/05/16
    @version    0.1 alpha
*/
HRESULT SbTex::_Act(const LPSBSPRITEPARAM pParam)
{
    HRESULT hr = S_OK;          //  この関数の戻り値

    D3DXMATRIX mxResult;            //  変換結果の行列

    //  単位行列を作成
    D3DXMatrixIdentity(&mxResult); 

    //  原点が左上ではなければ、中心で伸縮・回転を行うために、中央に原点を移動
    if(!(pParam->m_bAbsolutePosition))
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)-pParam->m_dCenterX, (FLOAT)-pParam->m_dCenterY, 0);
        mxResult = mxOrigin;
    }
    
    //  拡大行列作成
    D3DXMATRIX mxScale;
    if((pParam->m_dScaleX != 1.0) && (pParam->m_dScaleY != 1.0))
    {
        D3DXMatrixScaling(&mxScale, (FLOAT)pParam->m_dScaleX, (FLOAT)pParam->m_dScaleY, 0);
        mxResult = mxResult * mxScale;
    }

    //  原点が左上ならば、中心で回転を行うために、中央に原点を移動
    if(pParam->m_bAbsolutePosition)
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)(-pParam->m_dCenterX * pParam->m_dScaleX), (FLOAT)(-pParam->m_dCenterY * pParam->m_dScaleY), 0);
        mxResult = mxResult * mxOrigin;
    }

    //  回転行列作成
    D3DXMATRIX mxRotation;
    double dPseudoRotateX = 1, dPseudoRotateY = 1;  //  X,Yの回転を擬似回転にするため、その伸縮率を表す変数。

    //  回転順序に従い回転を行う。
    for(int nI = 0; nI < strlen(pParam->m_strRotatePhase); nI++)
    {
        switch(pParam->m_strRotatePhase[nI])
        {
            case 'x':
            case 'X':
                //  Z=0しか描画されないようなので、伸縮を使って擬似回転。
                //D3DXMatrixRotationX(&mxRotation, pLPSBSPRITEPARAM->m_vec3Angle.x);
                //mxResult = mxResult * mxRotation;
                //
                dPseudoRotateX = cos(pParam->m_vec3Angle.x);
                break;
            case 'y':
            case 'Y':
                //  Z=0しか描画されないようなので、伸縮を使って擬似回転。
                //D3DXMatrixRotationY(&mxRotation,  pLPSBSPRITEPARAM->m_vec3Angle.y);
                //mxResult = mxResult * mxRotation;
                //
                dPseudoRotateY = cos(pParam->m_vec3Angle.y);
                break;
            case 'z':
            case 'Z':
                D3DXMatrixRotationZ(&mxRotation,  pParam->m_vec3Angle.z);
                mxResult = mxResult * mxRotation;
                break;
        }
    }

    //  擬似回転：XとYの伸縮率を元に、拡大縮小をする。
    if(strlen(pParam->m_strRotatePhase) != 0){
        D3DXMATRIX mxPseudoRotate;
        D3DXMatrixScaling(&mxPseudoRotate, (FLOAT)dPseudoRotateX, (FLOAT)dPseudoRotateY, 1);
        mxResult = mxResult * mxPseudoRotate;
    }

    //  絶対座標であれば、原点を左上に戻す
    if(pParam->m_bAbsolutePosition)
    {
        D3DXMATRIX mxOrigin;
        D3DXMatrixTranslation(&mxOrigin, (FLOAT)(pParam->m_dCenterX * pParam->m_dScaleX), (FLOAT)(pParam->m_dCenterY  * pParam->m_dScaleY), 0);
        mxResult = mxResult * mxOrigin;
    }

    //  平行移動：原点を描画すべき位置に移動する。
    D3DXMATRIX mxTranslation;
    D3DXMatrixTranslation(&mxTranslation, (FLOAT) pParam->m_dX, (FLOAT) pParam->m_dY, 0);
    mxResult = mxResult * mxTranslation;
    
    //  行列を適用する
	m_pDxSprite->SetTransform(&mxResult);
   
    //  画像を描画する
	RECT rect = pParam->m_rectArea;

	hr = m_pDxSprite->Draw(m_pDxTex, &rect, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3(0,0,0),  pParam->m_colorPaint);
   
    return hr;
}
