﻿
/***************************
FinalProj_Team_8 1/16
4101056017 資工三 邱冠喻 Chiu Guan-Yu
4101040018 資工三 王建舜 Wang Jian-Shun
***************************/

#include "stdafx.h"
#include "MFC_FinalProj.h"
#include "MFC_FinalProjDlg.h"
#include "afxdialogex.h"
#include "ClockMain.h"
#include "ConfirmBox.h"
#include "shutdown_method.h"
#include <iostream>
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_FinalProjDlg 對話方塊



CMFC_FinalProjDlg::CMFC_FinalProjDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_FinalProjDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_FinalProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CLOCKCT, m_st_clockct);
	DDX_Control(pDX, IDC_STATIC_TIMER_TEXT, m_st_timertext);
	DDX_Control(pDX, IDC_STATIC_SHUTDOWNTEXT, m_st_shutdowntext);
	DDX_Control(pDX, IDC_STATIC_NEXTCLOCK, m_st_nextclock);
	DDX_Control(pDX, IDC_STATIC1, m_st_hide);
	DDX_Control(pDX, IDC_STATIC_NOWTIME, m_st_nowtime);
	DDX_Control(pDX, IDC_BUTTON_PLAYPAUSE, m_but_playpause);
	DDX_Control(pDX, IDC_BUTTON_PLAYPAUSE2, m_stopwatch_playpause);
	DDX_Control(pDX, IDC_STATIC_STOPWATCH, m_st_stopwatch);
	DDX_Control(pDX, IDC_ADD_CLASS, m_com_addclass);
	DDX_Control(pDX, IDC_CLASS_TABLE, m_list_classtable);
	DDX_Control(pDX, IDC_UNSET, m_com_unset);
	DDX_Control(pDX, IDC_IMPORT_SAVE, m_btn_import_save);
}

BEGIN_MESSAGE_MAP(CMFC_FinalProjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONCLOCK, &CMFC_FinalProjDlg::OnBnClickedButtonclock)
	ON_MESSAGE(WM_MYMESSAGE_SENDTOMAIN, &CMFC_FinalProjDlg::rcvfromClockMain)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONCOUNTDOWN, &CMFC_FinalProjDlg::OnBnClickedButtoncountdown)
	ON_MESSAGE(WM_MYMESSAGE_SENDCOUNTDOWNDATA, &CMFC_FinalProjDlg::rcvfromCountDown)
	ON_BN_CLICKED(IDC_BUTTON_PLAYPAUSE, &CMFC_FinalProjDlg::OnBnClickedButtonPlaypause)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CMFC_FinalProjDlg::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTON_STOPWATCH, &CMFC_FinalProjDlg::OnBnClickedButtonStopwatch)
	ON_BN_CLICKED(IDC_BUTTON_PLAYPAUSE2, &CMFC_FinalProjDlg::OnBnClickedButtonPlaypause2)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, &CMFC_FinalProjDlg::OnBnClickedButtonclear)
	ON_MESSAGE(WM_MYMESSAGE_SENDSHUTDOWNTOMAIN, &CMFC_FinalProjDlg::rcvfromShutDown) 
	ON_BN_CLICKED(IDC_BUTTONSHUTDOWN, &CMFC_FinalProjDlg::OnBnClickedButtonshutdown)
	ON_BN_CLICKED(IDC_BUTTON_STOPSHUTDOWN, &CMFC_FinalProjDlg::OnBnClickedButtonStopshutdown)
	ON_CBN_DROPDOWN(IDC_ADD_CLASS, &CMFC_FinalProjDlg::OnCbnDropdownAddClass)
	ON_NOTIFY(NM_CLICK, IDC_CLASS_TABLE, &CMFC_FinalProjDlg::OnNMClickClassTable)
	ON_CBN_SELCHANGE(IDC_ADD_CLASS, &CMFC_FinalProjDlg::OnCbnSelchangeAddClass)
	ON_CBN_SELCHANGE(IDC_UNSET, &CMFC_FinalProjDlg::OnCbnSelchangeUnset)
	ON_CBN_DROPDOWN(IDC_UNSET, &CMFC_FinalProjDlg::OnCbnDropdownUnset)
	ON_BN_CLICKED(IDC_IMPORT_SAVE, &CMFC_FinalProjDlg::OnBnClickedImportSave)
END_MESSAGE_MAP()


// CMFC_FinalProjDlg 訊息處理常式

BOOL CMFC_FinalProjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	memset (isused, 0, sizeof(isused));

	CTime now = CTime::GetCurrentTime();
	CString nowstr, msgboxstr;
	int nowhr, nowmin, nowsec;
	nowhr = now.GetHour();
	nowmin = now.GetMinute();
	nowsec = now.GetSecond();
	nowstr.Format(L"%d%d:%d%d:%d%d", nowhr/10, nowhr%10, nowmin/10, nowmin%10, nowsec/10, nowsec%10);
	m_st_nowtime.SetWindowTextW(nowstr);
	clock_ct = 0;
	SetTimer(1, 1000, NULL);
	for (int i=0; i<4; i++)
		CountDownData[i] = "";
	for (int i=0; i<3; i++)
		stopwatch[i] = "";
	stopwatchflag = false;

	m_list_classtable.InsertColumn(0,_T(""),0,200);
	m_list_classtable.InsertItem(0,_T("請匯入課程"));
	m_com_addclass.SetCueBanner(_T("請匯入課程"));
	m_com_unset.SetCueBanner(_T("請匯入課程"));
	course_loaded = false;
	class_table = new short[65];
	for (int i = 0; i < 65; i++)
		class_table[i] = -1;
	chosen = new std::vector<int>();
	credit = 0;

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFC_FinalProjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFC_FinalProjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC_FinalProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFC_FinalProjDlg::OnBnClickedButtonclock()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CClockMain dlg;
	dlg.DoModal();
}

LRESULT CMFC_FinalProjDlg::rcvfromClockMain(WPARAM wParam, LPARAM lParam)
{     
	// 接收傳過來的結構體
	ClockRetMain* pRcv;
	pRcv = (ClockRetMain*)wParam;

	Rcv.clock_ct = pRcv->clock_ct;
	Rcv.enable_clock_ct = pRcv->enable_clock_ct;
	Rcv.pClkLiveRet = pRcv->pClkLiveRet;
	Rcv.pClkRet = pRcv->pClkRet;
	CString tp;
	tp.Format(L"%d", Rcv.enable_clock_ct);
	m_st_clockct.SetWindowTextW(tp);


	for (int i=0; i<Rcv.enable_clock_ct; i++) {
		use[i].hr = Rcv.pClkLiveRet[i].hr;
		use[i].min = Rcv.pClkLiveRet[i].min;
		use[i].sec = Rcv.pClkLiveRet[i].sec;
		use[i].path = Rcv.pClkLiveRet[i].path;
		use[i].cycle = Rcv.pClkLiveRet[i].cycle;
		use[i].check = false;
	}
	clock_ct = Rcv.enable_clock_ct;

	nowtime = CTime::GetCurrentTime();
	int nowhr, nowmin, nowsec, smlestabs=2147483647, thisabs, smlestid=-1;
	nowhr = nowtime.GetHour();
	nowmin = nowtime.GetMinute();
	nowsec = nowtime.GetSecond();
	nowsec += nowhr*3600 + nowmin*60;
	for (int i=0; i<Rcv.enable_clock_ct; i++) {
		thisabs = _wtoi(use[i].hr)*3600 + _wtoi(use[i].min)*60 + _wtoi(use[i].sec) - nowsec;
		if (thisabs < 0)
			thisabs += 86400;
		smlestabs = min(thisabs, smlestabs);
		if (smlestabs == thisabs)
			smlestid = i;
	}
	if (smlestid != -1) {
		settimeid = smlestid;
		settimestr = use[smlestid].hr + ":" + use[smlestid].min + ":" + use[smlestid].sec;
		settimepath = use[smlestid].path;
		m_st_nextclock.SetWindowTextW(settimestr);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_NEXTCLOCK)->ShowWindow(SW_SHOW);
	}
	else {
		settimeid = -1;
		settimestr = "";
		settimepath = "";
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NEXTCLOCK)->ShowWindow(SW_HIDE);
	}

	//把所有的記錄save到data.txt
	//if (Rcv.clock_ct != 0) //有資料再寫入
	//{
		FILE *fStream;
		errno_t e = _tfopen_s(&fStream, _T("\data.txt"), _T("wt,ccs=UNICODE"));
		if (e == 0) 
		{
			CStdioFile myFile(fStream);  // open the file from this stream
			CString tp1, tp2, tp3, tp4, tp5, tp6, tp;
			tp1.Format (L"\n%d\n", Rcv.clock_ct);		//count
			myFile.WriteString(tp1);
			for (int i=0; i<Rcv.clock_ct; i++)
			{
				tp1 = Rcv.pClkRet[i].hr;				//hour
				tp2 = Rcv.pClkRet[i].min;				//min
				tp3 = Rcv.pClkRet[i].sec;				//ini
				tp4 = Rcv.pClkRet[i].path;				//path
				if (Rcv.pClkRet[i].check)
					tp5 = L"1";
				else
					tp5 = L"0";
				if (Rcv.pClkRet[i].cycle)
					tp6 = L"是";
				else
					tp6 = L"否";
				tp = (tp1 + L"\t" + tp2 + L"\t" + tp3 + L"\t" + tp4 + L"\t" + tp5 + L"\t" + tp6 + L"\n");
				myFile.WriteString(tp);
			}
			myFile.Close();

		}
	//}
	return LRESULT();
}

void CMFC_FinalProjDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	if (nIDEvent == 1)											//鬧鐘timer
	{
		CTime now = CTime::GetCurrentTime();
		CString nowstr, msgboxstr;
		int nowhr, nowmin, nowsec, allsec;
		nowhr = now.GetHour();
		nowmin = now.GetMinute();
		nowsec = now.GetSecond();
		nowstr.Format(L"%d%d:%d%d:%d%d", nowhr/10, nowhr%10, nowmin/10, nowmin%10, nowsec/10, nowsec%10);
		m_st_nowtime.SetWindowTextW(nowstr);
		msgboxstr = L"現在時間是" + nowstr + L"，時間到囉!";
		if (nowstr == settimestr)
		{
			//TRACE("settimeid = %d\n", settimeid);
			mymci= new CMCI(use[settimeid].path, L"MPEGAudio");
			mymci->Play(0, 500, use[settimeid].cycle);

			if (MessageBox(msgboxstr, L"鬧鐘", MB_ICONINFORMATION | MB_OK) == IDOK)
			{
				mymci->Close();
				isused[settimeid] = true;
				now = CTime::GetCurrentTime();
				nowhr = now.GetHour();
				nowmin = now.GetMinute();
				nowsec = now.GetSecond();
				allsec = nowhr*3600 + nowmin*60 + nowsec;
				if (clock_ct != 0)
				{
					int thisabs, smlestabs=2147483647, smlestid=-1, i;
					for (i=0; i<clock_ct; i++)
					{
						int a, b, c;
						a = _wtoi(use[i].hr)*3600;
						b = _wtoi(use[i].min)*60;
						c = _wtoi(use[i].sec);
						thisabs = a + b + c - allsec;
						if (thisabs < 0)		//隔天
							thisabs += 86400;
						smlestabs = min(thisabs, smlestabs);
						if (smlestabs == thisabs)
							smlestid = i;
					}
					if (smlestid != -1)
					{
						settimeid = smlestid;
						settimestr = use[settimeid].hr + ":" + use[settimeid].min + ":" + use[settimeid].sec;
						settimepath = use[settimeid].path;
						m_st_nextclock.SetWindowTextW(settimestr);
					}
					else
					{
						settimeid = -1;
						settimestr = "";
						settimepath = "";
						GetDlgItem(IDC_STATIC_NEXTCLOCK)->ShowWindow(SW_HIDE);
						GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
					}
				}
			}
		}
	}

	if (nIDEvent == 2)						//倒數計時timer
	{
		int sec, min, hr;
		CString tp;
		sec = _wtoi(CountDownData[2]);
		min = _wtoi(CountDownData[1]);
		hr = _wtoi(CountDownData[0]);
		sec--;
		if (sec == -1) {
			min--;
			sec = 59;
		}
		if (min == -1 && hr >= 1) {
			hr--;
			min = 59;
		}
		tp.Format(L"%d%d:%d%d:%d%d", hr/10, hr%10, min/10, min%10, sec/10, sec%10);
		CountDownData[0].Format(L"%d", hr);
		CountDownData[1].Format(L"%d", min);
		CountDownData[2].Format(L"%d", sec);

		tp = L"剩餘時間: " + tp;
		m_st_timertext.SetWindowTextW(tp);
		if (sec == 0 && min == 0 && hr == 0)
		{
			KillTimer(2);
			mymci2= new CMCI(CountDownData[3], L"MPEGAudio");
			if (CountDownData[4] == L"是")
				mymci2->Play(0, 500, true);
			else
				mymci2->Play(0, 500, false);
			CString msgboxstr = L"倒數計時已經結束囉!";
			if (MessageBox(msgboxstr, L"倒數計時器", MB_ICONINFORMATION | MB_OK) == IDOK)
			{
				mymci2->Close();
				CString tp;
				m_but_playpause.GetWindowTextW(tp);
				if (tp == L"||")
				{
					tp = L"▶ / ||";
					m_but_playpause.SetWindowTextW(tp);
				}
				CountDownData[0] = CountDownData[1] = CountDownData[2] = CountDownData[3] = "";
				m_st_timertext.SetWindowTextW(L"倒數計時器未設定！");
				GetDlgItem(IDC_BUTTON_PLAYPAUSE)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_BUTTONSTOP)->ShowWindow(SW_HIDE);

			}
		}
	}

	if (nIDEvent == 3)					//碼表timer
	{
		int hr, min, sec;
		CString tp;
		hr = _wtoi(stopwatch[0]);
		min = _wtoi(stopwatch[1]);
		sec = _wtoi(stopwatch[2]);
		sec++;
		if (sec == 60) {
			sec = 0;
			min++;
		}
		if (min == 60) {
			min = 0;
			hr++;
		}
		tp.Format(L"%d%d:%d%d:%d%d", hr/10, hr%10, min/10, min%10, sec/10, sec%10);
		m_st_stopwatch.SetWindowTextW(tp);
		stopwatch[0].Format(L"%d", hr);
		stopwatch[1].Format(L"%d", min);
		stopwatch[2].Format(L"%d", sec);;
	}

	if (nIDEvent == 4)								//定時關機timer
	{
		CTime now = CTime::GetCurrentTime();
		CString nowstr;
		int nowhr, nowmin, nowsec, nowallsec;
		int sethr, setmin, setsec, setallsec;
		nowhr = now.GetHour();
		nowmin = now.GetMinute();
		nowsec = now.GetSecond();
		nowallsec = nowhr*3600 + nowmin*60 + nowsec;

		sethr = _wtoi(rcv.clock.hr);
		setmin = _wtoi(rcv.clock.min);
		setsec = _wtoi(rcv.clock.sec);
		setallsec = sethr*3600 + setmin*60 + setsec;

		int minus = setallsec-nowallsec;
		if (minus < 0)
			minus += 86400;

		if (minus <= 60 && rcv.rebootflag == false)
		{ //剩下1min內發視窗警告
			ShutdownSystem(L"本電腦即將在1分鐘內「關機」，請將尚未儲存的文件盡快儲存，以免遺失。", rcv.rebootflag); 
		}
		else if (minus <= 60 && rcv.rebootflag == true)
		{
			ShutdownSystem(L"本電腦即將在1分鐘內「重新開機」，請將尚未儲存的文件盡快儲存，以免遺失。", rcv.rebootflag); 
		}
	}

}


void CMFC_FinalProjDlg::OnBnClickedButtoncountdown()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CCountDown dlg;
	dlg.DoModal();
}

LRESULT CMFC_FinalProjDlg::rcvfromCountDown(WPARAM wParam, LPARAM lParam) {
	// 接受到訊息後的工作
	// do something

	// 接收傳過來的結構體
	CString* pRcv;
	pRcv = (CString*)wParam;

	// 取值

	CountDownData[0] = pRcv[0];
	CountDownData[1] = pRcv[1];
	CountDownData[2] = pRcv[2];
	CountDownData[3] = pRcv[3];
	CountDownData[4] = pRcv[4];

	CString tp = CountDownData[0] + L":" + CountDownData[1] + L":" + CountDownData[2];
	if (tp == "00:00:00") {
		tp = "24:00:00";
		CountDownData[0] = "24";
	}
	tp = L"剩餘時間: " + tp;
	m_st_timertext.SetWindowTextW(tp);
	GetDlgItem(IDC_BUTTON_PLAYPAUSE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTONSTOP)->ShowWindow(SW_SHOW);

	return LRESULT();
}

void CMFC_FinalProjDlg::OnBnClickedButtonPlaypause()
{
	CString tp;
	m_but_playpause.GetWindowTextW(tp);
	if (tp == L"▶ / ||" || tp == L"▶")		//第一次按->開始
	{
		tp = L"||";
		m_but_playpause.SetWindowTextW(tp);
		SetTimer(2, 1000, NULL);
	}
	else if (tp == L"||")					//停止狀態
	{
		tp = L"▶";
		m_but_playpause.SetWindowTextW(tp);
		KillTimer(2);
	}
}

void CMFC_FinalProjDlg::OnBnClickedButtonstop()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString tp;
	m_but_playpause.GetWindowTextW(tp);
	if (tp == L"||")
	{
		tp = L"▶ / ||";
		m_but_playpause.SetWindowTextW(tp);
	}
	CountDownData[0] = CountDownData[1] = CountDownData[2] = CountDownData[3] = "";
	m_st_timertext.SetWindowTextW(L"倒數計時器未設定！");
	GetDlgItem(IDC_BUTTON_PLAYPAUSE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTONSTOP)->ShowWindow(SW_HIDE);
	KillTimer(2);
}


/******************************************************************************************/


void CMFC_FinalProjDlg::OnBnClickedButtonStopwatch()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	stopwatchflag = !stopwatchflag;
	CString tp;
	if (stopwatchflag) {	//start
		tp = L"▶ / ||";
		m_st_stopwatch.SetWindowTextW(L"00:00:00");
		m_stopwatch_playpause.SetWindowTextW(tp);
		stopwatch[0] = stopwatch[1] = stopwatch[2] = "00";
		GetDlgItem(IDC_STATIC_STOPWATCH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_PLAYPAUSE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTONCLEAR)->ShowWindow(SW_SHOW);
	}
	else {					//end
		tp = L"▶ / ||";
		m_st_stopwatch.SetWindowTextW(L"00:00:00");
		stopwatch[0] = stopwatch[1] = stopwatch[2] = stopwatch[3] = "";
		
		GetDlgItem(IDC_STATIC_STOPWATCH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_PLAYPAUSE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTONCLEAR)->ShowWindow(SW_HIDE);
		KillTimer(3);
	}
	
}

void CMFC_FinalProjDlg::OnBnClickedButtonPlaypause2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString tp;
	m_stopwatch_playpause.GetWindowTextW(tp);
	if (tp == L"▶ / ||" || tp == L"▶") { //第一次按->開始
		tp = L"||";
		m_stopwatch_playpause.SetWindowTextW(tp);
		SetTimer (3, 1000, NULL);
	}
	else if (tp == L"||") { //停止狀態
		tp = L"▶";
		m_stopwatch_playpause.SetWindowTextW(tp);
		KillTimer(3);
	}
}

void CMFC_FinalProjDlg::OnBnClickedButtonclear()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CString tp;
	m_stopwatch_playpause.GetWindowTextW(tp);
	if (tp == L"||")
	{
		tp = L"▶ / ||";
		m_stopwatch_playpause.SetWindowTextW(tp);
	}
	m_st_stopwatch.SetWindowTextW(L"00:00:00");
	stopwatch[0] = stopwatch[1] = stopwatch[2] = "00";
	KillTimer(3);
}


/******************************************************************************************/


void CMFC_FinalProjDlg::OnBnClickedButtonshutdown()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CShutDown dlg;
	dlg.DoModal();
}

LRESULT CMFC_FinalProjDlg::rcvfromShutDown(WPARAM wParam, LPARAM lParam)
{
    // 接受到訊息後的工作
    // do something

    // 接收傳過來的結構體
	ShutDownStruct* pDs;
    pDs = (ShutDownStruct*)wParam;
    // 取值
	rcv.rebootflag = pDs->rebootflag;
	rcv.clock.hr = pDs->clock.hr;
	rcv.clock.min = pDs->clock.min;
	rcv.clock.sec = pDs->clock.sec;
	CString tp = rcv.clock.hr + L":" + rcv.clock.min + L":" + rcv.clock.sec;
	if (rcv.rebootflag == true)
		tp = L"重開機時間: " + tp;
	else
		tp = L"關機時間: " + tp;
	m_st_shutdowntext.SetWindowTextW(tp);
	GetDlgItem(IDC_BUTTON_STOPSHUTDOWN)->ShowWindow(SW_SHOW);

	SetTimer(4, 1000, NULL);

    return LRESULT();
}

void CMFC_FinalProjDlg::OnBnClickedButtonStopshutdown()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	if (AbortSystemShutdown(NULL)) {
		m_st_shutdowntext.SetWindowTextW(L"定時關機未設定！");
		GetDlgItem(IDC_BUTTON_STOPSHUTDOWN)->ShowWindow(SW_HIDE);
		KillTimer(4);
	}
	else {
		TRACE ("Failed to abort\n");
	}
}

/*** CoursePicking Part ***********************************************************************/

void CMFC_FinalProjDlg::import()
{
	try{
		CFileDialog FileDlg(TRUE, CString(".json"), NULL, OFN_HIDEREADONLY,CString(_T("JSON Files (*.json)|*.json|")));
		CString fname;
		if (FileDlg.DoModal() == IDOK)  
		{  
			fname = FileDlg.GetPathName();
			ifstream in(fname);

			if(in.fail())
				throw new CString(_T("File open failed！"));

			Json::Reader reader;
			Json::Features::all();

			if(!reader.parse(in,JsonValue,false))
				throw new CString("Json File not valid!");

			in.close();

			if(!JsonValue.isObject())
				throw new CString("Json not valid!");

			Json::Value rootV = JsonValue["course"];
			if(!rootV.isArray())
				throw new CString("Json not valid!");
			courses = new vector<Course*>();

			int err_cnt = 0,OK_cnt = 0,loaded;
			for (int i = 0; i < rootV.size(); i++){
				try{
					courses->push_back(new Course(&rootV[i]));
					OK_cnt++;
				}catch(CString* msg){
					err_cnt++;
				}
			}

			for (int i = 0; i < courses->size(); i++)
				(*courses)[i]->to_combobox(&m_com_addclass);

			m_com_addclass.SetCueBanner(_T("從這裡選擇要加入的課程"));
			m_com_unset.SetCueBanner(_T("按我觀看已選取的課程清單，選取之可清除"));
			m_btn_import_save.SetWindowTextW(_T("儲存選課狀態"));
			Course::set_list_head(&m_list_classtable);
			
			course_loaded = true;
			CString import_report,load_report;
			import_report.Format(_T("成功匯入 %d 筆課程, %d 筆失敗"),OK_cnt,err_cnt);

			rootV = JsonValue["chosen"];
			if(rootV.isArray()){
				loaded = 0;
				for (int i = 0; i < rootV.size(); i++){
					if(!rootV[i].isInt())
						break;
					add_class(rootV[i].asInt());
					loaded++;
				}
				load_report.Format(_T("\n%d 筆之前的選課紀錄已讀取"),loaded);
				import_report += load_report;
			}
				
			AfxMessageBox(import_report);
		}
	}catch(CString* msg){
		AfxMessageBox(*msg);
	}
}

void CMFC_FinalProjDlg::OnCbnDropdownAddClass()
{
	if(!course_loaded)
		import();
}

void CMFC_FinalProjDlg::OnNMClickClassTable(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(!course_loaded){
		import();
		return;
	}
	CString msg = _T("課程代碼 > 課程名稱 列表：\n");
	for (int i = 0; i < chosen->size(); i++)
		msg += (*courses)[(*chosen)[i]]->toCodeStr() + _T("\n");
	AfxMessageBox(msg);
}

void CMFC_FinalProjDlg::add_class(int cho)
{
	(*courses)[cho]->to_list(&m_list_classtable,class_table,cho);
	(*courses)[cho]->to_combobox(&m_com_unset);
	chosen->push_back(cho);
	credit += (*courses)[cho]->credits;
	update();
}

void CMFC_FinalProjDlg::OnCbnSelchangeAddClass()
{
	int cho = m_com_addclass.GetCount() - m_com_addclass.GetCurSel() -1;
	try{
		CString msg = (*courses)[cho]->toString() + _T("\n要加入課表嗎？");
		ConfirmBox Dlg(&msg);
		if (Dlg.DoModal() == IDOK){
			add_class(cho);
		}
	}catch(CString* msg){
		AfxMessageBox(*msg);
	}
	m_com_addclass.SetCurSel(-1);
}


void CMFC_FinalProjDlg::OnCbnSelchangeUnset()
{
	int selection = m_com_unset.GetCurSel();
	int cho = m_com_unset.GetCount() - m_com_unset.GetCurSel() -1;
	int r_index = (*chosen)[cho];
	try{
		CString msg = (*courses)[r_index]->toString() + _T("\n要從課表中移除嗎？");
		ConfirmBox Dlg(&msg);
		if (Dlg.DoModal() == IDOK){
			(*courses)[r_index]->to_list(&m_list_classtable,class_table,r_index,true);
			m_com_unset.DeleteString(selection);
			chosen->erase(chosen->begin() + cho,chosen->begin() + cho + 1);
			credit -= (*courses)[r_index]->credits;
			update();
		}
	}catch(CString* msg){
		AfxMessageBox(*msg);
	}
	m_com_unset.SetCurSel(-1);
}


void CMFC_FinalProjDlg::OnCbnDropdownUnset()
{
	if(!course_loaded)
		import();
}

void CMFC_FinalProjDlg::update()
{
	CString msg;
	msg.Format(_T("選課小幫手，目前學分數：%d"),credit);
	this->SetWindowTextW(msg);
}

void CMFC_FinalProjDlg::OnBnClickedImportSave()
{
	if(!course_loaded){
		import();
		return;
	}

	try{
		CFileDialog FileDlg(FALSE, CString(".json"), NULL, OFN_HIDEREADONLY,CString(_T("JSON Files (*.json)|*.json|")));
		CString fname;
		if (FileDlg.DoModal() == IDOK)  
		{  
			fname = FileDlg.GetPathName();

			Json::StyledStreamWriter* jwritter = new Json::StyledStreamWriter();
			Json::Features::all();

			Json::Value* vec = new Json::Value(Json::arrayValue);
			for (int i = 0; i < chosen->size(); i++)
				vec->append((*chosen)[i]);

			JsonValue["chosen"] = *vec;

			ofstream out(fname);

			if(out.fail())
				throw new CString(_T("File open failed！"));

			jwritter->write(out,JsonValue);

			if(out.fail())
				throw new CString(_T("File save failed！"));

			out.close();

			AfxMessageBox(_T("存檔成功！"));
		}
	}catch(CString* msg){
		AfxMessageBox(*msg);
	}
}

/***************************
FinalProj_Team_8 1/16
4101056017 資工三 邱冠喻 Chiu Guan-Yu
4101040018 資工三 王建舜 Wang Jian-Shun
***************************/
