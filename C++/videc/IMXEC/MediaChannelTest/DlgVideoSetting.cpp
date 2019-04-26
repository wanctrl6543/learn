// DlgVideoSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MediaChannelTest.h"
#include "DlgVideoSetting.h"


// DlgVideoSetting 对话框

IMPLEMENT_DYNAMIC(DlgVideoSetting, CDialog)

DlgVideoSetting::DlgVideoSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVideoSetting::IDD, pParent)
{
	m_nDevID=1;
	m_VideoCodecType=VIDEC_CODEC_H264;
	m_nFrameRate=30;
	m_nBitrate=1024;
	
	m_nWidth=1920;
	m_nHeight=1080;
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
	DDX_Control(pDX, IDC_COMBO_CODEC, m_cbxCodec);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_cbxFormat);
}


BEGIN_MESSAGE_MAP(DlgVideoSetting, CDialog)
	ON_BN_CLICKED(IDOK, &DlgVideoSetting::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV, &DlgVideoSetting::OnCbnSelchangeComboDev)
END_MESSAGE_MAP()


// DlgVideoSetting 消息处理程序

void DlgVideoSetting::OnBnClickedOk()
{
	int nIndex=0;

	nIndex=m_cbxCodec.GetCurSel();
	m_VideoCodecType=(VIDEC_CODEC_TYPE)m_cbxCodec.GetItemData(nIndex);

	nIndex=m_cbxFrameRate.GetCurSel();
	m_nFrameRate=(int)m_cbxFrameRate.GetItemData(nIndex);

	nIndex=m_cbxBitrate.GetCurSel();
	m_nBitrate=(int)m_cbxBitrate.GetItemData(nIndex);

	m_nDevID=m_cbxDev.GetCurSel();
	nIndex=m_cbxFormat.GetCurSel();
	VIDEC_DEV_TYPE nDevType=VIDEC_DEV_SD;
	IMXEC_CapChanDev::GetDevType(m_nDevID,nDevType);
	IMXEC_CapChanDev::GetFormatSize(nDevType,nIndex,m_nWidth,m_nHeight);

	OnOK();
}

BOOL DlgVideoSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIndex=0;

	nIndex=m_cbxCodec.AddString("H263");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263);
	nIndex=m_cbxCodec.AddString("H263+");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263P);
	nIndex=m_cbxCodec.AddString("H263++");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263PP);
	nIndex=m_cbxCodec.AddString("H264");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H264);
	nIndex=m_cbxCodec.AddString("H264 SVC");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H264_SVC);
	for (nIndex=0;nIndex<m_cbxCodec.GetCount();nIndex++)
	{
		VIDEC_CODEC_TYPE VideoCodecType=(VIDEC_CODEC_TYPE)m_cbxCodec.GetItemData(nIndex);
		if (VideoCodecType==m_VideoCodecType)
		{
			m_cbxCodec.SetCurSel(nIndex);
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
	nIndex=m_cbxFrameRate.AddString("60");
	m_cbxFrameRate.SetItemData(nIndex,60);
	if (m_nFrameRate<=1)
		m_nFrameRate=1;
	else if (m_nFrameRate<=5)
		m_nFrameRate=5;
	else if (m_nFrameRate<=10)
		m_nFrameRate=10;
	else if (m_nFrameRate<=15)
		m_nFrameRate=15;
	else if (m_nFrameRate<=30)
		m_nFrameRate=30;
	else 
		m_nFrameRate=60;
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
	int nDevCount=IMXEC_CapChanDev::GetDevCount();
	for (int i=0;i<nDevCount;i++)
	{
		if (IMXEC_CapChanDev::GetDevName(i,szDevName,127)<0)
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

	FillFormat();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void DlgVideoSetting::FillFormat(void)
{
	m_cbxFormat.ResetContent();
	m_nDevID=m_cbxDev.GetCurSel();

	VIDEC_DEV_TYPE nDevType=VIDEC_DEV_SD;
	IMXEC_CapChanDev::GetDevType(m_nDevID,nDevType);
	
	char szFormatName[128]="";

	int nFormatCount=IMXEC_CapChanDev::GetFormatCount(nDevType);
	int i=0;
	for (i=0;i<nFormatCount;++i)
	{
		if (IMXEC_CapChanDev::GetFormatName(nDevType,i,szFormatName,127)<0)
		{
			break;
		}
		m_cbxFormat.AddString(szFormatName);
	}

	int nFormatIndex=0;
	for (i=0;i<nFormatCount;++i)
	{
		int nWidth=0;
		int nHeight=0;
		if (IMXEC_CapChanDev::GetFormatSize(nDevType,i,nWidth,nHeight)<0)
		{
			break;
		}
		
		if (nWidth>m_nWidth || nHeight>m_nHeight)
		{
			break;
		}
		nFormatIndex=i;
	}
	m_cbxFormat.SetCurSel(nFormatIndex);
}

void DlgVideoSetting::OnCbnSelchangeComboDev()
{
	FillFormat();
}
