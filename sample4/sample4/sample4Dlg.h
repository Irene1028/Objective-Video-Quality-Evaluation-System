
// sample4Dlg.h : ͷ�ļ�
//

#pragma once
#include "PlayControl.h"
#include "afxcmn.h"

// Csample4Dlg �Ի���
class Csample4Dlg : public CDialogEx
{
// ����
	private:  
    CPlayControl m_PlayControl; 

public:
	Csample4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SAMPLE4_DIALOG };

	CFile mFile;//�����ļ���Ӧ��������
	CFile mFile2;
	int number;//�����ļ��ĳ���
	int number2;
	int i,j,k,h,c;//ѭ���õ��ı���
	int frame,frame2;//����
	unsigned char *sRead;//sRead1,sRead2�Ǵ����е�ָ��
	unsigned char *sRead2;
	unsigned char *sR1,*sR2;//sR1,sR2��Ϊ�˱���洢��ָ����λ�����鷳���������ָ�룬ר�Ÿ�����λ
	double mse1,MSE,PSNR;
	double mseall;
	
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
