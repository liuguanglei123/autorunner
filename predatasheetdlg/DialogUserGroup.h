#pragma once
#include "cusergroup.h"
#include "afxwin.h"

// CDialogUserGroup �Ի���8m,

class CDialogUserGroup : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserGroup)

public:
	CDialogUserGroup();
	virtual ~CDialogUserGroup();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CUSERGROUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	CCUserGroupRecSet *m_usergrouprec;
	CEdit m_strgroupid;
	CEdit m_strgrouptype;
	afx_msg LRESULT   OnQuerySiblings(WPARAM wParam, LPARAM lParam);
public:
	static BOOL Exec(XMLElement* xmlConfig);

};
