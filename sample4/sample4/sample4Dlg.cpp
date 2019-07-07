
// sample4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "sample4.h"
#include "sample4Dlg.h"
#include "afxdialogex.h"
#include <math.h>
#include "mysql.h"
#pragma comment (lib, "libmysql.lib")

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


// Csample4Dlg 对话框




Csample4Dlg::Csample4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csample4Dlg::IDD, pParent)
	, input1(_T(""))
	, input2(_T(""))
	, out_path(_T(""))
	, psnr_aver(0)
	, width(0)
	, height(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csample4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, input1);
	DDX_Text(pDX, IDC_EDIT4, input2);
	DDX_Text(pDX, IDC_EDIT5, out_path);
	DDX_Text(pDX, IDC_EDIT6, psnr_aver);
	DDX_Text(pDX, IDC_EDIT1, width);
	DDX_Text(pDX, IDC_EDIT2, height);
	DDX_Control(pDX, IDC_PROGRESS1, m_hThread);
}

BEGIN_MESSAGE_MAP(Csample4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Csample4Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_open, &Csample4Dlg::OnBnClickedopen)
	ON_BN_CLICKED(IDC_on, &Csample4Dlg::OnBnClickedon)
	ON_BN_CLICKED(IDC_pause, &Csample4Dlg::OnBnClickedpause)
	ON_BN_CLICKED(IDC_stop, &Csample4Dlg::OnBnClickedstop)
	ON_BN_CLICKED(IDC_open1, &Csample4Dlg::OnBnClickedopen1)
	ON_BN_CLICKED(IDC_open2, &Csample4Dlg::OnBnClickedopen2)
	ON_BN_CLICKED(IDC_out, &Csample4Dlg::OnBnClickedout)
	ON_BN_CLICKED(IDC_PSNR, &Csample4Dlg::OnBnClickedPsnr)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &Csample4Dlg::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()


// Csample4Dlg 消息处理程序

BOOL Csample4Dlg::OnInitDialog()
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

void Csample4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Csample4Dlg::OnPaint()
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
HCURSOR Csample4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Csample4Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedopen()
{
	CString file_name = "";  
    CFileDialog fd(TRUE,  NULL,   
                   file_name,   
                   OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,   
                   NULL, NULL);  
      
    if (fd.DoModal() == IDOK)   
    {  
        m_PlayControl.Init(::GetDlgItem(GetSafeHwnd(),IDC_VIDEO),   
            fd.GetPathName().GetBuffer(fd.GetPathName().GetLength()));  
          
        m_PlayControl.PostThreadMessage(WM_MANAGE, 0, 0);  
    }  

	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedon()
{
	m_PlayControl.Play();  
	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedpause()
{
	m_PlayControl.Pause(); 
	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedstop()
{
	m_PlayControl.Stop();
	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedopen1()//打开第一个序列存入指定位置
{
	UpdateData(true);
	
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
		input1=dlg.GetPathName();
	input1.Format(input1);
	UpdateData(false);
	mFile.Open(input1,CFile::modeRead);
	if(mFile.GetLength()<2)
		return;
	number=mFile.GetLength();
	frame=mFile.GetLength()/(width*height*3.0/2);
	sRead = new unsigned char[number+1];
	mFile.Read(sRead,mFile.GetLength());
	mFile.Close();

	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedopen2()//打开第2个序列存入指定位置
{
	UpdateData(true);
	
	CFileDialog dlg(TRUE);
	if(dlg.DoModal()==IDOK)
		input2=dlg.GetPathName();
	input2.Format(input2);
	UpdateData(false);
	mFile2.Open(input2,CFile::modeRead);
	if(mFile2.GetLength()<2)
		return;
	number2=mFile2.GetLength();
	frame2=mFile2.GetLength()/(width*height*3.0/2);
	sRead2 = new unsigned char[number2+1];
	mFile2.Read(sRead2,mFile2.GetLength());
	mFile2.Close();

	// TODO: 在此添加控件通知处理程序代码
}



void Csample4Dlg::OnBnClickedout()//输出对角拼接后的视频
{
	UpdateData(true);
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
		out_path=dlg.GetPathName();
	out_path.Format(out_path);
	UpdateData(false);
	CFile out;
	sR1=sRead;//sRead1,sRead2是存序列的指针，sR1,sR2是为了避免存储的指针移位带来麻烦而定义的新指针，专门负责移位
	sR2=sRead2;
	if(out.Open(out_path,CFile::modeCreate|CFile::modeWrite))
	{
		for(i=0;i<frame;i++)/////////桢循环
		{
			for(k=0;k<height;k++)////////////行循环
			{
				for(j=0;j<(int)(width-(1.764*k));j++)
				{
					out.Write(sR1+j,1);
				}
				sR1+=width;//sR1,sR2是为了避免存储的指针移位带来麻烦而定义的新指针，相当于大家的buffer
				for(j;j<width;j++)
				{
					out.Write(sR2+j,1);
				}
				sR2+=width;//sR1,sR2是为了避免存储的指针移位带来麻烦而定义的新指针，相当于大家的buffer
				
			}
			for(k;k<height*3/2;k++)
			{
				for(c=0;c<(int)(width/2-1.764*(k-height));c++)
				{
					out.Write(sR1+c,1);
				}
				sR1+=width*1/2;
				for(c;c<width/2;c++)
				{
					out.Write(sR2+c,1);
				}
				sR2+=width*1/2;
			}
			for(k;k<height*2;k++)
			{
				for(c=0;c<(int)(width/2-1.764*(k-height*3/2));c++)
				{
					out.Write(sR1+c,1);
				}
				sR1+=width*1/2;
				for(c;c<width/2;c++)
				{
					out.Write(sR2+c,1);
				}
				sR2+=width*1/2;
			}

			//只做灰度的时候跳过UV用下面两行代码
			//sRead+=height*width*1/2;
			//sRead2+=height*width*1/2;
		}
		out.Close();
	}

	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnBnClickedPsnr()
{
	UpdateData(true);


	///////////////////////////////////////////////
	//连数据库部分
	mysql_library_init(0,NULL,NULL);
	MYSQL *mysql;
	mysql= (MYSQL *)malloc(sizeof(MYSQL));
	mysql_init(mysql);
	mysql_real_connect(mysql , "localhost" ,"root" ,"", "spj",0,NULL,0);

	////////////////////////////////////////////////

	double spsnr[300];
	//数据初始化
	PSNR=0;
	mse1=0.0;
	sR1=sRead;
	sR2=sRead2;

	//进度条
	m_hThread.SetRange(0,250);
	m_hThread.SetStep(1);
	

	//画图（底色）
	CDC* dc=GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(dc,320,310);//宽高怎么定
	MemDC.SelectObject(&bitmap);
	CRect rect(0,0,320,310);
	//InvalidateRect(rect);//不画第二次不用！！
	CBrush brush(COLORREF(RGB(250,250,250)));
	MemDC.FillRect(rect,&brush);

	//（画图像）
	CDC *pDC = GetDC();
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	MemDC.SelectObject(&pen);

	//坐标轴
	MemDC.MoveTo(20,40);
	MemDC.LineTo(20,280);//高240
 	MemDC.LineTo(300,280);//宽280
	MemDC.TextOut(10,10,_T("PSNR"));
	MemDC.TextOut(15,282,_T("0"));
	MemDC.TextOut(300,285,_T("F"));
	//X轴
	MemDC.MoveTo(70,280);
	MemDC.LineTo(70,276);
	MemDC.TextOut(53,285,_T("50"));
	MemDC.MoveTo(120,280);
	MemDC.LineTo(120,276);
	MemDC.TextOut(103,285,_T("100"));
	MemDC.MoveTo(170,280);
	MemDC.LineTo(170,276);
	MemDC.TextOut(153,285,_T("150"));
	MemDC.MoveTo(220,280);
	MemDC.LineTo(220,276);
	MemDC.TextOut(203,285,_T("200"));
	MemDC.MoveTo(270,280);
	MemDC.LineTo(270,276);
	MemDC.TextOut(253,285,_T("250"));
	
	//Y轴
	MemDC.TextOut(2,270,_T("25"));
	MemDC.MoveTo(20,250);
	MemDC.LineTo(25,250);
	MemDC.TextOut(2,240,_T("27"));
	MemDC.MoveTo(20,220);
	MemDC.LineTo(25,220);
	MemDC.TextOut(2,210,_T("29"));
	MemDC.MoveTo(20,190);
	MemDC.LineTo(25,190);
	MemDC.TextOut(2,180,_T("31"));
	MemDC.MoveTo(20,160);
	MemDC.LineTo(25,160);
	MemDC.TextOut(2,150,_T("33"));
	MemDC.MoveTo(20,130);
	MemDC.LineTo(25,130);
	MemDC.TextOut(2,120,_T("35"));
	MemDC.MoveTo(20,100);
	MemDC.LineTo(25,100);
	MemDC.TextOut(2,90,_T("37"));
	MemDC.MoveTo(20,70);
	MemDC.LineTo(25,70);
	MemDC.TextOut(2,60,_T("39"));

	MemDC.MoveTo(20,280);//将画笔移位回零点

	//计算PSNR的值
	for(k=0;k<frame;k++)
	{
		
		mseall=0;MSE=0;//
		for(i=0;i<height;i++)
		{
			for(j=0;j<width;j++)
			{
			
				mse1 =(double) ( (sR1[j]-sR2[j])*(sR1[j]-sR2[j]) );
				mseall+=mse1;
			
			}
			sR1+=width;
			sR2+=width;
		}
		sR1+=height*width*1/2;
		sR2+=height*width*1/2;
		MSE=mseall/(width*height);//每一桢的MSE
		
		spsnr[k]=10*log10(65025/MSE);//数组spsnr[]存储每一桢的psnr

		////////////////////////数据库部分///////
		char s[300];
		sprintf(s,"insert into spj(frame,psnr) values(%d,%f)",k,spsnr[k]);
		mysql_query(mysql,s);
		
		MemDC.LineTo(k+20,280-(spsnr[k]-25)*15);
		////////////////////////////////////////

		PSNR+=spsnr[k];//250桢的psnr求和
		m_hThread.StepIt();
	}
	dc->BitBlt(10,10,320,310, &MemDC, 0, 0, SRCCOPY);
	mysql_close( mysql );
	mysql_library_end();
	

	psnr_aver=PSNR/frame;//250桢的psnr求和结果除桢数
	ReleaseDC(dc);
	UpdateData(false);
	// TODO: 在此添加控件通知处理程序代码
}


void Csample4Dlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}
