// DialogUserSprom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\MFCApplication1.h"
#include "DialogUserSprom.h"
#include "afxdialogex.h"


// CDialogUserSprom �Ի���

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


// CDialogUserSprom ��Ϣ�������


BOOL CDialogUserSprom::Exec(XMLElement* xmlConfig) 
{
	return TRUE;
}
