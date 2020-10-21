#pragma once
class UART_Configuration {

private:
	// variables used with the com port
	BOOL     m_bPortReady;
	HANDLE   m_hCom;
	CString  m_sComPort;
	CString  m_BaudRate;
	CString  m_ByteSize;
	CString  m_Parity;
	CString  m_StopBits;
	DCB      m_dcb;
	COMMTIMEOUTS m_CommTimeouts;
	BOOL     bWriteRC;
	BOOL     bReadRC;
	DWORD iBytesWritten;
	DWORD iBytesRead;
	char  sBuffer[128];

public:
	UART_Configuration();
	~UART_Configuration();
	void setComPort(CString val);
	void setBaudRate(CString val);
	void setByteSize(CString val);
	void setParity(CString val);
	void setStopBits(CString val);
	void setDCB();
	CString getComPort();
	CString getBaudRate();
	CString getByteSize();
	CString getParity();
	CString getStopBits();

	void connect();
	void disconnect();
	CString read();
	void write(CString sendString);

};

