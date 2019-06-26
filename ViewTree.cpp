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
// CViewTree ��Ϣ�������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CPoint point;
	GetCursorPos(&point);//����������λ��
	ScreenToClient(&point);//ת��Ϊ�ͻ�����
	UINT uFlags;

	HTREEITEM CurrentItem;
	CurrentItem = HitTest(point, &uFlags);//��õ�ǰ����ڵ��ITEM

	//��øýڵ�ĸ��ڵ�
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	//AfxMessageBox(_T("shiqujiaodian"));
//	((CMainFrame*)AfxGetMainWnd())->m_wndOutput.m_wndOutputBuild.AddString(_T("ʧȥ���㡣"));
//	*pResult = 0;
//}


//void CViewTree::OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}
