// ConfirmBox.cpp : 實作檔
//

#include "stdafx.h"
#include "MFC_FinalProj.h"
#include "ConfirmBox.h"
#include "afxdialogex.h"


// ConfirmBox 對話方塊

IMPLEMENT_DYNAMIC(ConfirmBox, CDialogEx)

ConfirmBox::ConfirmBox(CString* msg,CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfirmBox::IDD, pParent)
{
	this->msg = msg;
}

ConfirmBox::~ConfirmBox()
{
}

void ConfirmBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONFIRM_MSG, m_text_msg);

	m_text_msg.SetWindowTextW(*msg);
}


BEGIN_MESSAGE_MAP(ConfirmBox, CDialogEx)
END_MESSAGE_MAP()


// ConfirmBox 訊息處理常式
