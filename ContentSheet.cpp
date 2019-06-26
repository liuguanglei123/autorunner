// SelectSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ContentSheet.h"



// CSelectSheet

IMPLEMENT_DYNAMIC(CContentSheet, CPropertySheet)

CContentSheet::CContentSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_ContentPage1);
	AddPage(&m_ContentPage2);

}

CContentSheet::CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_ContentPage1);
	AddPage(&m_ContentPage2);

}

CContentSheet::~CContentSheet()
{
}


BEGIN_MESSAGE_MAP(CContentSheet, CPropertySheet)
END_MESSAGE_MAP()


// CSelectSheet 消息处理程序
