#include "pch.h"
#include "UART_Configuration.h"


#include "UART_CONFIGURATION.h"
#include "pch.h"


const int DATA_SIZE = 3;

const char DLE[1] = { 0x10 };
const char STX[1] = { 0x02 };
const char ETX[1] = { 0x03 };


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

bool UART_Configuration::setDCB()
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

	if (!m_bPortReady)
	{
		AfxMessageBox(_T("COMPORT cannot be connected!"), MB_OK | MB_ICONSTOP);
		return false;
	}

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

char * UART_Configuration::read()
{
	CString bufferString;
	static char data_buffer[3] = {0,0,0};
	char byte_data[1] = "";
	bool dle_found = false;
	bool stx_found = false;
	bool etx_found = false;
	bool data_found = false;

	memset(data_buffer, 0, 3);

	do {
		bReadRC =	ReadFile(m_hCom, &byte_data, 1, &iBytesRead, NULL);
		if (strncmp(byte_data, DLE,1) == 0)
			dle_found = true;

		if (strncmp(byte_data, STX,1) == 0)
			stx_found = true;


		if (dle_found && stx_found)
		{
			int count = 0;
			do {
				bReadRC = ReadFile(m_hCom, &byte_data, 1, &iBytesRead, NULL);
				if (strncmp(byte_data, ETX, 1) == 0)
					etx_found = true;
				if((etx_found == false) && count < DATA_SIZE)
				{ 
					data_buffer[count] = byte_data[0];
					count++;
				}

				if ((count > DATA_SIZE) || (iBytesRead == 0))
					break;
			} while ((etx_found == false));

			if (!etx_found && (iBytesRead == 0))
			{
				data_found = false;
				break;
			}
			else
			{
				data_found = true;
				break;
			}

		}
	} while (iBytesRead );
	
	return data_buffer;
}
void UART_Configuration::write(CString sendString)
{
	sendString.Append(CString("\r"));
	CStringA charstr(sendString);
	bWriteRC = WriteFile(m_hCom, (const char *)charstr, sendString.GetLength(), &iBytesWritten, NULL);
	iBytesWritten;
}
