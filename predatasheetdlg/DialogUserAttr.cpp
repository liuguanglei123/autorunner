// DialogUserAttr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "../MFCApplication1.h"
#include "DialogUserAttr.h"
#include "afxdialogex.h"


// CDialogUserAttr �Ի���

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


// CDialogUserAttr ��Ϣ�������

BOOL CDialogUserAttr::Exec(XMLElement* xmlConfig)
{
	return TRUE;
}