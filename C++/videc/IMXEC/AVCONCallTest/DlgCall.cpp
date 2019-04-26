// DlgCall.cpp : 实现文件
//

#include "stdafx.h"
#include "AVCONCallTest.h"
#include "DlgCall.h"


// DlgCall 对话框

IMPLEMENT_DYNAMIC(DlgCall, CDialog)

DlgCall::DlgCall(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCall::IDD, pParent)
	, m_strUserID(_T(""))
{

}

DlgCall::~DlgCall()
{
}

void DlgCall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERID, m_strUserID);
	DDV_MaxChars(pDX, m_strUserID, 16);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_EDIT_USERID, m_editUserID);
}


BEGIN_MESSAGE_MAP(DlgCall, CDialog)
	ON_EN_CHANGE(IDC_EDIT_USERID, &DlgCall::OnEnChangeEditUserID)
END_MESSAGE_MAP()


// DlgCall 消息处理程序

void DlgCall::OnEnChangeEditUserID()
{
	CString strUserID="";
	m_editUserID.GetWindowText(strUserID);
	m_btnOK.EnableWindow(strUserID.GetLength());
}

BOOL DlgCall::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnOK.EnableWindow(m_strUserID.GetLength());


	return TRUE;  // return TRUE unless you set the focus to a control
}
