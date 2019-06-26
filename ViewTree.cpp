#include "stdafx.h"
#include "ViewTree.h"
#include "casetree.h"
#include "MainFrm.h"
#include "ChildFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	//ON_NOTIFY_REFLECT(NM_KILLFOCUS, &CViewTree::OnNMKillfocus)
	//ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, &CViewTree::OnTvnBeginlabeledit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint point;
	GetCursorPos(&point);//获得鼠标点击的位置
	ScreenToClient(&point);//转化为客户坐标
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem = HitTest(point, &uFlags);//获得当前点击节点的ITEM

	//获得该节点的父节点
	// HTREEITEM ParentItem=m_videotree.GetParentItem(CurrentItem);
	if (CurrentItem == NULL)
		return;
	catalog *cata = (catalog*)GetItemData(CurrentItem);


	if (!cata->iscatalog)
	{
		CMainFrame * pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CChildFrame* pChild = (CChildFrame*)pMainFrame->GetActiveFrame();
		//CChildFrame* pChild1 = (CChildFrame*)pMainFrame->MDIGetActive();

		::SendMessage(pChild->rightview->m_hWnd, WM_CATALOGSHOW, _ttoi(cata->Id), (LPARAM)cata->iscatalog);
	}

}


//void CViewTree::OnNMKillfocus(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	//AfxMessageBox(_T("shiqujiaodian"));
//	((CMainFrame*)AfxGetMainWnd())->m_wndOutput.m_wndOutputBuild.AddString(_T("失去焦点。"));
//	*pResult = 0;
//}


//void CViewTree::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}
