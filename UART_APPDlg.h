
// UART_APPDlg.h : header file
//

#pragma once


// CUARTAPPDlg dialog
class CUARTAPPDlg : public CDialogEx
{
// Construction
public:
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonSw1();
	afx_msg void OnBnClickedButtonSw2();
	afx_msg void OnBnClickedButtonSw3();
	afx_msg void OnToolsConfigure();
};
