#pragma once


// CDialogUserSprom 对话框

class CDialogUserSprom : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserSprom)

public:
	CDialogUserSprom();
	virtual ~CDialogUserSprom();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CUSERSPROM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	static BOOL Exec(XMLElement* xmlConfig);
};
