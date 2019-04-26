// DlgVideoSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "AVCONCallTest.h"
#include "DlgVideoSetting.h"


// DlgVideoSetting 对话框

IMPLEMENT_DYNAMIC(DlgVideoSetting, CDialog)

DlgVideoSetting::DlgVideoSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVideoSetting::IDD, pParent)
{
	m_nDevID=0;
	m_nFrameRate=15;
	m_nBitrate=384;
	m_nVideoFormatType=IMXEC_AVCONCall::VF_CIF;
}

DlgVideoSetting::~DlgVideoSetting()
{
}

void DlgVideoSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEV, m_cbxDev);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_cbxFrameRate);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_cbxBitrate);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_cbxFormat);
}


BEGIN_MESSAGE_MAP(DlgVideoSetting, CDialog)
	ON_BN_CLICKED(IDOK, &DlgVideoSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgVideoSetting 消息处理程序

void DlgVideoSetting::OnBnClickedOk()
{
	int nIndex=0;
	nIndex=m_cbxFormat.GetCurSel();
	m_nVideoFormatType=(IMXEC_AVCONCall::VIDEO_FORMAT)m_cbxFormat.GetItemData(nIndex);

	nIndex=m_cbxFrameRate.GetCurSel();
	m_nFrameRate=(int)m_cbxFrameRate.GetItemData(nIndex);

	nIndex=m_cbxBitrate.GetCurSel();
	m_nBitrate=(int)m_cbxBitrate.GetItemData(nIndex);

	m_nDevID=m_cbxDev.GetCurSel();

	OnOK();
}

BOOL DlgVideoSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIndex=0;
	nIndex=m_cbxFormat.AddString("QCIF ( 176 X 144 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_QCIF);

	nIndex=m_cbxFormat.AddString("QVGA ( 320 X 240 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_QVGA);

	nIndex=m_cbxFormat.AddString("CIF ( 352 X 288 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_CIF);

	nIndex=m_cbxFormat.AddString("VGA ( 640 X 480 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_VGA);

	nIndex=m_cbxFormat.AddString("4CIF ( 704 X 576 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_4CIF);

	nIndex=m_cbxFormat.AddString("720P ( 1280 X 720 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_720P);

	nIndex=m_cbxFormat.AddString("1080I ( 1920 X 540 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_1080I);

	nIndex=m_cbxFormat.AddString("1080P ( 1920 X 1080 )");
	m_cbxFormat.SetItemData(nIndex,IMXEC_AVCONCall::VF_1080P);

	for (nIndex=0;nIndex<m_cbxFormat.GetCount();nIndex++)
	{
		IMXEC_AVCONCall::VIDEO_FORMAT nVideoFormatType=(IMXEC_AVCONCall::VIDEO_FORMAT)m_cbxFormat.GetItemData(nIndex);
		if (nVideoFormatType==m_nVideoFormatType)
		{
			m_cbxFormat.SetCurSel(nIndex);
			break;
		}
	}

	nIndex=m_cbxFrameRate.AddString("1");
	m_cbxFrameRate.SetItemData(nIndex,1);
	nIndex=m_cbxFrameRate.AddString("5");
	m_cbxFrameRate.SetItemData(nIndex,5);
	nIndex=m_cbxFrameRate.AddString("10");
	m_cbxFrameRate.SetItemData(nIndex,10);
	nIndex=m_cbxFrameRate.AddString("15");
	m_cbxFrameRate.SetItemData(nIndex,15);
	nIndex=m_cbxFrameRate.AddString("30");
	m_cbxFrameRate.SetItemData(nIndex,30);
	if (m_nFrameRate<=1)
		m_nFrameRate=1;
	else if (m_nFrameRate<=5)
		m_nFrameRate=5;
	else if (m_nFrameRate<=10)
		m_nFrameRate=10;
	else if (m_nFrameRate<=15)
		m_nFrameRate=15;
	else 
		m_nFrameRate=30;
	for (nIndex=0;nIndex<m_cbxFrameRate.GetCount();nIndex++)
	{
		int nFrameRate=(int)m_cbxFrameRate.GetItemData(nIndex);
		if (nFrameRate==m_nFrameRate)
		{
			m_cbxFrameRate.SetCurSel(nIndex);
			break;
		}
	}

	char szDevName[128]="";
	int nDevCount=IMXEC_AVCONCall::GetVideoDevCount();
	for (int i=0;i<nDevCount;i++)
	{
		if (IMXEC_AVCONCall::GetVideoDevName(i,szDevName,127)<0)
		{
			break;
		}
		m_cbxDev.AddString(szDevName);
	}
	m_cbxDev.SetCurSel(m_nDevID);

	nIndex=m_cbxBitrate.AddString("32");
	m_cbxBitrate.SetItemData(nIndex,32);
	nIndex=m_cbxBitrate.AddString("64");
	m_cbxBitrate.SetItemData(nIndex,64);
	nIndex=m_cbxBitrate.AddString("128");
	m_cbxBitrate.SetItemData(nIndex,128);
	nIndex=m_cbxBitrate.AddString("256");
	m_cbxBitrate.SetItemData(nIndex,256);
	nIndex=m_cbxBitrate.AddString("384");
	m_cbxBitrate.SetItemData(nIndex,384);
	nIndex=m_cbxBitrate.AddString("512");
	m_cbxBitrate.SetItemData(nIndex,512);
	nIndex=m_cbxBitrate.AddString("768");
	m_cbxBitrate.SetItemData(nIndex,768);
	nIndex=m_cbxBitrate.AddString("1024");
	m_cbxBitrate.SetItemData(nIndex,1024);
	nIndex=m_cbxBitrate.AddString("1536");
	m_cbxBitrate.SetItemData(nIndex,1536);
	nIndex=m_cbxBitrate.AddString("2048");
	m_cbxBitrate.SetItemData(nIndex,2048);
	nIndex=m_cbxBitrate.AddString("3072");
	m_cbxBitrate.SetItemData(nIndex,3072);
	nIndex=m_cbxBitrate.AddString("4096");
	m_cbxBitrate.SetItemData(nIndex,4096);
	nIndex=m_cbxBitrate.AddString("6144");
	m_cbxBitrate.SetItemData(nIndex,6144);
	if (m_nBitrate<=32)
		m_nBitrate=32;
	else if (m_nBitrate<=64)
		m_nBitrate=64;
	else if (m_nBitrate<=128)
		m_nBitrate=128;
	else if (m_nBitrate<=256)
		m_nBitrate=256;
	else if (m_nBitrate<=384)
		m_nBitrate=384;
	else if (m_nBitrate<=512)
		m_nBitrate=512;
	else if (m_nBitrate<=768)
		m_nBitrate=768;
	else if (m_nBitrate<=1024)
		m_nBitrate=1024;
	else if (m_nBitrate<=1536)
		m_nBitrate=1536;
	else if (m_nBitrate<=2048)
		m_nBitrate=2048;
	else if (m_nBitrate<=3072)
		m_nBitrate=3072;
	else if (m_nBitrate<=4096)
		m_nBitrate=4096;
	else if (m_nBitrate<=1536)
		m_nBitrate=1536;
	else 
		m_nBitrate=6144;
	for (nIndex=0;nIndex<m_cbxBitrate.GetCount();nIndex++)
	{
		int nBitrate=(int)m_cbxBitrate.GetItemData(nIndex);
		if (nBitrate==m_nBitrate)
		{
			m_cbxBitrate.SetCurSel(nIndex);
			break;
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
}
