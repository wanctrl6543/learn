// DlgVideoSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "ConferenceCallTest.h"
#include "DlgVideoSetting.h"


// DlgVideoSetting 对话框

IMPLEMENT_DYNAMIC(DlgVideoSetting, CDialog)

DlgVideoSetting::DlgVideoSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgVideoSetting::IDD, pParent)
{
	m_nDevID=0;
	m_VideoCodecType=VIDEC_CODEC_H264;
	m_nFrameRate=15;
	m_nBitrate=384;
	m_VideoFormatType=VIDEO_FORMAT_CIF;

	m_nSecondDevID=0;
	m_SecondVideoCodecType=VIDEC_CODEC_H264;
	m_nSecondFrameRate=15;
	m_nSecondBitrate=384;
	m_SecondVideoFormatType=VIDEO_FORMAT_CIF;
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
	DDX_Control(pDX, IDC_COMBO_SECOND_DEV, m_cbxSecondDev);
	DDX_Control(pDX, IDC_COMBO_SECOND_FRAMERATE, m_cbxSecondFrameRate);
	DDX_Control(pDX, IDC_COMBO_SECOND_BITRATE, m_cbxSecondBitrate);
	DDX_Control(pDX, IDC_COMBO_SECOND_CODEC, m_cbxSecondCodec);
	DDX_Control(pDX, IDC_COMBO_SECOND_FORMAT, m_cbxSecondFormat);
}


BEGIN_MESSAGE_MAP(DlgVideoSetting, CDialog)
	ON_BN_CLICKED(IDOK, &DlgVideoSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgVideoSetting 消息处理程序

void DlgVideoSetting::OnBnClickedOk()
{
	int nIndex=0;
	nIndex=m_cbxFormat.GetCurSel();
	m_VideoFormatType=(VIDEO_FORMAT_TYPE)m_cbxFormat.GetItemData(nIndex);

	nIndex=m_cbxCodec.GetCurSel();
	m_VideoCodecType=(VIDEC_CODEC_TYPE)m_cbxCodec.GetItemData(nIndex);

	nIndex=m_cbxFrameRate.GetCurSel();
	m_nFrameRate=(int)m_cbxFrameRate.GetItemData(nIndex);

	nIndex=m_cbxBitrate.GetCurSel();
	m_nBitrate=(int)m_cbxBitrate.GetItemData(nIndex);

	m_nDevID=m_cbxDev.GetCurSel();

	nIndex=m_cbxSecondFormat.GetCurSel();
	m_SecondVideoFormatType=(VIDEO_FORMAT_TYPE)m_cbxSecondFormat.GetItemData(nIndex);

	nIndex=m_cbxSecondCodec.GetCurSel();
	m_SecondVideoCodecType=(VIDEC_CODEC_TYPE)m_cbxSecondCodec.GetItemData(nIndex);

	nIndex=m_cbxSecondFrameRate.GetCurSel();
	m_nSecondFrameRate=(int)m_cbxSecondFrameRate.GetItemData(nIndex);

	nIndex=m_cbxSecondBitrate.GetCurSel();
	m_nSecondBitrate=(int)m_cbxSecondBitrate.GetItemData(nIndex);

	m_nSecondDevID=m_cbxSecondDev.GetCurSel();

	OnOK();
}

BOOL DlgVideoSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIndex=0;
	nIndex=m_cbxFormat.AddString("QCIF ( 176 X 144 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_QCIF);
	nIndex=m_cbxFormat.AddString("CIF ( 352 X 288 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_CIF);
	nIndex=m_cbxFormat.AddString("4CIF ( 704 X 576 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_4CIF);
	nIndex=m_cbxFormat.AddString("16CIF ( 1408 X 1152 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_16CIF);
	nIndex=m_cbxFormat.AddString("720I ( 1280 X 360 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_720I);
	nIndex=m_cbxFormat.AddString("720P ( 1280 X 720 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_720P);
	nIndex=m_cbxFormat.AddString("1080I ( 1920 X 540 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_1080I);
	nIndex=m_cbxFormat.AddString("1080P ( 1920 X 1080 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_1080P);
	nIndex=m_cbxFormat.AddString("VGA ( 640 X 480 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_VGA);
	nIndex=m_cbxFormat.AddString("SVGA ( 800 X 600 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_SVGA);
	nIndex=m_cbxFormat.AddString("XVGA ( 1024 X 768 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_XGA);
	nIndex=m_cbxFormat.AddString("SXVGA ( 1280 X 1024 )");
	m_cbxFormat.SetItemData(nIndex,VIDEO_FORMAT_SXGA);
	for (nIndex=0;nIndex<m_cbxFormat.GetCount();nIndex++)
	{
		VIDEO_FORMAT_TYPE VideoFormatType=(VIDEO_FORMAT_TYPE)m_cbxFormat.GetItemData(nIndex);
		if (VideoFormatType==m_VideoFormatType)
		{
			m_cbxFormat.SetCurSel(nIndex);
			break;
		}
	}

	nIndex=m_cbxCodec.AddString("H263");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263);
	nIndex=m_cbxCodec.AddString("H263+");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263P);
	nIndex=m_cbxCodec.AddString("H263++");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H263PP);
	nIndex=m_cbxCodec.AddString("H264");
	m_cbxCodec.SetItemData(nIndex,VIDEC_CODEC_H264);
	nIndex=m_cbxCodec.AddString("H264SVC");
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
	int nDevCount=VIDEC_GetDevCount();
	for (int i=0;i<nDevCount;i++)
	{
		if (VIDEC_GetDevName(i,szDevName,127)<0)
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

	nIndex=m_cbxSecondFormat.AddString("QCIF ( 176 X 144 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_QCIF);
	nIndex=m_cbxSecondFormat.AddString("CIF ( 352 X 288 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_CIF);
	nIndex=m_cbxSecondFormat.AddString("4CIF ( 704 X 576 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_4CIF);
	nIndex=m_cbxSecondFormat.AddString("16CIF ( 1408 X 1152 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_16CIF);
	nIndex=m_cbxSecondFormat.AddString("720I ( 1280 X 360 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_720I);
	nIndex=m_cbxSecondFormat.AddString("720P ( 1280 X 720 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_720P);
	nIndex=m_cbxSecondFormat.AddString("1080I ( 1920 X 540 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_1080I);
	nIndex=m_cbxSecondFormat.AddString("1080P ( 1920 X 1080 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_1080P);
	nIndex=m_cbxSecondFormat.AddString("VGA ( 640 X 480 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_VGA);
	nIndex=m_cbxSecondFormat.AddString("SVGA ( 800 X 600 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_SVGA);
	nIndex=m_cbxSecondFormat.AddString("XVGA ( 1024 X 768 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_XGA);
	nIndex=m_cbxSecondFormat.AddString("SXVGA ( 1280 X 1024 )");
	m_cbxSecondFormat.SetItemData(nIndex,VIDEO_FORMAT_SXGA);
	for (nIndex=0;nIndex<m_cbxSecondFormat.GetCount();nIndex++)
	{
		VIDEO_FORMAT_TYPE VideoFormatType=(VIDEO_FORMAT_TYPE)m_cbxSecondFormat.GetItemData(nIndex);
		if (VideoFormatType==m_SecondVideoFormatType)
		{
			m_cbxSecondFormat.SetCurSel(nIndex);
			break;
		}
	}

	nIndex=m_cbxSecondCodec.AddString("H263");
	m_cbxSecondCodec.SetItemData(nIndex,VIDEC_CODEC_H263);
	nIndex=m_cbxSecondCodec.AddString("H263+");
	m_cbxSecondCodec.SetItemData(nIndex,VIDEC_CODEC_H263P);
	nIndex=m_cbxSecondCodec.AddString("H263++");
	m_cbxSecondCodec.SetItemData(nIndex,VIDEC_CODEC_H263PP);
	nIndex=m_cbxSecondCodec.AddString("H264");
	m_cbxSecondCodec.SetItemData(nIndex,VIDEC_CODEC_H264);
	nIndex=m_cbxSecondCodec.AddString("H264SVC");
	m_cbxSecondCodec.SetItemData(nIndex,VIDEC_CODEC_H264_SVC);
	for (nIndex=0;nIndex<m_cbxSecondCodec.GetCount();nIndex++)
	{
		VIDEC_CODEC_TYPE VideoCodecType=(VIDEC_CODEC_TYPE)m_cbxSecondCodec.GetItemData(nIndex);
		if (VideoCodecType==m_SecondVideoCodecType)
		{
			m_cbxSecondCodec.SetCurSel(nIndex);
			break;
		}
	}

	nIndex=m_cbxSecondFrameRate.AddString("1");
	m_cbxSecondFrameRate.SetItemData(nIndex,1);
	nIndex=m_cbxSecondFrameRate.AddString("5");
	m_cbxSecondFrameRate.SetItemData(nIndex,5);
	nIndex=m_cbxSecondFrameRate.AddString("10");
	m_cbxSecondFrameRate.SetItemData(nIndex,10);
	nIndex=m_cbxSecondFrameRate.AddString("15");
	m_cbxSecondFrameRate.SetItemData(nIndex,15);
	nIndex=m_cbxSecondFrameRate.AddString("30");
	m_cbxSecondFrameRate.SetItemData(nIndex,30);
	nIndex=m_cbxSecondFrameRate.AddString("60");
	m_cbxSecondFrameRate.SetItemData(nIndex,60);
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
	for (nIndex=0;nIndex<m_cbxSecondFrameRate.GetCount();nIndex++)
	{
		int nFrameRate=(int)m_cbxSecondFrameRate.GetItemData(nIndex);
		if (nFrameRate==m_nSecondFrameRate)
		{
			m_cbxSecondFrameRate.SetCurSel(nIndex);
			break;
		}
	}

	//m_cbxSecondDev.AddString("DesktopVideo");
	nDevCount=VIDEC_GetDevCount();
	for (int i=0;i<nDevCount;i++)
	{
		if (VIDEC_GetDevName(i,szDevName,127)<0)
		{
			break;
		}
		m_cbxSecondDev.AddString(szDevName);
	}
	m_cbxSecondDev.SetCurSel(m_nSecondDevID);

	nIndex=m_cbxSecondBitrate.AddString("32");
	m_cbxSecondBitrate.SetItemData(nIndex,32);
	nIndex=m_cbxSecondBitrate.AddString("64");
	m_cbxSecondBitrate.SetItemData(nIndex,64);
	nIndex=m_cbxSecondBitrate.AddString("128");
	m_cbxSecondBitrate.SetItemData(nIndex,128);
	nIndex=m_cbxSecondBitrate.AddString("256");
	m_cbxSecondBitrate.SetItemData(nIndex,256);
	nIndex=m_cbxSecondBitrate.AddString("384");
	m_cbxSecondBitrate.SetItemData(nIndex,384);
	nIndex=m_cbxSecondBitrate.AddString("512");
	m_cbxSecondBitrate.SetItemData(nIndex,512);
	nIndex=m_cbxSecondBitrate.AddString("768");
	m_cbxSecondBitrate.SetItemData(nIndex,768);
	nIndex=m_cbxSecondBitrate.AddString("1024");
	m_cbxSecondBitrate.SetItemData(nIndex,1024);
	nIndex=m_cbxSecondBitrate.AddString("1536");
	m_cbxSecondBitrate.SetItemData(nIndex,1536);
	nIndex=m_cbxSecondBitrate.AddString("2048");
	m_cbxSecondBitrate.SetItemData(nIndex,2048);
	nIndex=m_cbxSecondBitrate.AddString("3072");
	m_cbxSecondBitrate.SetItemData(nIndex,3072);
	nIndex=m_cbxSecondBitrate.AddString("4096");
	m_cbxSecondBitrate.SetItemData(nIndex,4096);
	nIndex=m_cbxSecondBitrate.AddString("6144");
	m_cbxSecondBitrate.SetItemData(nIndex,6144);
	if (m_nSecondBitrate<=32)
		m_nSecondBitrate=32;
	else if (m_nSecondBitrate<=64)
		m_nSecondBitrate=64;
	else if (m_nSecondBitrate<=128)
		m_nSecondBitrate=128;
	else if (m_nSecondBitrate<=256)
		m_nSecondBitrate=256;
	else if (m_nSecondBitrate<=384)
		m_nSecondBitrate=384;
	else if (m_nSecondBitrate<=512)
		m_nSecondBitrate=512;
	else if (m_nSecondBitrate<=768)
		m_nSecondBitrate=768;
	else if (m_nSecondBitrate<=1024)
		m_nSecondBitrate=1024;
	else if (m_nSecondBitrate<=1536)
		m_nSecondBitrate=1536;
	else if (m_nSecondBitrate<=2048)
		m_nSecondBitrate=2048;
	else if (m_nSecondBitrate<=3072)
		m_nSecondBitrate=3072;
	else if (m_nSecondBitrate<=4096)
		m_nSecondBitrate=4096;
	else if (m_nSecondBitrate<=1536)
		m_nSecondBitrate=1536;
	else 
		m_nSecondBitrate=6144;
	for (nIndex=0;nIndex<m_cbxSecondBitrate.GetCount();nIndex++)
	{
		int nBitrate=(int)m_cbxSecondBitrate.GetItemData(nIndex);
		if (nBitrate==m_nSecondBitrate)
		{
			m_cbxSecondBitrate.SetCurSel(nIndex);
			break;
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}
