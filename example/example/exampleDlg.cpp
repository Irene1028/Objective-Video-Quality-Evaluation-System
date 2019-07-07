
// exampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "example.h"
#include "exampleDlg.h"
#include "afxdialogex.h"
#include <math.h>
//#include <GaussBlurFilter.hpp>

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


// CexampleDlg 对话框




CexampleDlg::CexampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CexampleDlg::IDD, pParent)
	, open_path(_T(""))
	, width(0)
	, height(0)
	, gaosi_path(_T(""))
	, Dv(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CexampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, open_path);
	DDX_Text(pDX, IDC_EDIT3, width);
	DDX_Text(pDX, IDC_EDIT4, height);
	DDX_Text(pDX, IDC_EDIT2, gaosi_path);
	DDX_Text(pDX, IDC_EDIT5, Dv);
}

BEGIN_MESSAGE_MAP(CexampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_open, &CexampleDlg::OnBnClickedopen)
	ON_BN_CLICKED(IDC_gaosi, &CexampleDlg::OnBnClickedgaosi)
	ON_BN_CLICKED(IDC_cal, &CexampleDlg::OnBnClickedcal)
END_MESSAGE_MAP()


// CexampleDlg 消息处理程序

BOOL CexampleDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CexampleDlg::OnPaint()
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
HCURSOR CexampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexampleDlg::OnBnClickedopen()//打开一个视频存入指定位置
{
	UpdateData(true);
	
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
		open_path=dlg.GetPathName();
	open_path.Format(open_path);
	UpdateData(false);
	mFile.Open(open_path,CFile::modeRead);
	if(mFile.GetLength()<2)
		return;
	number=mFile.GetLength();
	frame=mFile.GetLength()/(width*height*3/2);
	sRead = new unsigned char[number+1];
	mFile.Read(sRead,mFile.GetLength());
	mFile.Close();
	// TODO: 在此添加控件通知处理程序代码//打开一个视频把他写入数组
}


void CexampleDlg::OnBnClickedgaosi()////高斯处理并且直接计算Savg并且输出高斯模糊过的视频
{
	UpdateData(true);
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
		gaosi_path=dlg.GetPathName();
	gaosi_path.Format(gaosi_path);
	
	CFile out;
	sR1=sRead;//sR1是sRead的替身，专门负责移位，防止sRead移位带来麻烦
	sGauss = new unsigned char[width*height*frame+1];
	sR2=sGauss;//sR2是sGauss的替身，专门负责移位，防止sGauss移位带来麻烦
	double Savg[250];//数组存储每一针的Savg
	SAVG_AVER=0;//Savg初始化

	//高斯处理
	if(out.Open(gaosi_path,CFile::modeCreate|CFile::modeWrite))
	{
		sR2=sGauss;
		for(i=0;i<frame;i++)
		{
			Savg[i]=0;
			for(k=0;k<height;k++)
			{
				if(k==0)//第一行原值填充
				{
					for(j=0;j<width;j++)
					{
					sR2[j]=sR1[j];
					}
				}
				else if(k==(height-1))//最后一行原值填充
				{
					for(j=0;j<width;j++)
					sR2[j]=sR1[j];
				}
				else//其他中间行
				{
					for(j=0;j<width;j++)
					{
						if(j==0)//第一个点原值填充
							sR2[j]=sR1[j];
						else if(j==(width-1))//最后一个点原值填充
							sR2[j]=sR1[j];
						else
						{
							sR2[j]=(sR1[j]*4+(sR1[-1+j]+sR1[1+j]+sR1[width+j]+sR1[-width+j])*2+(sR1[width+j+1]+sR1[width+j-1]+sR1[-width+j+1]+sR1[-width+j-1])*1)/16.0;
							//高斯的核心处理！
							Savg[i]+=abs(sR1[j]-sR2[j]);
							//每一点的Savg加和
							
						}
					}
					
				}
				out.Write(sR2,width);//每一行高斯过的写出
				sR1+=width;
				sR2+=width;
				
			}
			sR1+=width*height/2;
			Savg[i]=Savg[i]/(width*height);//每一针的Savg之和求得一针的平均值
			SAVG_AVER+=Savg[i];//算250针的加和
			//out.Write(sR2-height*width,height*width);//可以试着一针一针写出，速度更快呦
		}
		out.Close();
		SAVG_AVER=SAVG_AVER/frame;//算250针的平均值
	}

	
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CexampleDlg::OnBnClickedcal()
{
	UpdateData(true);
	//局部失真
	//水平
	double *sh=new double[480*272];
	double sh_Sum=0;
	double sh_Aver[250];
	double fangcha[250];
	double fc=0;
	double FC_AVER=0;
	double num;
	sR1=sRead;
	for(i=0;i<frame;i++)
	{
		sh_Sum=0;
		for(k=0;k<height;k++)
		{
			for(j=0;j<width-1;j++)
			{
				sh[k*(width-1)+j]=abs(sR1[j]-sR1[j+1]);//计算每一点Sh的值存入sh[]
				sh_Sum+=sh[k*(width-1)+j];//每一点的sh 值加和
			}
			sR1+=width;//跳行
		}
		sh_Aver[i]=sh_Sum/(479*272);//计算每一针sh均值存入sh_Aver[i]

		fc=0;//定义一个方差变量方便计算
		for(j=0;j<((width-1)*height);j++)
		{
			fc+=pow(sh[j]-sh_Aver[i],2);
		}
		fangcha[i]=sqrt(fc/((width-1)*height));//算出方差之后开方得到标准差（每针存入fangcha[i]）
		FC_AVER+=fangcha[i];//250针标准差加和
		num=width*height*(1/2);
		sR1+=(char)num;
	}
	FC_AVER=FC_AVER/frame;//标准差求平均

	//垂直（算法和水平一样只是各种数组和指针后面加2表示）
	double *sh2=new double[480*271];
	double sh_Sum2=0;
	double sh_Aver2[250];
	double fangcha2[250];
	double fc2=0;
	double FC_AVER2=0;
	double num2;
	sR1=sRead;
	for(i=0;i<frame;i++)
	{
		sh_Sum2=0;
		for(k=0;k<width;k++)
		{
			for(j=0;j<(height-1);j++)
			{
				sh2[k*(height-1)+j]=abs(sR1[j]-sR1[j+width]);
				sh_Sum2+=sh2[k*(height-1)+j]; 
			}
			sR1+=height;
		}
		sh_Aver2[i]=sh_Sum2/(width*(height-1));

		fc2=0;
		for(j=0;j<((width-1)*height);j++)
		{
			fc2+=pow(sh[j]-sh_Aver[i],2);
		}
		fangcha2[i]=sqrt(fc2/((width-1)*height));
		FC_AVER2+=fangcha2[i];

		num2=(height*width*(1/2));
		sR1+=(char)num2;
	}
	FC_AVER2=FC_AVER2/frame;

	Dv=(FC_AVER+FC_AVER2)/2+SAVG_AVER;//水平的和垂直的取平均然后加上Savg得到最终的评价指标
	
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}
