#pragma once


#include "../../include/VIDEC/VIDEC.h"

// DlgCapVideo 对话框
class DlgMain;
class DlgCapVideo : public CDialog
{
	DECLARE_DYNAMIC(DlgCapVideo)

public:
	DlgCapVideo(DlgMain&rDlgMain);   // 标准构造函数
	virtual ~DlgCapVideo();

	VIDEC_Wnd*		m_pWnd;
	DlgMain&		m_rDlgMain;

	void ResizeControls(void);

// 对话框数据
	enum { IDD = IDD_DIALOG_CAP_VIDEO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
