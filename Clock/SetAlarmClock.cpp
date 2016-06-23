// SetAlarmClock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clock.h"
#include "SetAlarmClock.h"
#include "afxdialogex.h"
#include <fstream>
#include "ClockDlg.h"
// CSetAlarmClock �Ի���

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


// CSetAlarmClock ��Ϣ�������


void CSetAlarmClock::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		//ʹ��T2A��Cstringת��Ϊchar *
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
		MessageBox(_T("��ӳɹ�"));
	}
	else
	{
		MessageBox(_T("�����ʱ���Ѿ����ù�����"));
	}
}
