// DialogUserSprom.cpp : 实现文件
//

#include "stdafx.h"
#include "..\MFCApplication1.h"
#include "DialogUserSprom.h"
#include "afxdialogex.h"


// CDialogUserSprom 对话框

IMPLEMENT_DYNAMIC(CDialogUserSprom, CPropertyPage)

CDialogUserSprom::CDialogUserSprom()
	: CPropertyPage(IDD_PROPPAGE_CUSERSPROM)
{

}

CDialogUserSprom::~CDialogUserSprom()
{
}

void CDialogUserSprom::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogUserSprom, CPropertyPage)
END_MESSAGE_MAP()


// CDialogUserSprom 消息处理程序


BOOL CDialogUserSprom::Exec(XMLElement* xmlConfig) 
{
	return TRUE;
}
