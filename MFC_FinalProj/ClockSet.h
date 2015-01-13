#pragma once
#include "afxwin.h"

#define WM_MYMESSAGE_SENDTOCLOCKMAIN (WM_USER + 2)

struct Clock {
	bool check, cycle;
	CString hr, min, sec, path;
};

// CClockSet 對話方塊

class CClockSet : public CDialogEx
{
	DECLARE_DYNAMIC(CClockSet)

public:
	CClockSet(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CClockSet();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_CLOCKSET1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CComboBox m_ComboBoxHr;
	CComboBox m_ComboBoxMin;
	CComboBox m_ComboBoxSec;
	Clock newclock;
	CEdit m_EditPath;
	afx_msg void OnBnClickedButtonSelfile();
	CButton m_but_cycle;
};
