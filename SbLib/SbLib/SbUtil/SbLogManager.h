/**
	@file		SbLogManager.h
	@brief		ログ管理クラスヘッダー
	@author		Hau-kun
	@date		2010/05/15
	@version	0.1
*/

#include "..\sbstdafx.h"


#ifndef _SB_WINDOW_LOG_H_
#define _SB_WINDOW_LOG_H_

#define LPSBLOGMANAGER SbLogManager*
#define SBLOG_HR(str, hr)	SbLogManager::Log(__FILE__, __LINE__, hr, str);
#define SBLOG(str)			SbLogManager::Log(__FILE__, __LINE__, S_OK, str);	
#define SBLOG_NUM(str, num)	SbLogManager::Log(__FILE__, __LINE__, S_OK, str, num);	



/**
	@class		SbLogManager
	@brief		ログ管理クラス
	@note
	@date		2010/05/15
	@version	0.1	alpha
*/
class SbLogManager
{
public:
	SbLogManager(LPSTR strFileName);
	~SbLogManager(void);
	static HRESULT Create(LPSTR strFileName);
	static HRESULT SbLogManager::Log(LPSTR strFileName, int strLineNumber, const HRESULT hr, LPCSTR strLog);
    static HRESULT SbLogManager::Log(LPSTR strFileName, int strLineNumber, const HRESULT hr, LPCSTR strLog, double intLog);

private :
	static std::fstream m_srmFile;
};

#endif