
// DrawBootDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawBoot.h"
#include "DrawBootDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDrawBootDlg 对话框



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


// CDrawBootDlg 消息处理程序

BOOL CDrawBootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	
	/*
		静态文本框显示北大校徽
	*/
	HBITMAP hBitmap;
	//关联图片ID  
	hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1),  IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
	 //获得指向静态控件的指针    
	pStatic = (CStatic *)GetDlgItem(IDC_STATIC_PHOTO);//控件ID     
	//设置静态控件的样式，使其可以使用位图，并试位标显示使居中    
	pStatic->ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	 //设置静态控件显示位图    
	pStatic->SetBitmap(hBitmap);

	//获得指向静态控件的指针    
	//pStatic = (CStatic *)GetDlgItem(IDC_STATIC_HINT);//控件ID
	//font.CreatePointFont(90, _T("Arial"), NULL);
	//pStatic->SetFont(&font);

	/*
		滑块控件初始化

	*/
	
	//获取当前操作的控件指针
	pSlide1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	pSlide1->SetRange(0, 100);//设置初始范围0~100
	pSlide1->SetPos(50);//设置初始值
	strText1.Format(__T("%d"), pSlide1->GetPos());//格式化
	SetDlgItemText(IDC_STATIC_SLIDER, strText1);

	/*
		初始化单选按钮
	*/
	CButton *pB = (CButton *)GetDlgItem(IDC_SLOW_RADIO);
	pB->SetCheck(TRUE);
	//((CButton *)GetDlgItem(IDC_SLOW_RADIO))->GetCheck();// 返回1表示选上，0表示没选上

	/*
		设置编辑框字体及位置垂直居中
	*/

	font.CreatePointFont(240, _T("Arial"));
	m_Word.SetFont(&font);

	CRect rect;
	m_Word.GetClientRect(&rect);
	::OffsetRect(&rect, 0, 15);
	::SendMessageA(((CComboBox*)GetDlgItem(IDC_WORD_EDIT))->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

	/*
		设置标题字号
	*/
	//获得指向静态控件的指针    
	pStatic = (CStatic *)GetDlgItem(IDC_STATIC_TITLE);//控件ID
	pStatic->SetFont(&font);
	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawBootDlg::OnPaint()
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
	// TODO:  在此添加控件通知处理程序代码
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
	m_mscomm.put_Output(COleVariant(str_send));//发送数据
}


void CDrawBootDlg::OnBnClickedExitButton()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_mscomm.get_PortOpen())
	{
		m_mscomm.put_PortOpen(FALSE);//关闭串口
		AfxMessageBox(_T("串口已关闭"));
	}
	OnOK();//退出程序
}


void CDrawBootDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	//获取当前操作的控件指针
	pSlide1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	int nPos = pSlide1->GetPos(); //获得滑块的当前位置
	strText1 = " ";
	strText1.Format(__T("%d%%"), nPos);
	SetDlgItemText(IDC_STATIC_SLIDER, strText1);

	*pResult = 0;
}



//点击设置按钮设置舵机初始高度
void CDrawBootDlg::OnClickedSetupButton()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDrawBootDlg::OnBnClickedButtonShowdata()
{
	// TODO:  在此添加控件通知处理程序代码
	char Wordbuf[32];  // 存储16点阵汉字的字模
	
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
		MessageBox(__T("请输入一个汉字！"), __T("提示"), MB_ICONINFORMATION);
		exit(0);
	}
	int n = (pc1 - 0xa1) * 94 + (pc2 - 0xa1);//计算在文件中的位置
	FILE *fp = fopen("E:\\zpeng\\VSprojects\\Hanzi\\Hanzi\\xiaobo16.DAT", "rb");
	if (fp == NULL)
	{
		MessageBox( __T("打开文件错误！ "), __T("提示"), MB_ICONINFORMATION);
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
		{ 0, 1 },//向右
		//{ 1, 1 },//右下
		{ 1, 0 },//向下
		//{1,-1},//左下
		{ 0, -1 },//向左
		//{-1,-1},//左上
		{ -1, 0 },//向上
		//	{-1,1}//右上
	};
	int tx, ty, k;
	//int steps;
	for (k = 0; k < 4; k++)
	{
		//计算下一个点的坐标
		tx = x + next[k][0];
		ty = y + next[k][1];
		//判断是否越界
		if (tx<0 || ty > 16 || ty<0 || tx > 16)
		{
			continue;
		}
		//判断该点是否已经遍历过
		if (CDrawBootDlg::WordData[tx][ty] == 1 && CDrawBootDlg::book[tx][ty] == 1)
		{
			//SendLocation(tx, ty);
			CDrawBootDlg::Locate[CDrawBootDlg::locate++] = ty ;
			CDrawBootDlg::Locate[CDrawBootDlg::locate++] = tx ;
			//m_mscomm.put_Output(COleVariant(m_EditSend));//发送数据
			CDrawBootDlg::book[tx][ty] = 0;//标记这个点已走过
			DfsGetPath(tx, ty);//开始寻找下一个点
			//book[tx][ty] = 1;//取消标记
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
	// TODO:  在此添加控件通知处理程序代码
	CString portnums = __T("0");
	m_COM.GetWindowText(portnums);
	int flag = _ttoi(portnums);
	if (flag)//如果输入的串口编号为正整数，才执行下列命令
	{
		if (m_mscomm.get_PortOpen())
		{
			m_mscomm.put_PortOpen(FALSE);
		}
		m_mscomm.put_CommPort(flag); //选择COM
		m_mscomm.put_InBufferSize(1024); //接收缓冲区
		m_mscomm.put_OutBufferSize(1024);//发送缓冲区
		m_mscomm.put_InputLen(0);//设置当前接收区数据长度为0,表示全部读取
		m_mscomm.put_InputMode(1);//以二进制方式读写数据
		m_mscomm.put_RThreshold(1);//接收缓冲区有1个及1个以上字符时，将引发接收数据的OnComm
		m_mscomm.put_Settings(_T("9600,n,8,1"));//波特率9600无检验位，8个数据位，1个停止位
		if (!m_mscomm.get_PortOpen())//如果串口没有打开则打开
		{
			m_mscomm.put_PortOpen(TRUE);//打开串口
			AfxMessageBox(_T("串口打开成功"));
		}
		else
		{
			m_mscomm.put_OutBufferCount(0);
			AfxMessageBox(_T("串口打开失败"));
		}
	}
	else
	{
		AfxMessageBox(_T("请先输入需要打开串口编号"));
	}
}



void CDrawBootDlg::OnOncommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
}

