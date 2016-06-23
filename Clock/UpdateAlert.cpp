// UpdateAlert.cpp : 实现文件
//

#include "stdafx.h"
#include "Clock.h"
#include "UpdateAlert.h"
#include "afxdialogex.h"

// CUpdateAlert 对话框

IMPLEMENT_DYNAMIC(CUpdateAlert, CDialogEx)

CUpdateAlert::CUpdateAlert(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UPDATE_ALERT, pParent)
{

}

CUpdateAlert::~CUpdateAlert()
{
}

void CUpdateAlert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALERT, m_alert);
}


BEGIN_MESSAGE_MAP(CUpdateAlert, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CUpdateAlert::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDOK, &CUpdateAlert::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CUpdateAlert::OnBnClickedButtonUpdate)
END_MESSAGE_MAP()

 

//设置字体
void CUpdateAlert::setfont(CEdit & edit)
{
	CFont font;
	font.CreateFontW(15, 15, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, _T("华文楷体"));
	edit.SetFont(&font);
}

int CUpdateAlert::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


void CUpdateAlert::listAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	std::ifstream read;
	read.open("alert.txt");
	if (read)
	{
		char cmessage[50];
		while (!read.eof())
		{
			alert a_alert;
			read >> a_alert.hour >> a_alert.minute >> cmessage;
			a_alert.message = cmessage;
			if (a_alert.hour >= 0 && a_alert.hour < 24)
			{
				valert.push_back(a_alert);
			}
		}
		read.close();
	}
	else
	{
		m_alert.AddString(_T("尚未设置提醒"));
	}
	if (valert.size() > 0)
	{
		for (size_t i = 0; i < valert.size(); i++)
		{
			CString alert;
			if (valert[i].hour < 10 && valert[i].minute < 10)
			{
				alert.Format(_T("0%d:0%d    "), valert[i].hour, valert[i].minute);
				alert += valert[i].message;
				m_alert.AddString(alert);
			}
			else if (valert[i].hour >= 10 && valert[i].minute < 10)
			{
				alert.Format(_T("%d:0%d    "), valert[i].hour, valert[i].minute);
				alert += valert[i].message;
				m_alert.AddString(alert);
			}
			else if (valert[i].hour < 10 && valert[i].minute >= 10)
			{
				alert.Format(_T("0%d:%d    "), valert[i].hour, valert[i].minute);
				alert += valert[i].message;
				m_alert.AddString(alert);
			}
			else
			{
				alert.Format(_T("%d:%d    "), valert[i].hour, valert[i].minute);
				alert += valert[i].message;
				m_alert.AddString(alert);
			}
		}
	}
	else
	{
		m_alert.AddString(_T("尚未设置提醒"));
	}
}


BOOL CUpdateAlert::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	listAdd();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUpdateAlert::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CUpdateAlert::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CUpdateAlert::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	m_alert.DeleteString(m_alert.GetCurSel());
	if (m_alert.GetCount() > 0)
	{
		for (size_t i = 0; i < m_alert.GetCount(); i++)
		{
			CString cstrtext;
			m_alert.GetText(i, cstrtext);
			USES_CONVERSION;
			char * ctext = T2A(cstrtext);
			std::string stext = ctext;
			//获取hour
			std::string shour = stext.substr(0, 2);
			int hour = atoi(shour.c_str());
			//获取minute
			std::string sminute = stext.substr(3, 2);
			int minute = atoi(shour.c_str());
			//获取message 
			std::string message = stext.substr(9, stext.length() - 9);
			if (i == 0)
			{
				std::ofstream file;
				file.open("alert.txt");
				file << hour << "\t" << minute << "\t" << message.c_str();
				file.close();
			}
			else
			{
				std::ofstream file;
				file.open("alert.txt", std::ofstream::app);
				file << "\n" << hour << "\t" << minute << "\t" << message.c_str();
				file.close();
			}
		}
	}
	else
	{
		std::ofstream file;
		file.open("alert.txt");
		file.close();
	}
}
