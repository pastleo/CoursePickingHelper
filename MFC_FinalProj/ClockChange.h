#pragma once
#include "afxwin.h"
#include "ClockSet.h"
#include "ClockMain.h"

#define WM_MYMESSAGE_SENDTOCLOCKMAIN2 (WM_USER + 8)

struct ClockChange {
	Clock newclock;
	CString index;
};

// CClockChange 對話方塊


class CClockChange : public CDialogEx
{
	DECLARE_DYNAMIC(CClockChange)

public:
	CClockChange(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CClockChange();
	afx_msg LRESULT receiver(WPARAM wParam, LPARAM lParam);

// 對話方塊資料
	enum { IDD = IDD_DIALOG_CLOCKCHANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_combo_hr;
	CComboBox m_combo_min;
	CComboBox m_combo_sec;
	CEdit m_edit_path;
	afx_msg void OnBnClickedOk();
	ClockChange newclock;
	afx_msg void OnBnClickedButtonSelfile();
};
