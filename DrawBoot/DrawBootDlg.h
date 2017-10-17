
// DrawBootDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CDrawBootDlg �Ի���
class CDrawBootDlg : public CDialogEx
{
// ����
public:
	CDrawBootDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAWBOOT_DIALOG };

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
//	afx_msg void OnBnClickedRadio3();
//	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeWordEdit();
	CStatic m_Static;
	CStatic *pStatic = NULL;
	CString strText1;//�����ַ�������
	CSliderCtrl* pSlide1 = NULL;
	static int WordData[16][16];
	static int book[16][16];
	static short Locate[600];
	static int locate;

	
	
	afx_msg void OnBnClickedApplyButton();
	afx_msg void OnBnClickedExitButton();

	CString m_Edit;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_Word;
	CFont font;

	CStatic m_static;
	afx_msg void OnClickedSetupButton();
	afx_msg void OnBnClickedButtonShowdata();

	
	
	CMscomm1 m_mscomm;
	CEdit m_COM;
	afx_msg void OnBnClickedButtonOpencom();
	DECLARE_EVENTSINK_MAP()
	void OnOncommMscomm1();
	friend void DfsGetPath(int, int);
	
};


