// DialogUserAttr.cpp : 实现文件
//

#include "stdafx.h"
#include "../MFCApplication1.h"
#include "DialogUserAttr.h"
#include "afxdialogex.h"


// CDialogUserAttr 对话框

IMPLEMENT_DYNAMIC(CDialogUserAttr, CPropertyPage)

CDialogUserAttr::CDialogUserAttr()
	: CPropertyPage(IDD_PROPPAGE_RELAANDCELL)
{

}

CDialogUserAttr::~CDialogUserAttr()
{
}

void CDialogUserAttr::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogUserAttr, CPropertyPage)
END_MESSAGE_MAP()


// CDialogUserAttr 消息处理程序

BOOL CDialogUserAttr::Exec(XMLElement* xmlConfig)
{
	return TRUE;
}