#pragma once


// CContentPage1 �Ի���

class CContentPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CContentPage1)

public:
	CContentPage1();   // ��׼���캯��
	virtual ~CContentPage1();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ContentDlg1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
