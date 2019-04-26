// DlgAudioSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MediaChannelTest.h"
#include "DlgAudioSetting.h"


// DlgAudioSetting 对话框

IMPLEMENT_DYNAMIC(DlgAudioSetting, CDialog)

DlgAudioSetting::DlgAudioSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAudioSetting::IDD, pParent)
	, m_AudioCodecID(X_AUDIO_CODEC_AUDEC_24)
{

}

DlgAudioSetting::~DlgAudioSetting()
{
}

void DlgAudioSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AUDIO_CODEC, m_cbxAudioCodec);
}


BEGIN_MESSAGE_MAP(DlgAudioSetting, CDialog)
	ON_BN_CLICKED(IDOK, &DlgAudioSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgAudioSetting 消息处理程序

BOOL DlgAudioSetting::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nIndex=m_cbxAudioCodec.AddString("G.711 ULaw 64Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G711U);
	nIndex=m_cbxAudioCodec.AddString("G.711 ALaw 64Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G711A);
	nIndex=m_cbxAudioCodec.AddString("G.729A 8Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G729);
	//nIndex=m_cbxAudioCodec.AddString("G.723.1 6.3Kbps");
	//m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G7231_63);
	nIndex=m_cbxAudioCodec.AddString("G.722 64Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G722_64);
	nIndex=m_cbxAudioCodec.AddString("G.722.1 24Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G7221_14_24);
	nIndex=m_cbxAudioCodec.AddString("G.722.1 32Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_G7221_14_32);
	nIndex=m_cbxAudioCodec.AddString("AUDEC 24Kbps");
	m_cbxAudioCodec.SetItemData(nIndex,X_AUDIO_CODEC_AUDEC_24);

	switch (m_AudioCodecID)
	{
	case X_AUDIO_CODEC_G711U:
		nIndex=0;
		break;
	case X_AUDIO_CODEC_G711A:
		nIndex=1;
		break;
	case X_AUDIO_CODEC_G729:
		nIndex=2;
		break;
	case X_AUDIO_CODEC_G722_64:
		nIndex=3;
		break;
	case X_AUDIO_CODEC_G7221_14_24:
		nIndex=4;
		break;
	case X_AUDIO_CODEC_G7221_14_32:
		nIndex=5;
		break;
	case X_AUDIO_CODEC_AUDEC_24:
		nIndex=6;
		break;
	default:
		nIndex=0;
		break;
	}

	m_cbxAudioCodec.SetCurSel(nIndex);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void DlgAudioSetting::OnBnClickedOk()
{
	int nIndex=m_cbxAudioCodec.GetCurSel();
	m_AudioCodecID=(X_AUDIO_CODEC_ID)m_cbxAudioCodec.GetItemData(nIndex);

	OnOK();
}
