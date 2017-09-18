/**
    @file       SbSpriteParam.cpp
    @brief      スプライトパラメータクラスソース
    @author     Hau-kun
    @date       2010/05/16
    @version    0.1 alpha
*/

#include "sbstdafx.h"
#include "SbSpriteParam.h"

SbSpriteParam::SbSpriteParam()
{
	m_dX = 0;
    m_dY = 0;
    m_dScaleX = 1.0;
    m_dScaleY = 1.0;
    m_dCenterX = 1.0;
    m_dCenterY = 1.0;
    m_vec3Angle = D3DXVECTOR3(0,0,0);
    m_strRotatePhase = "";
    m_colorPaint = D3DCOLOR_ARGB(255, 255, 255, 255);
    m_rectArea.left = 0;
    m_rectArea.top = 0;
    m_rectArea.right = 0;
    m_rectArea.bottom = 0;
    m_bAbsolutePosition = false;
}

SbSpriteParam::~SbSpriteParam()
{
}
/**
    @fn         HRESULT SbSpriteParam::SetPosition(const double dX, const double dY)
    @brief      クラスの座標を設定する
    @param[in]  double  dX      設定するX座標
    @param[in]  double  dY      設定するY座標
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetPosition(const double dX, const double dY)
{
    m_dX = dX;
    m_dY = dY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetScale(const double dScaleX, const double dScaleY)
    @brief      クラスの拡大率を設定する
    @param[in]  double  dScaleX  設定する横方向拡大率
    @param[in]  double  dScaleY  設定する縦方向拡大率
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetScale(const double dScaleX, const double dScaleY)
{
    m_dScaleX = dScaleX;
    m_dScaleY = dScaleY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetCenter(const double dCenterX, const double dCenterY)
    @brief      クラスの中心座標を設定する
    @param[in]  double  dCenterX    設定する中心のX座標
    @param[in]  double  dCenterY    設定する中心のY座標
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetCenter(const double dCenterX, const double dCenterY)
{
    m_dCenterX = dCenterX;
    m_dCenterY = dCenterY;
    return S_OK;
}

/**
    @fn         HRESULT SbSpriteParam::SetRect(const int nLeft, const int nTop, const int nRight, const int nBottom)
    @overload
    @brief      描画に使用する矩形の領域を設定する
    @param[in]  int     nLeft       設定するRECTの左量
    @param[in]  int     nTop        設定するRECTの上量
    @param[in]  int     nRight      設定するRECTの右量
    @param[in]  int     nBottom     設定するRECTの下量
    @retval     HRESULT S_OK
    @note       
    @date       2009/06/13
    @version    0.1
*/
HRESULT SbSpriteParam::SetRect(const int nLeft, const int nTop, const int nRight, const int nBottom)
{
    m_rectArea.left = nLeft;
    m_rectArea.top = nTop;
    m_rectArea.right = nRight;
    m_rectArea.bottom = nBottom;
    return S_OK;
}
