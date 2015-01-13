// ClockChange.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_FinalProj.h"
#include "ClockChange.h"
#include "afxdialogex.h"


// CClockChange 對話方塊

IMPLEMENT_DYNAMIC(CClockChange, CDialogEx)

	CClockChange::CClockChange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClockChange::IDD, pParent)
{

}

CClockChange::~CClockChange()
{
}

void CClockChange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOHOUR, m_combo_hr);
	DDX_Control(pDX, IDC_COMBOMIN, m_combo_min);
	DDX_Control(pDX, IDC_COMBOSEC, m_combo_sec);
	DDX_Control(pDX, IDC_EDIT1, m_edit_path);
}


BEGIN_MESSAGE_MAP(CClockChange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CClockChange::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SELFILE, &CClockChange::OnBnClickedButtonSelfile)
	ON_MESSAGE(WM_MYMESSAGE_SENDTOCHANGE, &CClockChange::receiver) 
END_MESSAGE_MAP()


// CClockChange 訊息處理常式


BOOL CClockChange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化
	CString tp, tp2;

	for (int i=0; i<24; i++) {
		tp.Format(_T("%d%d"), i/10, i%10);
		m_combo_hr.AddString(tp);
	}
	for (int i=0; i<60; i++) {
		tp.Format(_T("%d%d"), i/10, i%10);
		m_combo_min.AddString(tp);
		m_combo_sec.AddString(tp);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}

LRESULT CClockChange::receiver(WPARAM wParam, LPARAM lParam)
{
	// 接受到訊息後的工作
	// do something

	// 接收傳過來的結構體
	CString* pRcv;
	pRcv = (CString*)wParam;

	// 取值
	m_combo_hr.SetCurSel(_wtoi(pRcv[0]));
	m_combo_min.SetCurSel(_wtoi(pRcv[1]));
	m_combo_sec.SetCurSel(_wtoi(pRcv[2]));
	m_edit_path.SetWindowTextW(pRcv[3]);
	newclock.index = pRcv[4];

	return LRESULT();
}

void CClockChange::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (m_combo_hr.GetWindowTextLengthW() == 0 ||
		m_combo_min.GetWindowTextLengthW() == 0 ||
		m_combo_sec.GetWindowTextLengthW() == 0)
		MessageBox(_T("時間欄位不可留白"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else if (m_edit_path.GetWindowTextLengthW() == 0)
		MessageBox(_T("請選擇音樂檔案"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else {
		m_combo_hr.GetWindowText(newclock.newclock.hr);
		m_combo_min.GetWindowText(newclock.newclock.min);
		m_combo_sec.GetWindowText(newclock.newclock.sec);
		m_edit_path.GetWindowText(newclock.newclock.path);

		CWnd* pWnd = CWnd::GetParent();
		pWnd->SendMessageW(WM_MYMESSAGE_SENDTOCLOCKMAIN2, (WPARAM)&newclock);
		CDialogEx::OnOK();
	}
}


void CClockChange::OnBnClickedButtonSelfile()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString lpszDefExt = L"MP3 Files (*.mp3)|*.mp3||";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY ,lpszDefExt , this);
	if (dlg.DoModal() == IDOK) {
		CString FileName = dlg.GetPathName(); //取得開啟檔案的全名(包含路徑)
		m_edit_path.SetWindowTextW(FileName);
	}
}
