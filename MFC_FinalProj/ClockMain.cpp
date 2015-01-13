// ClockMain.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_FinalProj.h"
#include "ClockMain.h"
#include "afxdialogex.h"
#include "ClockChange.h"

// CClockMain 對話方塊

IMPLEMENT_DYNAMIC(CClockMain, CDialogEx)

	CClockMain::CClockMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClockMain::IDD, pParent)
{

}

CClockMain::~CClockMain()
{
}

void CClockMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CLOCKCT, m_st_clockct);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_STATIC_NOWTIME, m_st_nowtime);
}


BEGIN_MESSAGE_MAP(CClockMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTONADD, &CClockMain::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDOK, &CClockMain::OnBnClickedOk)
	ON_MESSAGE(WM_MYMESSAGE_SENDTOCLOCKMAIN, &CClockMain::rcvfromset)
	ON_BN_CLICKED(IDC_BUTTONDEL, &CClockMain::OnBnClickedButtondel)
	ON_WM_TIMER()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CClockMain::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CClockMain::OnNMDblclkList1)
	ON_MESSAGE(WM_MYMESSAGE_SENDTOCLOCKMAIN2, &CClockMain::rcvfromchange)
END_MESSAGE_MAP()


// CClockMain 訊息處理常式


BOOL CClockMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	m_ListCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //勾選,選整行
	m_ListCtrl.InsertColumn(0,L"時間",0,125,50);
	m_ListCtrl.InsertColumn(1,L"播放檔案",0,500,50);
	m_ListCtrl.InsertColumn(2,L"是否循環",0,100,50);
	for (int i=0; i<1000; i++) {
		clock[i].check = false;
		clock[i].hr = L"";
		clock[i].min = L"";
		clock[i].sec = L"";
		clock[i].path = L"";
		clock[i].cycle = false;
	}

	Sender.pClkRet = clock;
	Sender.pClkLiveRet = liveclock;
	Sender.clock_ct = 0;
	Sender.enable_clock_ct = 0;

	COleDateTime myDtTime;
	nowtime = CTime::GetCurrentTime();
	int nowhr, nowmin, nowsec;
	nowhr = nowtime.GetHour();
	nowmin = nowtime.GetMinute();
	nowsec = nowtime.GetSecond();
	tp2.Format(L"%d%d:", nowhr/10, nowhr%10);
	tp += tp2;
	tp2.Format(L"%d%d:", nowmin/10, nowmin%10);
	tp += tp2;
	tp2.Format(L"%d%d", nowsec/10, nowsec%10);
	tp += tp2;
	m_st_nowtime.SetWindowTextW(tp);
	StartTimer();

	CString tp_arr[6];
	CStdioFile myFile;
	CFileException fileException;
	int n, tp_len, count=0, i, readcount = 0;
	FILE *fStream;
	errno_t e = _tfopen_s(&fStream, _T("\data.txt"), _T("rt,ccs=UNICODE"));
	if (e == 0) 
	{
		CStdioFile myFile(fStream);  // open the file from this stream
		CString tp1, tp2, tp3, tp4, tp5, tp;
		while (myFile.ReadString(tp))
		{
			if (readcount == 0) 
			{
				readcount++;
				continue;
			}
			else if (readcount == 1)
			{
				Sender.clock_ct = _wtoi(tp);
				readcount++;
			}
			else 
			{
				n = 0;
				i = 0;
				tp_len = tp.GetLength();
				while (n < tp_len)
				{
					tp_arr[i++] = tp.Tokenize(L"\t", n);
				}
				i = 0;
				clock[count].hr = tp_arr[0];		//hour
				clock[count].min =tp_arr[1];		//min
				clock[count].sec = tp_arr[2];		//sec
				clock[count].path = tp_arr[3];		//path
				if (tp_arr[4] == L"1") {			//check
					clock[count].check = true;
				}
				else 
					clock[count].check = false;
				if (tp_arr[5] == L"是") {
					clock[count].cycle = true;
				}
				else
					clock[count].cycle = false;
				count++;
			}
		}
		myFile.Close();
	}
	for (int i=0; i<Sender.clock_ct; i++)
	{
		tp.Format(L"Clock%d", i);
		m_ListCtrl.InsertItem(i, tp);						//count
		tp = clock[i].hr + L":" + clock[i].min + L":" + clock[i].sec;
		m_ListCtrl.SetItemText(i,0, tp);					//time
		m_ListCtrl.SetItemText(i,1, clock[i].path);			//path
		if (clock[i].cycle)
			tp = L"是";
		else
			tp = L"否";
		m_ListCtrl.SetItemText(i,2, tp);					//cycle

		if (clock[i].check)
			m_ListCtrl.SetItemState(i, INDEXTOSTATEIMAGEMASK(2), LVIS_STATEIMAGEMASK);
		else
			m_ListCtrl.SetItemState(i, INDEXTOSTATEIMAGEMASK(1), LVIS_STATEIMAGEMASK);
									   //2 -> checked , 1 -> not checked

		m_ListCtrl.SetItemData(i, i);						//for sorting
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


void CClockMain::OnBnClickedButtonadd()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CClockSet dlg;
	dlg.DoModal();
}

LRESULT CClockMain::rcvfromset(WPARAM wParam, LPARAM lParam) {
	Clock *rcv;
	rcv = (Clock*) wParam;
	clock[Sender.clock_ct].hr = rcv->hr;
	clock[Sender.clock_ct].min = rcv->min;
	clock[Sender.clock_ct].sec = rcv->sec;
	clock[Sender.clock_ct].path = rcv->path;
	clock[Sender.clock_ct].cycle = rcv->cycle;

	CString tp;
	tp.Format(L"Clock%d", Sender.clock_ct);
	m_ListCtrl.InsertItem(Sender.clock_ct, tp);
	tp.Format(L"%s:%s:%s", clock[Sender.clock_ct].hr, clock[Sender.clock_ct].min, clock[Sender.clock_ct].sec);
	m_ListCtrl.SetItemText(Sender.clock_ct, 0, tp);
	m_ListCtrl.SetItemText(Sender.clock_ct, 1, clock[Sender.clock_ct].path);
	if (clock[Sender.clock_ct].cycle == true)
		tp = L"是";
	else
		tp = L"否";
	m_ListCtrl.SetItemText(Sender.clock_ct, 2, tp);
	m_ListCtrl.SetItemData(0, 0); //for sorting

	Sender.clock_ct++;

	return LRESULT();
}

LRESULT CClockMain::rcvfromchange(WPARAM wParam, LPARAM lParam) {
	ClockChange *rcv;
	rcv = (ClockChange*) wParam;
	int index = _wtoi(rcv->index);
	clock[index].hr = rcv->newclock.hr;
	clock[index].min = rcv->newclock.min;
	clock[index].sec = rcv->newclock.sec;
	clock[index].path = rcv->newclock.path;
	clock[index].cycle = rcv->newclock.cycle;

	tp.Format(L"%s:%s:%s", clock[index].hr, clock[index].min, clock[index].sec);
	m_ListCtrl.SetItemText(index, 0, tp);
	m_ListCtrl.SetItemText(index, 1, clock[index].path);
	if (clock[index].cycle)
		tp = L"是";
	else
		tp = L"否";
	m_ListCtrl.SetItemText(index, 2, tp);

	return LRESULT();
}

void CClockMain::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	StopTimer();

	for (int i=0, j=0; i<Sender.clock_ct; i++) {
		if (clock[i].check == true) {
			liveclock[j].check = clock[i].check;
			liveclock[j].hr = clock[i].hr;
			liveclock[j].min = clock[i].min;
			liveclock[j].sec = clock[i].sec;
			liveclock[j].cycle = clock[i].cycle;
			liveclock[j++].path = clock[i].path;
		}
	}

	CWnd* pWnd = CWnd::GetParent();
	pWnd->SendMessageW(WM_MYMESSAGE_SENDTOMAIN, (WPARAM)&Sender);

	CDialogEx::OnOK();
}


void CClockMain::OnBnClickedButtondel()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	int row = m_ListCtrl.GetSelectionMark();
	if (m_ListCtrl.GetItemState(row, LVIS_SELECTED) == LVIS_SELECTED) {
		if (clock[row].check) {
			Sender.enable_clock_ct--;
			tp.Format(L"%d", Sender.enable_clock_ct);
			m_st_clockct.SetWindowTextW(tp);
			UpdateData(true);
		}
		for (int i=row; i<Sender.clock_ct-1; i++) {
			clock[i].hr = clock[i+1].hr;
			clock[i].min = clock[i+1].min;
			clock[i].sec = clock[i+1].sec;
			clock[i].path = clock[i+1].path;
			clock[i].cycle = clock[i+1].cycle;
		}
		m_ListCtrl.DeleteItem(row);
		Sender.clock_ct -= 1;

	}
}


void CClockMain::StartTimer()
{
	SetTimer(ID_TIMER_SECOND, SECOND_ELAPSE, NULL);
}


void CClockMain::StopTimer()
{
	KillTimer(ID_TIMER_SECOND);
}

void CClockMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	int nowhr, nowmin, nowsec;
	CString tp, tp2;
	switch (nIDEvent) {
	case ID_TIMER_SECOND:
		nowtime = CTime::GetCurrentTime();
		nowhr = nowtime.GetHour();
		nowmin = nowtime.GetMinute();
		nowsec = nowtime.GetSecond();
		tp2.Format(L"%d%d:", nowhr/10, nowhr%10);
		tp += tp2;
		tp2.Format(L"%d%d:", nowmin/10, nowmin%10);
		tp += tp2;
		tp2.Format(L"%d%d", nowsec/10, nowsec%10);
		tp += tp2;
		m_st_nowtime.SetWindowTextW(tp);
		break;
	default:
		break;
	}
}

void CClockMain::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 在此加入控制項告知處理常式程式碼
	if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */ 
		) 
	{ 
		//TRACE("Item %d is checked\n", pNMLV->iItem); 
		Sender.enable_clock_ct++;
		clock[pNMLV->iItem].check = true;

	} 
	else if((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */ 
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */ 
		) 
	{ 
		//TRACE("Item %d is unchecked\n", pNMLV->iItem); 
		Sender.enable_clock_ct--;
		clock[pNMLV->iItem].check = false;
	} 
	else 
	{ 
		tp.Format(L"%d", Sender.enable_clock_ct);
		m_st_clockct.SetWindowTextW(tp);
		UpdateData(true);
	} 
	tp.Format(L"%d", Sender.enable_clock_ct);
	m_st_clockct.SetWindowTextW(tp);
	UpdateData(true);

	*pResult = 0; 

}

void CClockMain::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 在此加入控制項告知處理常式程式碼
	
	int row = m_ListCtrl.GetSelectionMark();
	if(row < 0)
		return;
	CString str[6];
	str[0] = clock[row].hr;
	str[1] = clock[row].min;
	str[2] = clock[row].sec;
	str[3] = clock[row].path;
	str[4].Format(L"%d", row);
	if (clock[row].cycle)
		str[5] = L"是";
	else
		str[5] = L"否";
	CClockChange *dlg = new CClockChange();
	if (dlg != NULL) {
		BOOL ret = dlg->Create(IDD_DIALOG_CLOCKCHANGE, this);
		if (!ret)
			AfxMessageBox(_T("Error creating Dialog"));
		dlg->ShowWindow(SW_SHOW);
		CWnd* pWnd = CWnd::FindWindowW(NULL, L"修改鬧鐘");
		pWnd->SendMessageW(WM_MYMESSAGE_SENDTOCHANGE, (WPARAM)&str);
	}
	else
		AfxMessageBox(_T("Error Creating Dialog Object"));

	*pResult = 0;
}
