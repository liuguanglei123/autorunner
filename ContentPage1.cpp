// ContentPage1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ContentPage1.h"
#include "afxdialogex.h"
#include "ContentSheet.h"

// CContentPage1 �Ի���

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


// CDialogUserAttr ��Ϣ�������


BOOL CContentPage1::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	RECT rect;
	//this->GetClientRect(&rect);
	((CContentSheet*)GetParent())->GetClientRect(&rect);

	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
	//pSheet->SetWindowPos(NULL, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


