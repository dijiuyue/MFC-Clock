// SetAlarmClock.cpp : 实现文件
//

#include "stdafx.h"
#include "Clock.h"
#include "SetAlarmClock.h"
#include "afxdialogex.h"
#include <fstream>
#include "ClockDlg.h"
// CSetAlarmClock 对话框

IMPLEMENT_DYNAMIC(CSetAlarmClock, CDialogEx)

CSetAlarmClock::CSetAlarmClock(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_message(_T(""))
{

}

CSetAlarmClock::~CSetAlarmClock()
{
}

void CSetAlarmClock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_message);
	DDX_Control(pDX, IDC_COMBO_HOUR, m_hour);
	DDX_Control(pDX, IDC_COMBO_MINUTE, m_minute);
}


BEGIN_MESSAGE_MAP(CSetAlarmClock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CSetAlarmClock::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// CSetAlarmClock 消息处理程序


void CSetAlarmClock::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	//setAlert alert;
	UpdateData(true);
	int hour, minute;
	hour = m_hour.GetCurSel();
	minute = m_minute.GetCurSel();
	//m_minute.GetLBText(m_minute.GetCurSel(), minute);
	CClockDlg test;
	int if_set = test.if_exit(hour, minute);
	if (!if_set)
	{
		//使用T2A将Cstring转换为char *
		USES_CONVERSION;
		char * message = T2A(m_message);
		std::ifstream fin("alert.txt");
		if (fin)
		{
			std::ofstream file;
			file.open("alert.txt", std::ofstream::app);
			file << "\n" << hour << "\t" << minute << "\t" << message;
			file.close();
		}
		else
		{
			std::ofstream file;
			file.open("alert.txt", std::ofstream::app);
			file << hour << "\t" << minute << "\t" << message;
			file.close();
		}
		MessageBox(_T("添加成功"));
	}
	else
	{
		MessageBox(_T("在这个时间已经设置过提醒"));
	}
}
