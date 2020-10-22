
// UART_APPDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "UART_APP.h"
#include "UART_APPDlg.h"
#include "afxdialogex.h"
#include "cstring"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char LED1OFF_RECEIVE[3] = { 0x43, 0x01, 0x00 };
const char LED1ON_RECEIVE[3] = { 0x43, 0x01, 0x01 };
const char LED1INV_RECEIVE[3] = { 0x43, 0x01, 0x02 };

const char LED2OFF_RECEIVE[3] = { 0x43, 0x01, 0x00 };
const char LED2ON_RECEIVE[3] = { 0x43, 0x01, 0x01 };
const char LED2INV_RECEIVE[3] = { 0x43, 0x01, 0x02 };

const char LED3OFF_RECEIVE[3] = { 0x43, 0x01, 0x00 };
const char LED3ON_RECEIVE[3] = { 0x43, 0x01, 0x01 };
const char LED3INV_RECEIVE[3] = { 0x43, 0x01, 0x02 };


const char LED1OFF_SEND[3] = { 0x43, 0x01, 0x00 };
const char LED1ON_SEND[3] = { 0x43, 0x01, 0x01 };
const char LED1INV_SEND[3] = { 0x43, 0x01, 0x02 };

const char LED2OFF_SEND[3] = { 0x43, 0x01, 0x00 };
const char LED2ON_SEND[3] = { 0x43, 0x01, 0x01 };
const char LED2INV_SEND[3] = { 0x43, 0x01, 0x02 };

const char LED3OFF_SEND[3] = { 0x43, 0x01, 0x00 };
const char LED3ON_SEND[3] = { 0x43, 0x01, 0x01 };
const char LED3INV_SEND[3] = { 0x43, 0x01, 0x02 };

static UINT BASED_CODE indicators[] =
{
	IDS_STATUS,
	IDS_COMPORT
};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
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




CConfigureDlg::CConfigureDlg(UART_Configuration* uart_config) : CDialogEx(IDD_CONFIGURE_DIALOG)
{
	ptr_uart_config = uart_config;
}

CConfigureDlg::~CConfigureDlg()
{

}

BOOL CConfigureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CComboBox* m_comboComport = (CComboBox*)GetDlgItem(IDC_COMBO_COMPORT);

	for (int i = 1; i < 20; i++)
	{
		CString port_number;
		port_number.Format(_T("%d"), i);
		m_comboComport->AddString(CString(_T("COM") + port_number));
	}
	
	m_comboComport->SetCurSel(m_comboComport->FindStringExact(0, ptr_uart_config->getComPort()));

	CComboBox* m_comboBaudrate = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
    m_comboBaudrate->AddString(CString(_T("9600")));
    m_comboBaudrate->AddString(CString(_T("14400")));
    m_comboBaudrate->AddString(CString(_T("19200")));
    m_comboBaudrate->AddString(CString(_T("38400")));
    m_comboBaudrate->AddString(CString(_T("57600")));
    m_comboBaudrate->AddString(CString(_T("115200")));
    m_comboBaudrate->AddString(CString(_T("128000")));

	m_comboBaudrate->SetCurSel(m_comboBaudrate->FindStringExact(0, ptr_uart_config->getBaudRate()));

	CComboBox* m_comboBits = (CComboBox*)GetDlgItem(IDC_COMBO_DATA_BITS);
	m_comboBits->AddString(CString(_T("5")));
	m_comboBits->AddString(CString(_T("6")));
	m_comboBits->AddString(CString(_T("7")));
	m_comboBits->AddString(CString(_T("8")));

	m_comboBits->SetCurSel(m_comboBits->FindStringExact(0, ptr_uart_config->getByteSize()));


	CComboBox* m_comboParity = (CComboBox*)GetDlgItem(IDC_COMBO_PARITY);
	m_comboParity->AddString(CString(_T("NONE")));
	m_comboParity->AddString(CString(_T("EVEN")));
	m_comboParity->AddString(CString(_T("ODD")));
	m_comboParity->AddString(CString(_T("MARK")));
	m_comboParity->AddString(CString(_T("SPACE")));

	m_comboParity->SetCurSel(m_comboParity->FindStringExact(0, ptr_uart_config->getParity()));

	CComboBox* m_comboStopBits = (CComboBox*)GetDlgItem(IDC_COMBO_STOP_BITS);
	m_comboStopBits->AddString(CString(_T("1")));
	m_comboStopBits->AddString(CString(_T("1.5")));
	m_comboStopBits->AddString(CString(_T("2")));

	m_comboStopBits->SetCurSel(m_comboStopBits->FindStringExact(0, ptr_uart_config->getStopBits()));

	return TRUE;  // return TRUE  unless you set the focus to a control

}

void CConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigureDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConfigureDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CConfigureDlg::OnBnClickedCancel)
END_MESSAGE_MAP()




// CUARTAPPDlg dialog



CUARTAPPDlg::CUARTAPPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UART_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_UART);

	m_thread_created = false;
	receive_status = false;
	// get some color brush
	m_redcolor = RGB(255, 0, 0);                      // red
	m_bluecolor = RGB(0, 0, 255);                     // blue
	m_textcolor = RGB(255, 255, 255);                 // white text
	m_redbrush.CreateSolidBrush(m_redcolor);      // red background
	m_bluebrush.CreateSolidBrush(m_bluecolor);    // blue background
}

void CUARTAPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUARTAPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SW1, &CUARTAPPDlg::OnBnClickedButtonSw1)
	ON_BN_CLICKED(IDC_BUTTON_SW2, &CUARTAPPDlg::OnBnClickedButtonSw2)
	ON_BN_CLICKED(IDC_BUTTON_SW3, &CUARTAPPDlg::OnBnClickedButtonSw3)
	ON_COMMAND(ID_TOOLS_CONFIGURE, &CUARTAPPDlg::OnToolsConfigure)
	ON_COMMAND(ID_HELP_ABOUT, &CUARTAPPDlg::OnHelpAbout)
	ON_COMMAND(ID_TOOLS_CLEAR, &CUARTAPPDlg::OnToolsClear)
	ON_COMMAND(ID_MENU_CONNECT, &CUARTAPPDlg::OnMenuConnect)
	ON_COMMAND(ID_CALLS_DISC, &CUARTAPPDlg::OnMenuDisconnect)
	ON_COMMAND(ID_CONFIGURE_EXIT, &CUARTAPPDlg::OnConfigureExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CUARTAPPDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CUARTAPPDlg message handlers

BOOL CUARTAPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.


	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_bar.Create(this); //We create the status bar
	
	m_bar.SetIndicators(indicators, 2); //Set the number of panes 

	CRect rect;
	GetClientRect(&rect);
	//Size the two panes
	m_bar.SetPaneInfo(0, IDS_STATUS,
		SBPS_NORMAL, rect.Width() - 100);
	m_bar.SetPaneInfo(1, IDS_COMPORT, SBPS_STRETCH, 0);

	//This is where we actually draw it on the screen
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
		IDS_COMPORT);
	m_bar.GetStatusBarCtrl().SetBkColor(RGB(180, 180, 180));
	CString str1 = CString(_T(""));
	CString str2 = CString(_T("disconnected"));
	m_bar.SetPaneText(1, str1);
	m_bar.SetPaneText(0, str2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUARTAPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUARTAPPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUARTAPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUARTAPPDlg::OnBnClickedButtonSw1()
{
	// TODO: Add your control notification handler code here
}


void CUARTAPPDlg::OnBnClickedButtonSw2()
{
	// TODO: Add your control notification handler code here
}


void CUARTAPPDlg::OnBnClickedButtonSw3()
{
	// TODO: Add your control notification handler code here
}


void CUARTAPPDlg::OnToolsConfigure()
{
	CConfigureDlg dlgConfigure(&m_uart_config);
	dlgConfigure.DoModal();
}


void CUARTAPPDlg::OnHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CUARTAPPDlg::OnToolsClear()
{
	CEdit* m_editTerminal = (CEdit*)GetDlgItem(IDC_EDIT_TERMINAL);
	m_editTerminal->SetWindowTextW(CString(""));
}

UINT receiveThread(void* class_ptr)
{
	CUARTAPPDlg* m_class = (CUARTAPPDlg*)class_ptr;
	while(m_class->receive_status)
		m_class->readRXData();
	return 0;
}

void CUARTAPPDlg::readRXData()
{
	char* str = m_uart_config.read();
	CString readData = CString(str);
	CEdit* m_editTerminal = (CEdit*)GetDlgItem(IDC_EDIT_TERMINAL);

	// get the initial text length
	int nLength = m_editTerminal->GetWindowTextLength();

	
		
	// put the selection at the end of text
	m_editTerminal->SetSel(nLength, nLength);
	// replace the selection
	if (strcmp(str, LED1ON_RECEIVE) == 0)
		m_editTerminal->ReplaceSel(CString("LED1ondata received"));
	else
		m_editTerminal->ReplaceSel(readData);


}

void CUARTAPPDlg::OnMenuConnect()
{
	m_uart_config.setDCB();
	m_uart_config.connect();
	receive_status = true;
	// start thread to receive data
	if (m_thread_created == false)
	{
		AfxBeginThread(receiveThread, this);
		m_thread_created = true;
	}
	CString str1 = m_uart_config.getComPort();
	CString str2 = CString(_T("connected"));
	m_bar.SetPaneText(1, str1);
	m_bar.SetPaneText(0, str2);
}




void CUARTAPPDlg::OnMenuDisconnect()
{
	receive_status = false;
	m_uart_config.disconnect();
	//as thread exit
	m_thread_created = false;
	CString str1 = CString(_T(""));
	CString str2 = CString(_T("disconnected"));
	m_bar.SetPaneText(1, str1);
	m_bar.SetPaneText(0, str2);
}


void CUARTAPPDlg::OnConfigureExit()
{
	// TODO: Add your command handler code here

}



void CConfigureDlg::OnBnClickedOk()
{
	CComboBox* m_COMPORT = (CComboBox*)GetDlgItem(IDC_COMBO_COMPORT);
	CString com_name;
	int index = m_COMPORT->GetCurSel();
	m_COMPORT->GetLBText(index, com_name);
	ptr_uart_config->setComPort(com_name);

	CComboBox* m_BAUDRATE = (CComboBox*)GetDlgItem(IDC_COMBO_BAUDRATE);
	CString baud_rate;
	index = m_BAUDRATE->GetCurSel();
	m_BAUDRATE->GetLBText(index, baud_rate);
	ptr_uart_config->setBaudRate(baud_rate);


	CComboBox* m_DATABITS = (CComboBox*)GetDlgItem(IDC_COMBO_DATA_BITS);
	CString databits_str;
	index = m_DATABITS->GetCurSel();
	m_DATABITS->GetLBText(index, databits_str);
	ptr_uart_config->setByteSize(databits_str);


	CComboBox* m_PARITY = (CComboBox*)GetDlgItem(IDC_COMBO_PARITY);
	CString parity_str;
	index = m_PARITY->GetCurSel();
	m_PARITY->GetLBText(index, parity_str);
	ptr_uart_config->setParity(parity_str);


	CComboBox* m_STOPBITS = (CComboBox*)GetDlgItem(IDC_COMBO_STOP_BITS);
	CString stopbits_str;
	index = m_STOPBITS->GetCurSel();
	m_STOPBITS->GetLBText(index, stopbits_str);
	ptr_uart_config->setStopBits(stopbits_str);
	
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CConfigureDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CUARTAPPDlg::OnBnClickedButtonSend()
{
	CEdit* m_sen_edit = (CEdit*)GetDlgItem(IDC_EDIT_SEND_DATA);
	CString sendData;
	m_sen_edit->GetWindowTextW(sendData);
	m_uart_config.write(sendData);
	m_sen_edit->SetWindowTextW(CString(""));
}
