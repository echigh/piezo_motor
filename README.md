# piezo_motor
piezo_motor driver and get data task in qtech

module:
1.CSerialPort class, i modified it to recieve 1382400 baud rate.
2.use CClientDC to draw line.
3.use QueryDosDeviceA function to query available port.
4.1)use ResetContent to clear all terms in combobox, and then use init_CComboBox to refresh them.
  2)use ON_CBN_DROPDOWN to triger above.
5.use _wtoi to convert CString to integer.
