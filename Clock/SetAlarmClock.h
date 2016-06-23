#pragma once
#include "afxwin.h"


// CSetAlarmClock 对话框

class CSetAlarmClock : public CDialogEx
{
	DECLARE_DYNAMIC(CSetAlarmClock)

public:
	CSetAlarmClock(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetAlarmClock();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_message;
	afx_msg void OnBnClickedButtonAdd();
	CComboBox m_hour;
	CComboBox m_minute;

};
