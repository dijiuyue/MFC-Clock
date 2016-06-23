
// ClockDlg.h : ͷ�ļ�
//

#pragma once


// CClockDlg �Ի���
class CClockDlg : public CDialogEx
{
// ����
public:
	CClockDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLOCK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CString m_date;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_time;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateAlert();
	afx_msg void OnSetNewAlert();
	CMenu m_menu;
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void SetClockCoordinate();
	int clock_x, clock_y, clock_r; //���꣬�뾶
	CPoint curpt;
	
	CEdit date_edit, time_edit;
	afx_msg void SetDateCoordinate();

	afx_msg void OnStartScreen();
	afx_msg void OnExit();

	afx_msg int if_exit(int hour, int minute);
	afx_msg void play_alert(int hour, int minute);

};
