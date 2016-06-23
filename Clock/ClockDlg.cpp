
// ClockDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Clock.h"
#include "ClockDlg.h"
#include "afxdialogex.h"
#include "SetAlarmClock.h"
#include "UpdateAlert.h"
//��������
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IDC_CREAT_DATE 100
#define IDC_CREAT_TIME 101
#define PI 3.1415926
#define CLOCK_X 180
#define CLOCK_Y 140
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
int hour, minute, second;
bool start = 0;

CString CStr_date, CStr_time;

char on_time_message[50];
bool if_get = 0;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnSetNewAlert();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClockDlg �Ի���



CClockDlg::CClockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLOCK_DIALOG, pParent)
	, m_date(_T(""))
	, m_time(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_DATE, m_date);
	//DDX_Text(pDX, IDC_EDIT_TIME, m_time);
}

BEGIN_MESSAGE_MAP(CClockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_UPDATE_ALERT, &CClockDlg::OnUpdateAlert)
	ON_COMMAND(ID_SET_NEW_ALERT, &CClockDlg::OnSetNewAlert)
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_START_SCREEN, &CClockDlg::OnStartScreen)
	ON_COMMAND(ID_EXIT, &CClockDlg::OnExit)
END_MESSAGE_MAP()


// CClockDlg ��Ϣ�������

BOOL CClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	//CMenu* menu = new CMenu;
	m_menu.LoadMenu(IDR_MENU1);   //���ز˵���Դ     
	//this->SetMenu(menu);
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	//SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//ȫ��
	ShowCursor(false); //ȡ����ʾ���
	CRect rc(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); //��ȡ��Ļ��С
	::GetCursorPos(&curpt);
	this->MoveWindow(rc);
	SetDateCoordinate();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CClockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

//����clock����Ͱ뾶
void CClockDlg::SetClockCoordinate()
{
	CRect rectDlg;
	GetClientRect(rectDlg);//��ô���Ĵ�С
	clock_r = (rectDlg.bottom - rectDlg.top) / 6; //�뾶������1/6
	clock_x = (rectDlg.right - rectDlg.left) / 3;
	clock_y = (rectDlg.bottom - rectDlg.top) / 2;
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
//�Ի������С������Ļ����
void CClockDlg::OnPaint()
{
	SetClockCoordinate();
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		//���ر���
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);//IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ
		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		double x, y;
		for (size_t i = 0; i < 60; i++)
		{
			x = clock_x + clock_r * cos(i * 6 * PI / 180);
			y = clock_y - clock_r * sin(i * 6 * PI / 180);
			if (i % 15 == 0)
			{
				if (i / 15 == 0)
				{
					CPen HourPen(PS_SOLID, 2, RGB(0, 0, 0));
					dc.SelectObject(&HourPen);
					dc.MoveTo(x, y);
					dc.LineTo(x - 8, y);
				}
				else if (i / 15 == 1)
				{
					dc.MoveTo(x, y);
					dc.LineTo(x, y + 8);
				}
				else if (i / 15 == 3)
				{
					dc.MoveTo(x, y);
					dc.LineTo(x, y - 8);
				}
				else 
				{
					dc.MoveTo(x, y);
					dc.LineTo(x + 8, y);
				}
			}
			else if(i % 5 == 0)
			{
				dc.Ellipse(x - 2, y - 2, x + 2, y + 2);
			}
			else
			{
				dc.Ellipse(x - 1, y - 1, x + 1, y + 1);
			}
		}
		//��ָ��
		if (start)
		{
			int hour_len, minute_len, second_len;
			hour_len = 2 * clock_r / 3;
			minute_len = 7 * clock_r / 10;
			second_len = 9 * clock_r / 10;
			CDC *pDC;
			pDC = GetDC();
			int hx, hy;
			if (hour > 12) 
			{
				hx = hour_len * sin(((hour - 12) * 30 + minute /2 ) * PI / 180);
				hy = hour_len * cos(((hour - 12) * 30 + minute / 2) * PI / 180);
			}
			else
			{
				hx = hour_len * sin((hour * 30 + minute / 2) * PI / 180);
				hy = hour_len * cos((hour * 30 + minute / 2) * PI / 180);
			}
			CPen HourPen(PS_SOLID, 5, RGB(0, 0, 0));
			pDC->SelectObject(&HourPen);
			pDC->MoveTo(clock_x, clock_y);
			pDC->LineTo(clock_x + hx, clock_y - hy);
			int mx, my;
			mx = minute_len * sin(minute * 6 * PI / 180);
			my = minute_len * cos(minute * 6 * PI / 180);
			//�������ӻ���  
			CPen MinutePen(PS_SOLID, 3, RGB(0, 0, 255));
			pDC->SelectObject(&MinutePen);
			pDC->MoveTo(clock_x, clock_y);
			pDC->LineTo(clock_x + mx, clock_y - my);
			int sx, sy;
			sx = second_len * sin(second * 6 * PI / 180);
			sy = second_len * cos(second * 6 * PI / 180);
			//�������ӻ���  
			CPen SecondPen(PS_SOLID, 2, RGB(255, 0, 0));
			pDC->SelectObject(&SecondPen);
			pDC->MoveTo(clock_x, clock_y);
			pDC->LineTo(clock_x + sx, clock_y - sy);
			//��������ʱ����ʾ�ؼ�
			date_edit.SetWindowTextW(CStr_date);
			time_edit.SetWindowTextW(CStr_time);
		}
		if (!if_get)
		{
			play_alert(hour, minute);
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClockDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ȡ���������
	PlaySound(NULL, NULL, NULL);
	SetTimer(1, 1000, NULL);
}


 //�������ڿؼ�����
void CClockDlg::SetDateCoordinate()
{
	int dx, dy, dwidth, dheight;
	int tx, ty, twidth, theight;
	CRect rectDlg;
	GetClientRect(rectDlg);//��ô���Ĵ�С
	dwidth = (rectDlg.bottom - rectDlg.top) / 6;
	twidth = dwidth;
	dx = (rectDlg.right - rectDlg.left) / 2 - (rectDlg.bottom - rectDlg.top) / 12;
	tx = dx;
	dy = (rectDlg.bottom - rectDlg.top) / 2 - (rectDlg.bottom - rectDlg.top) / 24;
	dheight = (rectDlg.bottom - rectDlg.top) / 2;
	ty = (rectDlg.bottom - rectDlg.top) / 2;
	theight = (rectDlg.bottom - rectDlg.top) / 2 + (rectDlg.bottom - rectDlg.top) / 24;
	date_edit.Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP, CRect(dx + 100, dy - 10, dx + dwidth + 100, dheight - 10), this, IDC_CREAT_DATE);
	time_edit.Create(ES_LEFT | ES_AUTOHSCROLL | WS_BORDER | WS_VISIBLE | WS_CHILD | WS_TABSTOP, CRect(tx + 100, ty + 10, tx + twidth + 100, theight + 10), this, IDC_CREAT_TIME);
	//��������
	CFont font;
	font.CreateFontW(15, 15, 0, 0, FW_BLACK, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_CHARACTER_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, _T("���Ŀ���"));
	date_edit.SetFont(&font);
	time_edit.SetFont(&font);
}

void CClockDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString cstr_date, cstr_time;
	CTime get_time;
	get_time = get_time.GetCurrentTime(); //��ȡϵͳʱ��
	cstr_date = get_time.Format("%Y-%m-%d"); //��ȡ������
	cstr_time = get_time.Format("%X");      //��ȡʱ��
	CStr_date = get_time.Format("%Y-%m-%d");
	CStr_time = get_time.Format("%X");
	 
	//��ȡʱ���֡���
	hour = get_time.GetHour();
	minute = get_time.GetMinute();
	second = get_time.GetSecond();
	start = true;
	InvalidateRect(NULL, TRUE);
	UpdateWindow();//ˢ�´���
	CDialogEx::OnTimer(nIDEvent);
}


int CClockDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(1, 1000, NULL); //ÿ��ˢ��һ����Ļ
	return 0;
}

//���������
void CClockDlg::OnSetNewAlert()
{
	// TODO: �ڴ���������������
	CSetAlarmClock newClock;
	newClock.DoModal();
}

//�޸�����������
void CClockDlg::OnUpdateAlert()
{
	// TODO: �ڴ���������������
	CUpdateAlert *update;
	update = new CUpdateAlert;
	update->DoModal();
	
}

//�Ҽ������˵�
void CClockDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMenu *pMenu = m_menu.GetSubMenu(0);//��ò˵����  
	CRect rect;                         //����һ��CRect����  
	ClientToScreen(&point);                 //���ͻ�����ת��Ϊ��Ļ����  
	rect.top = point.x;       //����굱ǰ��������Ϊ�����˵������Ͻ�����  
	rect.left = point.y;      //����굱ǰ��������Ϊ�����˵������Ͻ�����  
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL, rect.top, rect.left, this, &rect);//��ʾ�����˵�
	CDialogEx::OnRButtonUp(nFlags, point);
}

//����ƶ�ȡ������
void CClockDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int moveptx = point.x - curpt.x;
	int movepty = point.y - curpt.y;
	if (moveptx + movepty > 10)
	{
		CRect rc(250, 100, 1116, 668);
		::GetCursorPos(&curpt);
		this->MoveWindow(rc);
		ShowCursor(true);
		//ɾ�������Ŀؼ�
		date_edit.DestroyWindow();
		time_edit.DestroyWindow();
		//���´���
		SetDateCoordinate();

	}
	CDialogEx::OnMouseMove(nFlags, point);
}

//��������
void CClockDlg::OnStartScreen()
{
	// TODO: �ڴ���������������
	ShowCursor(false);
	CRect rc(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	::GetCursorPos(&curpt);
	this->MoveWindow(rc);

	date_edit.DestroyWindow();
	time_edit.DestroyWindow();
	SetDateCoordinate();
}

//�ж�ʱ���Ƿ���ͬ
int CClockDlg::if_exit(int hour, int minute)
{
	int set_hour, set_minute;
	std::ifstream read;
	read.open("alert.txt");
	if (read)
	{
		while (!read.eof())
		{
			read >> set_hour >> set_minute >> on_time_message;
			if (set_hour == hour)
			{
				if (set_minute == minute)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

//������ʾ��
void CClockDlg::play_alert(int hour, int minute)
{
	if (if_exit(hour, minute) && !if_get)
	{
		if_get = 1;
		//KillTimer(1);
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		CString message;
		message += on_time_message;
		MessageBox(message);
	}
}


void CClockDlg::OnExit()
{
	// TODO: �ڴ���������������
	CDialogEx::OnOK();
}
