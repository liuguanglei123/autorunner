#pragma once


// CDialogUserAttr �Ի���

class CDialogUserAttr : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserAttr)

public:
	CDialogUserAttr();
	virtual ~CDialogUserAttr();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_RELAANDCELL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	static BOOL Exec(XMLElement* xmlConfig);

};
