
// DrawBootDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawBoot.h"
#include "DrawBootDlg.h"
#include "afxdialogex.h"

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


// CDrawBootDlg �Ի���



CDrawBootDlg::CDrawBootDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawBootDlg::IDD, pParent)
	, m_Edit(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawBootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PHOTO, m_Static);
	DDX_Text(pDX, IDC_WORD_EDIT, m_Edit);
	DDX_Control(pDX, IDC_WORD_EDIT, m_Word);
	DDX_Control(pDX, IDC_STATIC_HINT, m_static);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscomm);
	DDX_Control(pDX, IDC_EDIT_COMNUM, m_COM);
}

BEGIN_MESSAGE_MAP(CDrawBootDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_RADIO3, &CDrawBootDlg::OnBnClickedRadio3)
//	ON_EN_CHANGE(IDC_EDIT1, &CDrawBootDlg::OnEnChangeEdit1)
//	ON_BN_CLICKED(IDC_BUTTON1, &CDrawBootDlg::OnBnClickedButton1)
//	ON_EN_CHANGE(IDC_WORD_EDIT, &CDrawBootDlg::OnEnChangeWordEdit)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, &CDrawBootDlg::OnBnClickedApplyButton)
	ON_BN_CLICKED(IDC_EXIT_BUTTON, &CDrawBootDlg::OnBnClickedExitButton)
	//ON_BN_CLICKED(IDC_FAST_RADIO, &CDrawBootDlg::OnBnClickedFastRadio)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDrawBootDlg::OnNMCustomdrawSlider1)
	//ON_STN_CLICKED(IDC_STATIC_HINT, &CDrawBootDlg::OnStnClickedStaticHint)
	ON_BN_CLICKED(IDC_SETUP_BUTTON, &CDrawBootDlg::OnClickedSetupButton)
	ON_BN_CLICKED(IDC_BUTTON_SHOWDATA, &CDrawBootDlg::OnBnClickedButtonShowdata)
	ON_BN_CLICKED(IDC_BUTTON_OPENCOM, &CDrawBootDlg::OnBnClickedButtonOpencom)
END_MESSAGE_MAP()


// CDrawBootDlg ��Ϣ�������

BOOL CDrawBootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	
	/*
		��̬�ı�����ʾ����У��
	*/
	HBITMAP hBitmap;
	//����ͼƬID  
	hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1),  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
	 //���ָ��̬�ؼ���ָ��    
	pStatic = (CStatic *)GetDlgItem(IDC_STATIC_PHOTO);//�ؼ�ID     
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����    
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	 //���þ�̬�ؼ���ʾλͼ    
	pStatic->SetBitmap(hBitmap);

	//���ָ��̬�ؼ���ָ��    
	//pStatic = (CStatic *)GetDlgItem(IDC_STATIC_HINT);//�ؼ�ID
	//font.CreatePointFont(90, _T("Arial"), NULL);
	//pStatic->SetFont(&font);

	/*
		����ؼ���ʼ��

	*/
	
	//��ȡ��ǰ�����Ŀؼ�ָ��
	pSlide1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSlide1->SetRange(0, 100);//���ó�ʼ��Χ0~100
	pSlide1->SetPos(50);//���ó�ʼֵ
	strText1.Format(__T("%d"), pSlide1->GetPos());//��ʽ��
	SetDlgItemText(IDC_STATIC_SLIDER, strText1);

	/*
		��ʼ����ѡ��ť
	*/
	CButton *pB = (CButton *)GetDlgItem(IDC_SLOW_RADIO);
	pB->SetCheck(TRUE);
	//((CButton *)GetDlgItem(IDC_SLOW_RADIO))->GetCheck();// ����1��ʾѡ�ϣ�0��ʾûѡ��

	/*
		���ñ༭�����弰λ�ô�ֱ����
	*/

	font.CreatePointFont(240, _T("Arial"));
	m_Word.SetFont(&font);

	CRect rect;
	m_Word.GetClientRect(&rect);
	::OffsetRect(&rect, 0, 15);
	::SendMessageA(((CComboBox*)GetDlgItem(IDC_WORD_EDIT))->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

	/*
		���ñ����ֺ�
	*/
	//���ָ��̬�ؼ���ָ��    
	pStatic = (CStatic *)GetDlgItem(IDC_STATIC_TITLE);//�ؼ�ID
	pStatic->SetFont(&font);
	


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDrawBootDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDrawBootDlg::OnPaint()
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
HCURSOR CDrawBootDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CDrawBootDlg::WordData[16][16] = {0};
int CDrawBootDlg::book[16][16] = {0};
short CDrawBootDlg::Locate[600] = {0};
int CDrawBootDlg::locate = 0;

void CDrawBootDlg::OnBnClickedApplyButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i, j;
	CString str_send= NULL,str_temp = NULL;
	char table[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16 ; j++)
		{
			book[i][j] = WordData[i][j];
		}
	}
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 16 ; j++)
		{
			if (book[i][j] == 1)
			{
				//printf("(%d,%d)", j + 1, i + 1);
				book[i][j] = 0;
				DfsGetPath(i, j);
			}
		}
	}
	Locate[locate++] = 0;
	//Locate[locate] = 0;
	for (i = 0; i < locate; i ++)
	{
	//	unsigned int databuf = Locate[i] << 4;
	//	databuf |= Locate[i + 1];
		
		str_temp.Format(__T("%c"), table[Locate[i]]);
		str_send += str_temp;
		
		
	}
	m_mscomm.put_Output(COleVariant(str_send));//��������
}


void CDrawBootDlg::OnBnClickedExitButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);//�رմ���
		AfxMessageBox(_T("�����ѹر�"));
	}
	OnOK();//�˳�����
}


void CDrawBootDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰ�����Ŀؼ�ָ��
	pSlide1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int nPos = pSlide1->GetPos(); //��û���ĵ�ǰλ��
	strText1 = " ";
	strText1.Format(__T("%d%%"), nPos);
	SetDlgItemText(IDC_STATIC_SLIDER, strText1);

	*pResult = 0;
}



//������ð�ť���ö����ʼ�߶�
void CDrawBootDlg::OnClickedSetupButton()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDrawBootDlg::OnBnClickedButtonShowdata()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	char Wordbuf[32];  // �洢16�����ֵ���ģ
	
	GetDlgItemText(IDC_WORD_EDIT,m_Edit);
	int i=0 ,j = 0;
	char *pCharbuf = new char[10];
	unsigned char pc1,pc2;
	int iSize = WideCharToMultiByte(CP_ACP, 0, m_Edit, -1, NULL,0,NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, m_Edit, -1, pCharbuf, iSize, 0, 0);
	pc1 = pCharbuf[0];
	pc2 = pCharbuf[1];
	if (pc1 < 0xa1 || pc2 < 0xa1)
	{
		MessageBox(__T("������һ�����֣�"), __T("��ʾ"), MB_ICONINFORMATION);
		exit(0);
	}
	int n = (pc1 - 0xa1) * 94 + (pc2 - 0xa1);//�������ļ��е�λ��
	FILE *fp = fopen("E:\\zpeng\\VSprojects\\Hanzi\\Hanzi\\xiaobo16.DAT", "rb");
	if (fp == NULL)
	{
		MessageBox( __T("���ļ����� "), __T("��ʾ"), MB_ICONINFORMATION);
		exit(1);
	}
	fseek(fp, n * 32L, SEEK_SET);
	for (i = 0; i < 32; i++)
	{
		Wordbuf[i] = (char)fgetc(fp);
	}
	fclose(fp);
	for ( i = 0; i < 16; i++)
	{
		//printf("\n");
		for (j = 0; j < 16; j++)
		{
			if (Wordbuf[i * 2 + (j / 8)] & (0x80 >> (j % 8)))
			{
				WordData[i][j] = 1;
			}
			else
			{
				WordData[i][j] = 0;
			}
		}
	}

	CString str = NULL, tmp = NULL;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j< 16; j++)
		{
			tmp.Format(_T("%d "), WordData[i][j]);
			str += tmp;
		}
		str += __T("\r\n");
	}
	GetDlgItem(IDC_DOTDATA_EDIT)->SetWindowText(str);
	

	
}

void DfsGetPath(int x, int y)
{
	int next[4][2] = {
		{ 0, 1 },//����
		//{ 1, 1 },//����
		{ 1, 0 },//����
		//{1,-1},//����
		{ 0, -1 },//����
		//{-1,-1},//����
		{ -1, 0 },//����
		//	{-1,1}//����
	};
	int tx, ty, k;
	//int steps;
	for (k = 0; k < 4; k++)
	{
		//������һ���������
		tx = x + next[k][0];
		ty = y + next[k][1];
		//�ж��Ƿ�Խ��
		if (tx<0 || ty > 16 || ty<0 || tx > 16)
		{
			continue;
		}
		//�жϸõ��Ƿ��Ѿ�������
		if (CDrawBootDlg::WordData[tx][ty] == 1 && CDrawBootDlg::book[tx][ty] == 1)
		{
			//SendLocation(tx, ty);
			CDrawBootDlg::Locate[CDrawBootDlg::locate++] = ty ;
			CDrawBootDlg::Locate[CDrawBootDlg::locate++] = tx ;
			//m_mscomm.put_Output(COleVariant(m_EditSend));//��������
			CDrawBootDlg::book[tx][ty] = 0;//�����������߹�
			DfsGetPath(tx, ty);//��ʼѰ����һ����
			//book[tx][ty] = 1;//ȡ�����
			//addsomeprocess(tx, ty);
		}
	}

	return;

}


BEGIN_EVENTSINK_MAP(CDrawBootDlg, CDialogEx)
	ON_EVENT(CDrawBootDlg, IDC_MSCOMM1, 1, CDrawBootDlg::OnOncommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()

void CDrawBootDlg::OnBnClickedButtonOpencom()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString portnums = __T("0");
	m_COM.GetWindowText(portnums);
	int flag = _ttoi(portnums);
	if (flag)//�������Ĵ��ڱ��Ϊ����������ִ����������
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		m_mscomm.put_CommPort(flag); //ѡ��COM
		m_mscomm.put_InBufferSize(1024); //���ջ�����
		m_mscomm.put_OutBufferSize(1024);//���ͻ�����
		m_mscomm.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0,��ʾȫ����ȡ
		m_mscomm.put_InputMode(1);//�Զ����Ʒ�ʽ��д����
		m_mscomm.put_RThreshold(1);//���ջ�������1����1�������ַ�ʱ���������������ݵ�OnComm
		m_mscomm.put_Settings(_T("9600,n,8,1"));//������9600�޼���λ��8������λ��1��ֹͣλ
		if (!m_mscomm.get_PortOpen())//�������û�д����
		{
			m_mscomm.put_PortOpen(TRUE);//�򿪴���
			AfxMessageBox(_T("���ڴ򿪳ɹ�"));
		}
		else
		{
			m_mscomm.put_OutBufferCount(0);
			AfxMessageBox(_T("���ڴ�ʧ��"));
		}
	}
	else
	{
		AfxMessageBox(_T("����������Ҫ�򿪴��ڱ��"));
	}
}



void CDrawBootDlg::OnOncommMscomm1()
{
	// TODO:  �ڴ˴������Ϣ����������
}

