
// exampleDlg.h : 头文件
//

#pragma once


// CexampleDlg 对话框
class CexampleDlg : public CDialogEx
{
// 构造
public:
	CexampleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_EXAMPLE_DIALOG };

	CFile mFile;
	//CFile mFile2;
	int number;
	//int number2;
	int i,j,k;
	int frame;//祯数
	unsigned char *sRead;
	//unsigned char *sRead2;
	unsigned char *sR1,*sR2;
	double SAVG_AVER;
	unsigned char *sGauss;
	//double mse1,MSE,PSNR;
	//double mseall;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString open_path;
	afx_msg void OnBnClickedopen();
	int width;
	int height;
	CString gaosi_path;
	afx_msg void OnBnClickedgaosi();
	double Dv;
	afx_msg void OnBnClickedcal();
};
