#include "stdafx.h"  
#include "CMCI.h"  
#pragma comment(lib, "winmm.lib ")  

CMCI::CMCI(CString FilePath,CString DeviceType=L"MPEGAudio")  
{  
	MCI_OPEN_PARMS pm;  
	pm.dwCallback=NULL;  
	pm.lpstrAlias=NULL;  
	pm.lpstrDeviceType=DeviceType;  
	pm.lpstrElementName=FilePath;  
	pm.wDeviceID=NULL;  
	if(0==mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&pm))  
	{  
		this->m_iDeviceType=pm.wDeviceID;  
	}  
}  
CMCI::~CMCI()  
{  
	if(this->m_iDeviceType) Close();  
}  
void CMCI::Play(UINT From, UINT To)  
{  
	MCI_PLAY_PARMS pm;  
	pm.dwCallback=0;  
	pm.dwFrom=From;  
	pm.dwTo=To;  
	if(!this->m_iDeviceType) return;  
	mciSendCommand(this->m_iDeviceType,  
		MCI_PLAY,  
		MCI_NOTIFY,  
		(DWORD)&pm);  
}  
void CMCI::Close()  
{  
	if(this->m_iDeviceType)  
	{  
		MCI_GENERIC_PARMS gp;  
		gp.dwCallback=NULL;  
		mciSendCommand(this->m_iDeviceType,  
			MCI_CLOSE,  
			MCI_WAIT,  
			(DWORD)&gp);  
		this->m_iDeviceType=NULL;  
	}  
}  
void CMCI::Pause()  
{  
	if(this->m_iDeviceType )  
	{  
		MCI_GENERIC_PARMS gp;  
		gp.dwCallback=NULL;  
		mciSendCommand(this->m_iDeviceType,  
			MCI_PAUSE,  
			MCI_WAIT,  
			(DWORD)&gp);  
	}  
}  
void CMCI::Resume()  
{  
	if(this->m_iDeviceType )  
	{  
		MCI_GENERIC_PARMS gp;  
		gp.dwCallback=NULL;  
		mciSendCommand(this->m_iDeviceType,  
			MCI_RESUME,  
			MCI_WAIT,  
			(DWORD)&gp);  
	}  
}  