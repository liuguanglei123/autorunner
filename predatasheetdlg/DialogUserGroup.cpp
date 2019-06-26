// DialogUserGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFCApplication1.h"
#include "DialogUserGroup.h"
#include "afxdialogex.h"
#include "DialogUserInfo.h"



// CDialogUserGroup 对话框

IMPLEMENT_DYNAMIC(CDialogUserGroup, CPropertyPage)

CDialogUserGroup::CDialogUserGroup()
	: CPropertyPage(IDD_PROPPAGE_CUSERGROUP)
{
	m_usergrouprec = new CCUserGroupRecSet();
}

CDialogUserGroup::~CDialogUserGroup()
{
}

void CDialogUserGroup::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_strgroupid);
	DDX_Control(pDX, IDC_EDIT2, m_strgrouptype);
}

afx_msg LRESULT CDialogUserGroup::OnQuerySiblings(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("CDialogUserGroup::OnQuerySiblings"));
	return 0;
}


BEGIN_MESSAGE_MAP(CDialogUserGroup, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogUserGroup::OnBnClickedButton4)
	ON_MESSAGE(PSM_QUERYSIBLINGS, &CDialogUserGroup::OnQuerySiblings)
END_MESSAGE_MAP()


// CDialogUserGroup 消息处理程序


void CDialogUserGroup::OnBnClickedButton4()
{
	//QuerySiblings(1, 1);
	AfxMessageBox((CString)xdrdefinevec[1].xdr_dr_type);
	return;

	// TODO: 在此添加控件通知处理程序代码

}

BOOL CDialogUserGroup::Exec(XMLElement* xmlConfig)
{
	return TRUE;
}