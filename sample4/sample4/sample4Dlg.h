
// sample4Dlg.h : 头文件
//

#pragma once
#include "PlayControl.h"
#include "afxcmn.h"

// Csample4Dlg 对话框
class Csample4Dlg : public CDialogEx
{
// 构造
	private:  
    CPlayControl m_PlayControl; 

public:
	Csample4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SAMPLE4_DIALOG };

	CFile mFile;//两个文件对应两个序列
	CFile mFile2;
	int number;//两个文件的长度
	int number2;
	int i,j,k,h,c;//循环用到的变量
	int frame,frame2;//祯数
	unsigned char *sRead;//sRead1,sRead2是存序列的指针
	unsigned char *sRead2;
	unsigned char *sR1,*sR2;//sR1,sR2是为了避免存储的指针移位带来麻烦而定义的新指针，专门负责移位
	double mse1,MSE,PSNR;
	double mseall;
	
	

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
	CString input1;
	CString input2;
	CString out_path;
	double psnr_aver;
	afx_msg void OnEnChangeEdit1();
	int width;
	int height;
	afx_msg void OnBnClickedopen();
	afx_msg void OnBnClickedon();
	afx_msg void OnBnClickedpause();
	afx_msg void OnBnClickedstop();
	afx_msg void OnBnClickedopen1();
	afx_msg void OnBnClickedopen2();
	afx_msg void OnBnClickedout();
	afx_msg void OnBnClickedPsnr();
	CProgressCtrl m_hThread;
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
};
