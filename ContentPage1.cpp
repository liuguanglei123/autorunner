// ContentPage1.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ContentPage1.h"
#include "afxdialogex.h"
#include "ContentSheet.h"

// CContentPage1 对话框

IMPLEMENT_DYNAMIC(CContentPage1, CPropertyPage)

CContentPage1::CContentPage1()
	: CPropertyPage(IDD_ContentDlg1)
{

}

CContentPage1::~CContentPage1()
{
}

void CContentPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CContentPage1, CPropertyPage)
END_MESSAGE_MAP()


// CDialogUserAttr 消息处理程序


BOOL CContentPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	RECT rect;
	//this->GetClientRect(&rect);
	((CContentSheet*)GetParent())->GetClientRect(&rect);

	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
	//pSheet->SetWindowPos(NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


