#pragma once
#include "afxwin.h"


// CSetAlarmClock �Ի���

class CSetAlarmClock : public CDialogEx
{
	DECLARE_DYNAMIC(CSetAlarmClock)

public:
	CSetAlarmClock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetAlarmClock();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_message;
	afx_msg void OnBnClickedButtonAdd();
	CComboBox m_hour;
	CComboBox m_minute;

};
