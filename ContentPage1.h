#pragma once


// CContentPage1 对话框

class CContentPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CContentPage1)

public:
	CContentPage1();   // 标准构造函数
	virtual ~CContentPage1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ContentDlg1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
