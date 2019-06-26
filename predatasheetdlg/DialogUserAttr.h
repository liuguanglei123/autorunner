#pragma once


// CDialogUserAttr 对话框

class CDialogUserAttr : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserAttr)

public:
	CDialogUserAttr();
	virtual ~CDialogUserAttr();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_RELAANDCELL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	static BOOL Exec(XMLElement* xmlConfig);

};
