#include "pch.h"
#include "UART_Configuration.h"


#include "UART_CONFIGURATION.h"
#include "pch.h"

UART_Configuration::UART_Configuration()
{
	// variables used with the com port
	m_bPortReady = false;
	m_hCom;
	/* default values*/
	m_sComPort = CString(_T("COM5"));
	m_BaudRate = CString(_T("9600"));
	m_ByteSize = CString(_T("8"));
	m_Parity = CString(_T("NONE"));
	m_StopBits = CString(_T("1"));
	m_dcb;
	m_CommTimeouts;
	bWriteRC= false;
	bReadRC = false;
	iBytesWritten = 0;
	iBytesRead =0;

	/* default values*/
	m_dcb.BaudRate = 9600;
	m_dcb.ByteSize = 8;
	m_dcb.Parity = NOPARITY;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.fAbortOnError = TRUE;


}
UART_Configuration::~UART_Configuration()
{


}


void UART_Configuration::setComPort(CString val)
{
	m_sComPort = val;

}
void UART_Configuration::setBaudRate(CString val)
{
	m_BaudRate = val;
	m_dcb.BaudRate = _wtoi(m_BaudRate);

}
void UART_Configuration::setByteSize(CString val)
{
	m_ByteSize = val;
	m_dcb.ByteSize = _wtoi(m_ByteSize);
}
void UART_Configuration::setParity(CString val)
{
	m_Parity = val;
	if(m_Parity == "NONE")
		m_dcb.Parity = NOPARITY;
	else if(m_Parity == "EVEN")
		m_dcb.Parity = EVENPARITY;
	else if (m_Parity == "ODD")
		m_dcb.Parity = ODDPARITY;
	else if (m_Parity == "MARK")
		m_dcb.Parity = MARKPARITY;
	else if (m_Parity == "SPACE")
		m_dcb.Parity = SPACEPARITY;

}
void UART_Configuration::setStopBits(CString val)
{

	m_StopBits = val;
   if(m_StopBits == "1")
		m_dcb.StopBits = ONESTOPBIT;
   else if(m_StopBits == "1.5")
		m_dcb.StopBits = ONE5STOPBITS;
   else if(m_StopBits == "2")
		m_dcb.StopBits = TWOSTOPBITS;

}


CString UART_Configuration::getComPort()
{
	return m_sComPort;
}
CString UART_Configuration::getBaudRate()
{
	return m_BaudRate;
}
CString UART_Configuration::getByteSize()
{
	return m_ByteSize;
}
CString UART_Configuration::getParity()
{
	return m_Parity;
}
CString UART_Configuration::getStopBits()
{
	return m_StopBits;
}

void UART_Configuration::setDCB()
{
	m_hCom = CreateFile(m_sComPort,
		GENERIC_READ | GENERIC_WRITE,
		0, // exclusive access
		NULL, // no security
		OPEN_EXISTING,
		0, // no overlapped I/O
		NULL); // null templat

	m_bPortReady = SetupComm(m_hCom, 128, 128); // set buffer sizes
	m_bPortReady = GetCommState(m_hCom, &m_dcb);

}
void UART_Configuration::connect()
{
	m_bPortReady = SetCommState(m_hCom, &m_dcb);


	m_bPortReady = GetCommTimeouts(m_hCom, &m_CommTimeouts);

	m_CommTimeouts.ReadIntervalTimeout = 50;
	m_CommTimeouts.ReadTotalTimeoutConstant = 50;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 10;
	m_CommTimeouts.WriteTotalTimeoutConstant = 50;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 10;

	m_bPortReady = SetCommTimeouts(m_hCom, &m_CommTimeouts);

}
void UART_Configuration::disconnect()
{
	CloseHandle(m_hCom);

}

CString UART_Configuration::read()
{
	CString bufferString;
	bReadRC = ReadFile(m_hCom, &sBuffer, 128, &iBytesRead, NULL);
	if(iBytesRead)
		bufferString =sBuffer;
	else
		bufferString = "";
	memset(sBuffer, 0, 128);
	return bufferString;
}
void UART_Configuration::write(CString sendString)
{
	sendString.Append(CString("\r"));
	CStringA charstr(sendString);
	bWriteRC = WriteFile(m_hCom, (const char *)charstr, sendString.GetLength(), &iBytesWritten, NULL);
	iBytesWritten;
}
