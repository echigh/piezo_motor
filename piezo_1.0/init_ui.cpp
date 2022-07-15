#include "stdafx.h"
#include "piezo_1.0.h"
#include "piezo_1.0Dlg.h"
#include "afxdialogex.h"


void Cpiezo_10Dlg::init_CComboBox()
{
	for (int i = 0; i < 20; ++i)
	{
		TCHAR comName[32];
		wsprintf(comName, L"COM %d", i + 1);
		m_PortCombobox_STM32.InsertString(m_PortCombobox_STM32.GetCount(), comName);
	}
	m_PortCombobox_STM32.SetCurSel(0);

	int baudRate[] = { 9600, 14400, 19200, 38400, 56000, 57600, 115200,
	128000, 230400, 256000, 460800, 921600, 1382400};
	for (int i = 0; i < ARRAYSIZE(baudRate); ++i)
	{
		TCHAR brateName[32];
		wsprintf(brateName, L"%d", baudRate[i]);
		m_BaudrateCombobox_STM32.InsertString(m_BaudrateCombobox_STM32.GetCount(), brateName);
	}
	m_BaudrateCombobox_STM32.SetCurSel(0);

	for (int i = 0; i < 20; ++i)
	{
		TCHAR comName[32];
		wsprintf(comName, L"COM %d", i + 1);
		m_PortCombobox_LASER.InsertString(m_PortCombobox_LASER.GetCount(), comName);
	}
	m_PortCombobox_LASER.SetCurSel(0);

	//int baudRate[] = { 9600, 14400, 19200, 38400, 56000, 57600, 115200 };
	for (int i = 0; i < ARRAYSIZE(baudRate); ++i)
	{
		TCHAR brateName[32];
		wsprintf(brateName, L"%d", baudRate[i]);
		m_BaudrateCombobox_LASER.InsertString(m_BaudrateCombobox_LASER.GetCount(), brateName);
	}
	m_BaudrateCombobox_LASER.SetCurSel(0);
}
