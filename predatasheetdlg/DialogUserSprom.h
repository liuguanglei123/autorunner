#pragma once


// CDialogUserSprom �Ի���

class CDialogUserSprom : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserSprom)

public:
	CDialogUserSprom();
	virtual ~CDialogUserSprom();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CUSERSPROM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	static BOOL Exec(XMLElement* xmlConfig);
};
