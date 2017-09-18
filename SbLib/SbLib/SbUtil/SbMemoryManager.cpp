/**
	@file		SbMemoryManager.cpp
	@brief		メモリ管理クラスソース
	@author		Hau-kun
	@date		2011/02/13
	@version	0.1
*/

#include "sbstdafx.h"
#include "SbMemoryManager.h"

/**
	@fn			SbMemoryManager::SbMemoryManager(void)
	@brief		コンストラクタ
	@note
	@date		2011/02/13
	@version	0.1	alpha
*/
SbMemoryManager::SbMemoryManager(void)
{
    m_nObjectCount = 0;
	m_parObject = (void**)malloc(sizeof(void*) * m_nObjectCount);
}

/**
	@fn			SbMemoryManager::~SbMemoryManager(void)
	@brief		デストラクタ
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
SbMemoryManager::~SbMemoryManager(void)
{
    for(int i = 0; i < m_nObjectCount; i++){
		if(m_parObject[i] != NULL)
		{
			delete m_parObject[i];
			m_parObject[i] = NULL;
		}
    }
}

/**
    @fn         SbMemoryManager::AddObject
    @brief      オブジェクトのポインタを追加する
    @param[in]  void*   pObject         管理するオブジェクトのポインタ
    @return     HRESULT S_OK 成功
    @note
    @date       2011/02/13
    @version    0.1 alpha
*/
HRESULT SbMemoryManager::AddObject(void* pObject)
{
    m_nObjectCount++;
    m_parObject = (void**)realloc(m_parObject, sizeof(void*) * m_nObjectCount);
    m_parObject[m_nObjectCount - 1] = pObject;
    return S_OK;
}