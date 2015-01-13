// CountDown.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_FinalProj.h"
#include "CountDown.h"
#include "afxdialogex.h"


// CCountDown 對話方塊

IMPLEMENT_DYNAMIC(CCountDown, CDialogEx)

CCountDown::CCountDown(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCountDown::IDD, pParent)
{

}

CCountDown::~CCountDown()
{
}

void CCountDown::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOHOUR, m_combo_hr);
	DDX_Control(pDX, IDC_COMBOMIN, m_combo_min);
	DDX_Control(pDX, IDC_COMBOSEC, m_combo_sec);
	DDX_Control(pDX, IDC_EDIT1, m_edit_path);
	DDX_Control(pDX, IDC_CHECK1, m_but_cycle);
}


BEGIN_MESSAGE_MAP(CCountDown, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCountDown::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SELFILE, &CCountDown::OnBnClickedButtonSelfile)
END_MESSAGE_MAP()


// CCountDown 訊息處理常式


BOOL CCountDown::OnInitDialog()
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
	for (int i=0; i<5; i++)
		send[i] = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


void CCountDown::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
		if (m_combo_hr.GetWindowTextLengthW() == 0 ||
		m_combo_min.GetWindowTextLengthW() == 0 ||
		m_combo_sec.GetWindowTextLengthW() == 0)
		MessageBox(_T("時間欄位不可留白"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else if (m_edit_path.GetWindowTextLengthW() == 0)
		MessageBox(_T("請選擇音樂檔案"), _T("錯誤"),  MB_ICONERROR | MB_OK);
	else {
		m_combo_hr.GetWindowText(send[0]);
		m_combo_min.GetWindowText(send[1]);
		m_combo_sec.GetWindowText(send[2]);
		m_edit_path.GetWindowText(send[3]);
		if (m_but_cycle.GetCheck() == BST_CHECKED)
			send[4] = L"是";
		else
			send[4] = L"否";

		CWnd* pWnd = CWnd::GetParent();
		pWnd->SendMessageW(WM_MYMESSAGE_SENDCOUNTDOWNDATA, (WPARAM)&send);

		CDialogEx::OnOK();
	}
}


void CCountDown::OnBnClickedButtonSelfile()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString lpszDefExt = L"MP3 Files (*.mp3)|*.mp3||";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY ,lpszDefExt , this);
	if (dlg.DoModal() == IDOK) {
		CString FileName = dlg.GetPathName(); //取得開啟檔案的全名(包含路徑)
		m_edit_path.SetWindowTextW(FileName);
	}
}
