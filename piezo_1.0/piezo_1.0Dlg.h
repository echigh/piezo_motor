
// piezo_1.0Dlg.h : ͷ�ļ�
//

#pragma once

#include "serialport.h"

// Cpiezo_10Dlg �Ի���
class Cpiezo_10Dlg : public CDialogEx
{
// ����
public:
	Cpiezo_10Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PIEZO_10_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStm32();
	afx_msg void OnBnClickedButtonLaser();
	afx_msg void OnBnClickedButtonSendStm32Order();
	afx_msg void OnCbnDropdownStm32();
	afx_msg void OnCbnDropdownLaser();
	afx_msg LONG OnCommunication(WPARAM ch, LPARAM port);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CComboBox m_PortCombobox_STM32;
	CComboBox m_BaudrateCombobox_STM32;
	CComboBox m_PortCombobox_LASER;
	CComboBox m_BaudrateCombobox_LASER;
	CStatic m_Curve;
	CEdit m_edit_calibration;

	CSerialPort m_Comm_STM32;
	CSerialPort m_Comm_LASER;

	void init_CComboBox();

	int i_stm32_data = 0;
	int i_laser_data = 0;
	afx_msg void OnBnClickedButtonCalibrate();
};
