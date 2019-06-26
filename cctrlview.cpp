// cctrlview.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "cctrlview.h"
#include "ChildFrm.h"

// cctrlview

IMPLEMENT_DYNCREATE(cctrlview, CFormView)

cctrlview::cctrlview()
	: CFormView(IDD_CCTRLVIEW)
{

}

cctrlview::~cctrlview()
{
}

void cctrlview::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(cctrlview, CFormView)
	ON_WM_CTLCOLOR()
	ON_BN_DOUBLECLICKED(IDC_EXECSHELL, &cctrlview::OnBnDoubleclickedExecshell)
	ON_BN_DOUBLECLICKED(IDC_PREDATA, &cctrlview::OnBnDoubleclickedPredata)
	ON_BN_DOUBLECLICKED(IDC_INPUTEDIT, &cctrlview::OnBnDoubleclickedInputedit)
	ON_BN_DOUBLECLICKED(IDC_COMPAREFILE, &cctrlview::OnBnDoubleclickedComparefile)
	ON_BN_DOUBLECLICKED(IDC_COMPAREDATA, &cctrlview::OnBnDoubleclickedComparedata)
	ON_BN_DOUBLECLICKED(IDC_CLEANDATA, &cctrlview::OnBnDoubleclickedCleandata)
END_MESSAGE_MAP()


// cctrlview 诊断

#ifdef _DEBUG
void cctrlview::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void cctrlview::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// cctrlview 消息处理程序


HBRUSH cctrlview::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // 设置背景色

	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void cctrlview::OnBnDoubleclickedExecshell()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_EXECSHELL, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void cctrlview::OnBnDoubleclickedPredata()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_PREDATA, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void cctrlview::OnBnDoubleclickedInputedit()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_INPUTEDIT, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void cctrlview::OnBnDoubleclickedComparefile()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_COMPAREFILE, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void cctrlview::OnBnDoubleclickedComparedata()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_COMPAREDATA, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}


void cctrlview::OnBnDoubleclickedCleandata()
{
	::SendMessage((HWND)((CChildFrame*)GetParentFrame())->rightview->m_hWnd, WM_CREATEBUT_CLEANENV, 0, 0);
	// TODO: 在此添加控件通知处理程序代码
}
