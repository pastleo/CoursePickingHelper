#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <mmsystem.h>
#include <Digitalv.h>

class CMCI    
{  
public:  
	void Resume();  
	void Pause();  
	void Close();  
	void Play(UINT From,UINT To, bool cycle);  
	UINT m_iDeviceType;  
	CMCI(CString FilePath,CString DeviceType);  
	virtual ~CMCI();  
};  