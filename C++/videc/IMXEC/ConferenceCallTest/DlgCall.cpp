// DlgCall.cpp : 实现文件
//

#include "stdafx.h"
#include "ConferenceCallTest.h"
#include "DlgCall.h"


// DlgCall 对话框

IMPLEMENT_DYNAMIC(DlgCall, CDialog)

DlgCall::DlgCall(CWnd* pParent /*=NULL*/)
	: CDialog(DlgCall::IDD, pParent)
	, m_strPeerIP(_T(""))
	, m_strProto(_T(""))
{

}

DlgCall::~DlgCall()
{
}

void DlgCall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PEER_IP, m_strPeerIP);
	DDV_MaxChars(pDX, m_strPeerIP, 32);
	DDX_Control(pDX, IDC_COMBO_PROTO, m_cbxProto);
	DDX_CBString(pDX, IDC_COMBO_PROTO, m_strProto);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_EDIT_PEER_IP, m_editPeerIP);
}


BEGIN_MESSAGE_MAP(DlgCall, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PEER_IP, &DlgCall::OnEnChangeEditPeerIp)
END_MESSAGE_MAP()


// DlgCall 消息处理程序

void DlgCall::OnEnChangeEditPeerIp()
{
	CString strPeerIP="";
	m_editPeerIP.GetWindowTextA(strPeerIP);
	m_btnOK.EnableWindow(strPeerIP.GetLength());
}

BOOL DlgCall::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_btnOK.EnableWindow(m_strPeerIP.GetLength());

#ifdef HAS_H323 //#endif
	m_cbxProto.AddString("IMX");
	m_cbxProto.AddString("H323");
#endif

	m_cbxProto.AddString("SIP");
	m_cbxProto.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
}
