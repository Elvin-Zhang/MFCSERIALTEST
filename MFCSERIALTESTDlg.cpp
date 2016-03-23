
// MFCSERIALTESTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSERIALTEST.h"
#include "MFCSERIALTESTDlg.h"
#include "afxdialogex.h"
#include "SERIALPORT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSERIALTESTDlg �Ի���



CMFCSERIALTESTDlg::CMFCSERIALTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSERIALTESTDlg::IDD, pParent)
	, m_Receive(_T(""))
	, m_Send(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSERIALTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Receive);
	DDX_Text(pDX, IDC_EDIT2, m_Send);
	DDX_Control(pDX, IDC_COMBO2, m_ComPortNO);
	DDX_Control(pDX, IDC_COMBO1, m_PortBaud);
	DDX_Control(pDX, IDC_COMBO3, m_PortDataBits);
	DDX_Control(pDX, IDC_COMBO4, m_PortStopBits);
	DDX_Control(pDX, IDC_COMBO5, m_PortParity);
}

BEGIN_MESSAGE_MAP(CMFCSERIALTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCSERIALTESTDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCSERIALTESTDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCSERIALTESTDlg::OnBnClicked_ClosePort)
	ON_MESSAGE(WM_COMM_RXCHAR, &CMFCSERIALTESTDlg::OnRecvData)
END_MESSAGE_MAP()

// CMFCSERIALTESTDlg ��Ϣ��������

BOOL CMFCSERIALTESTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ����Ӷ���ĳ�ʼ������
	//m_SerialPort = new CSerialPort();
	m_SerialPort.Hkey2ComboBox(m_ComPortNO);
	m_PortBaud.SetCurSel(6);
	m_PortDataBits.SetCurSel(0);
	m_PortStopBits.SetCurSel(0);
	m_PortParity.SetCurSel(0);

	count = 0;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCSERIALTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCSERIALTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCSERIALTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMFCSERIALTESTDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	/*
	CString recvStr((char *)wParam);
	m_Receive += recvStr;
	for (int k = 0; k < lParam; k++)
	{
		m_Send += (char *)wParam + k;
	}
	UpdateData(false);
	return TRUE;
	*/
	count++;
	m_Receive.Format(_T("%d"), count);
	//m_Receive += "���յ����ݣ�";
	UpdateData(FALSE);
	//count = 0;
	return TRUE;
}

//�򿪴���
void CMFCSERIALTESTDlg::OnBnClickedButton1()
{
	//int portnr = ;
	CString portnrStr;
	UINT portnr;
	UINT baud;
	//UINT parityNum;
	char parity;
	UINT databits;
	UINT stopbits;
	
	m_ComPortNO.GetLBText(m_ComPortNO.GetCurSel(), portnrStr);
	for (int i = 3; i < portnrStr.GetLength(); i++)
	{
		char ch = portnrStr[i];
		//portnr = (UINT)ch;
		m_Receive += ch;
		UpdateData(FALSE);
	}
	portnr = atoi(m_Receive);
	m_Receive = "";
	//110;300;600;1200;2400;4800;9600;14400;19200;28800;38400;56000;57600;115200;128000;256000;
	switch (m_PortBaud.GetCurSel())
	{
		case 0:
			baud = 110;
			break;
		case 1:
			baud = 300;
			break;
		case 2:
			baud = 600;
			break;
		case 3:
			baud = 1200;
			break;
		case 4:
			baud = 2400;
			break;
		case 5:
			baud = 4800;
			break;
		case 6:
			baud = 9600;
			break;
		case 7:
			baud = 14400;
			break;
		case 8:
			baud = 19200;
			break;
		case 9:
			baud = 28800;
			break;
		case 10:
			baud = 38400;
			break;
		case 11:
			baud = 56000;
			break;
		case 12:
			baud = 57600;
			break;
		case 13:
			baud = 115200;
			break;
		case 14:
			baud = 128000;
			break;
		case 15:
			baud = 256000;
			break;
		default:
			break;
	}
	//None��;Odd��;Evenż;Mark 1;Space 0;
	switch (m_PortParity.GetCurSel())
	{
	case 0:
		parity = 'N';
		break;
	case 1:
		parity = 'O';
		break;
	case 2:
		parity = 'E';
		break;
	case 3:
		parity = 'M';
		break;
	case 4:
		parity = 'S';
		break;
	default:
		break;
	}

	stopbits = m_PortStopBits.GetCurSel();
	
	switch (m_PortDataBits.GetCurSel())
	{
	case 0:
		databits = 8;
		break;
	case 1:
		databits = 7;
		break;
	case 2:
		databits = 6;
		break;
	case 3:
		databits = 5;
		break;
	case 4:
		databits = 4;
		break;
	default:
		break;
	}

	BOOL IsOpen = m_SerialPort.InitPort(this, portnr, baud, parity, databits, stopbits, EV_RXCHAR | EV_RXFLAG, 1024, 1, 1, 1, 1, 1);
	//�жϴ����Ƿ��
	if (IsOpen)
	{
		AfxMessageBox(_T("�ɹ��򿪴���"));
	}
	else
	{
		AfxMessageBox(_T("�򿪴���ʧ�ܣ������´򿪣�"));
	}

	if (m_SerialPort.StartMonitoring())
	{
		AfxMessageBox(_T("�����߳��ѳɹ�����"));
	}
}

void CMFCSERIALTESTDlg::OnBnClickedButton3()
{
	m_Receive = "";
	UpdateData(false);
}


void CMFCSERIALTESTDlg::OnBnClicked_ClosePort()
{
	m_SerialPort.ClosePort();
}