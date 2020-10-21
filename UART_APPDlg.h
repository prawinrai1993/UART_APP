
// UART_APPDlg.h : header file
//

#pragma once
#include "UART_Configuration.h"

// CConfigure dialog used for CONFIGURE dialog

class CConfigureDlg : public CDialogEx
{

public:
	CConfigureDlg(UART_Configuration* uart_config);
	~CConfigureDlg();

protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGURE_DIALOG };
#endif



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

private:
	UART_Configuration* ptr_uart_config;
};



// CUARTAPPDlg dialog
class CUARTAPPDlg : public CDialogEx
{
// Construction
public:
	CStatusBar m_bar;
	CUARTAPPDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UART_APP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSw1();
	afx_msg void OnBnClickedButtonSw2();
	afx_msg void OnBnClickedButtonSw3();
	afx_msg void OnToolsConfigure();
	afx_msg void OnHelpAbout();
	afx_msg void OnToolsClear();
	afx_msg void OnMenuConnect();
	afx_msg void OnMenuDisconnect();
	afx_msg void OnConfigureExit();
	friend UINT receiveThread(void* param);
	void readRXData();
	
private:
	UART_Configuration m_uart_config;
	bool receive_status;
	CBrush m_redbrush, m_bluebrush;
	COLORREF m_redcolor, m_bluecolor, m_textcolor;
	bool m_thread_created;
public:
	afx_msg void OnBnClickedButtonSend();
};
