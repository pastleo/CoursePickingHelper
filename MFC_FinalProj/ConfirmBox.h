#pragma once
#include "afxwin.h"


// ConfirmBox 對話方塊

class ConfirmBox : public CDialogEx
{
	DECLARE_DYNAMIC(ConfirmBox)

public:
	ConfirmBox(CString* msg,CWnd* pParent = NULL);   // 標準建構函式
	virtual ~ConfirmBox();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_CONFIRM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
	CString* msg;
public:
	CStatic m_text_msg;
};
