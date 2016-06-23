#pragma once
#include "afxwin.h"
#include <fstream>
#include <iostream>
#include <vector>

// CUpdateAlert 对话框
struct alert
{
	int hour;
	int minute;
	CString message;
};

class CUpdateAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateAlert)

public:
	CUpdateAlert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUpdateAlert();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_ALERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	// 生成的消息映射函数
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedShow();
	CButton myButton;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void setfont(CEdit &edit);
	afx_msg void listAdd();
	CListBox m_alert;
	std::vector<alert> valert;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonUpdate();
};
