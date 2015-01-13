	// ClockSet.cpp : 實作檔
	//

	#include "stdafx.h"
	#include "MFC_FinalProj.h"
	#include "ClockSet.h"
	#include "afxdialogex.h"


	// CClockSet 對話方塊

	IMPLEMENT_DYNAMIC(CClockSet, CDialogEx)

	CClockSet::CClockSet(CWnd* pParent /*=NULL*/)
		: CDialogEx(CClockSet::IDD, pParent)
	{

	}

	CClockSet::~CClockSet()
	{
	}

	void CClockSet::DoDataExchange(CDataExchange* pDX)
	{
		CDialogEx::DoDataExchange(pDX);
		DDX_Control(pDX, IDC_COMBOHOUR, m_ComboBoxHr);
		DDX_Control(pDX, IDC_COMBOMIN, m_ComboBoxMin);
		DDX_Control(pDX, IDC_COMBOSEC, m_ComboBoxSec);
		DDX_Control(pDX, IDC_EDIT1, m_EditPath);
		DDX_Control(pDX, IDC_CHECK1, m_but_cycle);
		DDX_Control(pDX, IDC_CHECK1, m_but_cycle);
	}


	BEGIN_MESSAGE_MAP(CClockSet, CDialogEx)
		ON_BN_CLICKED(IDOK, &CClockSet::OnBnClickedOk)
		ON_BN_CLICKED(IDC_BUTTON_SELFILE, &CClockSet::OnBnClickedButtonSelfile)
	END_MESSAGE_MAP()


	// CClockSet 訊息處理常式


	BOOL CClockSet::OnInitDialog()
	{
		CDialogEx::OnInitDialog();
		// TODO:  在此加入額外的初始化
		CString tp, tp2;

		for (int i=0; i<24; i++) {
			tp.Format(_T("%d%d"), i/10, i%10);
			m_ComboBoxHr.AddString(tp);
		}
		for (int i=0; i<60; i++) {
			tp.Format(_T("%d%d"), i/10, i%10);
			m_ComboBoxMin.AddString(tp);
			m_ComboBoxSec.AddString(tp);
		}

		return TRUE;  // return TRUE unless you set the focus to a control

		// EXCEPTION: OCX 屬性頁應傳回 FALSE
	}

	void CClockSet::OnBnClickedOk()
	{
		// TODO: 在此加入控制項告知處理常式程式碼
		if (m_ComboBoxHr.GetWindowTextLengthW() == 0 ||
			m_ComboBoxMin.GetWindowTextLengthW() == 0 ||
			m_ComboBoxSec.GetWindowTextLengthW() == 0)
			MessageBox(_T("時間欄位不可留白"), _T("錯誤"),  MB_ICONERROR | MB_OK);
		else if (m_EditPath.GetWindowTextLengthW() == 0)
			MessageBox(_T("請選擇音樂檔案"), _T("錯誤"),  MB_ICONERROR | MB_OK);
		else {
			m_ComboBoxHr.GetWindowText(newclock.hr);
			m_ComboBoxMin.GetWindowText(newclock.min);
			m_ComboBoxSec.GetWindowText(newclock.sec);
			m_EditPath.GetWindowText(newclock.path);
			if (m_but_cycle.GetCheck() == BST_CHECKED)
				newclock.cycle = true;
			else
				newclock.cycle = false;

			CWnd* pWnd = CWnd::GetParent();
			pWnd->SendMessageW(WM_MYMESSAGE_SENDTOCLOCKMAIN, (WPARAM)&newclock);

			CDialogEx::OnOK();
		}
	}


	void CClockSet::OnBnClickedButtonSelfile()
	{
		// TODO: 在此加入控制項告知處理常式程式碼
		CString lpszDefExt = L"MP3 Files (*.mp3)|*.mp3||";
		CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY ,lpszDefExt , this);
		if (dlg.DoModal() == IDOK) {
			CString FileName = dlg.GetPathName(); //取得開啟檔案的全名(包含路徑)
			m_EditPath.SetWindowTextW(FileName);
		}
	}
