
// exampleDlg.h : ͷ�ļ�
//

#pragma once


// CexampleDlg �Ի���
class CexampleDlg : public CDialogEx
{
// ����
public:
	CexampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXAMPLE_DIALOG };

	CFile mFile;
	//CFile mFile2;
	int number;
	//int number2;
	int i,j,k;
	int frame;//����
	unsigned char *sRead;
	//unsigned char *sRead2;
	unsigned char *sR1,*sR2;
	double SAVG_AVER;
	unsigned char *sGauss;
	//double mse1,MSE,PSNR;
	//double mseall;

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
	CString open_path;
	afx_msg void OnBnClickedopen();
	int width;
	int height;
	CString gaosi_path;
	afx_msg void OnBnClickedgaosi();
	double Dv;
	afx_msg void OnBnClickedcal();
};
