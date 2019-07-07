
// exampleDlg.cpp : ʵ���ļ�
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


// CexampleDlg �Ի���




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


// CexampleDlg ��Ϣ�������

BOOL CexampleDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CexampleDlg::OnPaint()
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
HCURSOR CexampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CexampleDlg::OnBnClickedopen()//��һ����Ƶ����ָ��λ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������//��һ����Ƶ����д������
}


void CexampleDlg::OnBnClickedgaosi()////��˹������ֱ�Ӽ���Savg���������˹ģ��������Ƶ
{
	UpdateData(true);
	CFileDialog dlg(FALSE);
	if(dlg.DoModal()==IDOK)
		gaosi_path=dlg.GetPathName();
	gaosi_path.Format(gaosi_path);
	
	CFile out;
	sR1=sRead;//sR1��sRead������ר�Ÿ�����λ����ֹsRead��λ�����鷳
	sGauss = new unsigned char[width*height*frame+1];
	sR2=sGauss;//sR2��sGauss������ר�Ÿ�����λ����ֹsGauss��λ�����鷳
	double Savg[250];//����洢ÿһ���Savg
	SAVG_AVER=0;//Savg��ʼ��

	//��˹����
	if(out.Open(gaosi_path,CFile::modeCreate|CFile::modeWrite))
	{
		sR2=sGauss;
		for(i=0;i<frame;i++)
		{
			Savg[i]=0;
			for(k=0;k<height;k++)
			{
				if(k==0)//��һ��ԭֵ���
				{
					for(j=0;j<width;j++)
					{
					sR2[j]=sR1[j];
					}
				}
				else if(k==(height-1))//���һ��ԭֵ���
				{
					for(j=0;j<width;j++)
					sR2[j]=sR1[j];
				}
				else//�����м���
				{
					for(j=0;j<width;j++)
					{
						if(j==0)//��һ����ԭֵ���
							sR2[j]=sR1[j];
						else if(j==(width-1))//���һ����ԭֵ���
							sR2[j]=sR1[j];
						else
						{
							sR2[j]=(sR1[j]*4+(sR1[-1+j]+sR1[1+j]+sR1[width+j]+sR1[-width+j])*2+(sR1[width+j+1]+sR1[width+j-1]+sR1[-width+j+1]+sR1[-width+j-1])*1)/16.0;
							//��˹�ĺ��Ĵ���
							Savg[i]+=abs(sR1[j]-sR2[j]);
							//ÿһ���Savg�Ӻ�
							
						}
					}
					
				}
				out.Write(sR2,width);//ÿһ�и�˹����д��
				sR1+=width;
				sR2+=width;
				
			}
			sR1+=width*height/2;
			Savg[i]=Savg[i]/(width*height);//ÿһ���Savg֮�����һ���ƽ��ֵ
			SAVG_AVER+=Savg[i];//��250��ļӺ�
			//out.Write(sR2-height*width,height*width);//��������һ��һ��д�����ٶȸ�����
		}
		out.Close();
		SAVG_AVER=SAVG_AVER/frame;//��250���ƽ��ֵ
	}

	
	UpdateData(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CexampleDlg::OnBnClickedcal()
{
	UpdateData(true);
	//�ֲ�ʧ��
	//ˮƽ
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
				sh[k*(width-1)+j]=abs(sR1[j]-sR1[j+1]);//����ÿһ��Sh��ֵ����sh[]
				sh_Sum+=sh[k*(width-1)+j];//ÿһ���sh ֵ�Ӻ�
			}
			sR1+=width;//����
		}
		sh_Aver[i]=sh_Sum/(479*272);//����ÿһ��sh��ֵ����sh_Aver[i]

		fc=0;//����һ����������������
		for(j=0;j<((width-1)*height);j++)
		{
			fc+=pow(sh[j]-sh_Aver[i],2);
		}
		fangcha[i]=sqrt(fc/((width-1)*height));//�������֮�󿪷��õ���׼�ÿ�����fangcha[i]��
		FC_AVER+=fangcha[i];//250���׼��Ӻ�
		num=width*height*(1/2);
		sR1+=(char)num;
	}
	FC_AVER=FC_AVER/frame;//��׼����ƽ��

	//��ֱ���㷨��ˮƽһ��ֻ�Ǹ��������ָ������2��ʾ��
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

	Dv=(FC_AVER+FC_AVER2)/2+SAVG_AVER;//ˮƽ�ĺʹ�ֱ��ȡƽ��Ȼ�����Savg�õ����յ�����ָ��
	
	UpdateData(false);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
