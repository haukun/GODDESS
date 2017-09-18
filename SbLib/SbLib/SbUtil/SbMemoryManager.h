/**
	@file		SbMemoryManager.h
	@brief		メモリ管理クラスヘッダー
	@author		Hau-kun
	@date		2011/02/13
	@version	0.1
*/
#ifndef _SB_MEMORY_MANAGER_H_
#define _SB_MEMORY_MANAGER_H_

#include "..\sbstdafx.h"
#include "..\SbHeader.h"

#define LPSBMEMORYMANAGER SbMemoryManager*

/**
    @class      SbMemoryManager
    @brief      メモリ管理クラス
    @note
    @date       2011/02/13
    @version    0.1 alpha
*/
class SbMemoryManager
{
public:
    SbMemoryManager(void);
    ~SbMemoryManager(void);
    HRESULT AddObject(void* pObject);

private :
    void** m_parObject;
    int   m_nObjectCount;

};



#endif
