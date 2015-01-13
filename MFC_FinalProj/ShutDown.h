#pragma once
#include "afxwin.h"
#include "ClockSet.h"

#define WM_MYMESSAGE_SENDSHUTDOWNTOMAIN (WM_USER + 12)

struct ShutDownStruct{
	Clock clock;
	bool rebootflag;
};

// CShutDown 對話方塊

class CShutDown : public CDialogEx
{
	DECLARE_DYNAMIC(CShutDown)

public:
	CShutDown(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CShutDown();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_SHUTDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_combo_hr;
	CComboBox m_combo_min;
	CComboBox m_combo_sec;
};