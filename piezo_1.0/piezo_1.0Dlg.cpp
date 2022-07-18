
// piezo_1.0Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "piezo_1.0.h"
#include "piezo_1.0Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define REV_TIMER 0

#define UART_BUFF_LEN 5000000
static unsigned char m_stm32_data[UART_BUFF_LEN];
static unsigned char m_laser_data[UART_BUFF_LEN];

//picture control
int pic_height = 0, pic_width = 0;
int x_start = 0, y_start = 0;
int x_end = 0, y_end = 0;

Cpiezo_10Dlg::Cpiezo_10Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cpiezo_10Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpiezo_10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_STM32_COM, m_PortCombobox_STM32);
	DDX_Control(pDX, IDC_COMBO_STM32_BAUD, m_BaudrateCombobox_STM32);
	DDX_Control(pDX, IDC_COMBO_LASER_COM, m_PortCombobox_LASER);
	DDX_Control(pDX, IDC_COMBO_LASER_BAUD, m_BaudrateCombobox_LASER);
	DDX_Control(pDX, IDC_Curve, m_Curve);
	
}

BEGIN_MESSAGE_MAP(Cpiezo_10Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STM32, &Cpiezo_10Dlg::OnBnClickedButtonStm32)
	ON_BN_CLICKED(IDC_BUTTON_LASER, &Cpiezo_10Dlg::OnBnClickedButtonLaser)
	ON_BN_CLICKED(IDC_BUTTON_SEND_STM32_ORDER, &Cpiezo_10Dlg::OnBnClickedButtonSendStm32Order)
	ON_MESSAGE(WM_COMM_RXCHAR, OnCommunication)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cpiezo_10Dlg 消息处理程序

BOOL Cpiezo_10Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	init_CComboBox();
	SetTimer(REV_TIMER, 500, 0);

	//picture control
	CRect *rc = (CRect *)malloc(sizeof(CRect));
	m_Curve.GetWindowRect(rc);
	printf("left:%d\r\n", rc->left);
	printf("right:%d\r\n", rc->right);
	printf("top:%d\r\n", rc->top);
	printf("bottom:%d\r\n", rc->bottom);
	pic_height = rc->bottom - rc->top;
	pic_width = rc->right - rc->left;
	free(rc);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cpiezo_10Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cpiezo_10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cpiezo_10Dlg::OnBnClickedButtonStm32()
{
	m_Comm_STM32.ClosePort();
	m_Comm_STM32.CloseListenTread();

	CString port;
	m_PortCombobox_STM32.GetWindowTextW(port);
	CString baudRate;
	m_BaudrateCombobox_STM32.GetWindowTextW(baudRate);

	int portNumber = 0;
	const int spaceIdx = port.Find(L" ");
	if (spaceIdx > 0)
		portNumber = _wtoi(&port.GetBuffer()[spaceIdx]);

	if (!m_Comm_STM32.InitPort(this, portNumber, _wtoi(baudRate)))
	{
		printf("com for Stm32 open fail.\r\n");
	}
	m_Comm_STM32.p_uart_rev_buff = m_stm32_data;

	if (!m_Comm_STM32.OpenListenThread())
	{
		printf("com for Stm32 OpenListenThread fail.\r\n");
	}
}


void Cpiezo_10Dlg::OnBnClickedButtonLaser()
{
	m_Comm_LASER.ClosePort();
	m_Comm_LASER.CloseListenTread();

	CString port;
	m_PortCombobox_LASER.GetWindowTextW(port);
	CString baudRate;
	m_BaudrateCombobox_LASER.GetWindowTextW(baudRate);

	int portNumber = 0;
	const int spaceIdx = port.Find(L" ");
	if (spaceIdx > 0)
		portNumber = _wtoi(&port.GetBuffer()[spaceIdx]);

	if (!m_Comm_LASER.InitPort(this, portNumber, _wtoi(baudRate)))
	{
		printf("com for laser open fail.\r\n");
	}
	m_Comm_LASER.p_uart_rev_buff = m_laser_data;

	if (!m_Comm_LASER.OpenListenThread())
	{
		printf("com for laser OpenListenThread fail.\r\n");
	}

}


void Cpiezo_10Dlg::OnBnClickedButtonSendStm32Order()
{
	unsigned char test[] = { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x0d, 0x0a};
	m_Comm_STM32.WriteData(test, 7);
	printf("OnBnClickedButtonSendStm32Order\r\n");
}

LONG Cpiezo_10Dlg::OnCommunication(WPARAM ch, LPARAM port)
{

	if (port == m_Comm_STM32.m_nPortNr)
	{
		unsigned int len_stm32_data = m_Comm_STM32.char_counter;
		unsigned int i_stm32_data = 0;
		unsigned char * p_temp = m_Comm_STM32.p_uart_rev_buff;
		unsigned char compared = p_temp[0];
		
		for (i_stm32_data = 0; i_stm32_data < len_stm32_data; i_stm32_data++)
		{
			if (compared++ != p_temp[i_stm32_data])
			{
				printf("difference start at index:%d\r\n", i_stm32_data);
				printf("%02x %02x\r\n", p_temp[i_stm32_data-1], p_temp[i_stm32_data]);
				getchar();
				break;
			}
		}
		printf("compare work has been done.\r\n");
		printf("len_stm32_data is: %d\r\n", len_stm32_data);
		getchar();
		for (i_stm32_data = 0; i_stm32_data < 512; i_stm32_data++)
		{
			printf("%02x ", p_temp[i_stm32_data]);
		}
		printf("\r\n");
	}

	if (port == m_Comm_LASER.m_nPortNr)
	{
		
	}

	return 0;
}

void Cpiezo_10Dlg::OnTimer(UINT_PTR nIDEvent)
{

	if (nIDEvent == REV_TIMER)	//判断是哪个定时器触发的
	{
		if (m_Comm_STM32.char_counter > 5)
		{
			unsigned int i_stm32_data = 0;
			unsigned char * p_temp = m_Comm_STM32.p_uart_rev_buff;
			printf("m_Comm_STM32: ");
			for (i_stm32_data = 0; i_stm32_data < 5; i_stm32_data++)
			{
				printf("%02x ", p_temp[i_stm32_data]);
			}
			printf("\r\n");
		}
		if (m_Comm_LASER.char_counter > 100000)
		{
			unsigned int i_laser_data = 0;
			unsigned char * p_temp = m_Comm_LASER.p_uart_rev_buff;
			printf("m_Comm_LASER: ");
			for (i_laser_data = 0; i_laser_data < 16; i_laser_data++)
			{
				printf("%02x ", p_temp[i_laser_data]);
			}
			printf("\r\n");
		}
		//printf("\n +==========================================+\n");
	}

	/*pic control*/
	x_start = x_end;
	y_start = y_end;
	x_end = x_end + 10;
	y_end = y_end + 10;
	CClientDC dc_pic(GetDlgItem(IDC_Curve));
	printf("\r\nx_start:%d,y_start:%d,x_end:%d,y_end:%d\r\n", x_start, y_start, x_end, y_end);
	dc_pic.MoveTo(x_start, y_start);
	dc_pic.LineTo(x_end, y_end);
}