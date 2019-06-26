
#include "stdafx.h"
#include "MainFrm.h"
#include "casetree.h"
#include "Resource.h"
#include "MFCApplication1.h"
#include "catalogtreeret.h"
#include "sequencerecset.h"
#include "ChildFrm.h"
#include "ExecCaseThread.h"

#define IDC_TREE 10200
vector<CString> execCaseVec;

#define roottree 1

class CCaseViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CCaseView;

	DECLARE_SERIAL(CCaseViewMenuButton)

public:
	CCaseViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CCaseViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

CCaseView::CCaseView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
	m_catalogtree = new CCatalogTreeRecSet();
	m_casetree = new CCaseTreeRecSet();
	catalogseq = 0;
	isExecuting = FALSE;
}

CCaseView::~CCaseView()
{
}

BEGIN_MESSAGE_MAP(CCaseView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnCaseAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnCaseAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnCaseDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnCaseProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_COMMAND(ID_NEW_CASE, &CCaseView::OnNewCase)
	ON_COMMAND(ID_RENAME, &CCaseView::OnRename)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE, OnBeginlabeleditTree1)  //消息映射  
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, OnEndlabeleditTree1)    //消息映射 
	ON_NOTIFY(NM_KILLFOCUS, IDC_TREE,OnTreeNMKillfocus)

	ON_COMMAND(ID_NEWCATALOG, &CCaseView::OnNewcatalog)
	ON_COMMAND(ID_DELETE, &CCaseView::OnDelete)
	ON_COMMAND(ID_COPYCASE, &CCaseView::OnCopycase)
	ON_COMMAND(ID_PASTECASE, &CCaseView::OnPastecase)
	ON_COMMAND(ID_CUTCASE, &CCaseView::OnCutcase)
	ON_COMMAND(ID_EXEC, &CCaseView::OnExec)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaseView 消息处理程序

int CCaseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS ;// | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndCaseView.Create(dwViewStyle, rectDummy, this, IDC_TREE))
	{
		TRACE0("未能创建类视图\n");
		return -1;      // 未能创建
	}

	// 加载图像: 
	//m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	//m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	//OnChangeVisualStyle();

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//m_wndToolBar.SetOwner(this);

	//// 所有命令将通过此控件路由，而不是通过主框架路由: 
	//m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	//CMenu menuSort;
	//menuSort.LoadMenu(IDR_POPUP_SORT);

	//m_wndToolBar.ReplaceButton(ID_SORT_MENU, CCaseViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	//CCaseViewMenuButton* pButton = DYNAMIC_DOWNCAST(CCaseViewMenuButton, m_wndToolBar.GetButton(0));

	//if (pButton != NULL)
	//{
	//	pButton->m_bText = FALSE;
	//	pButton->m_bImage = TRUE;
	//	pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
	//	pButton->SetMessageWnd(this);
	//}

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	FillCaseView();

	return 0;
}

void CCaseView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CCaseView::FillCaseView()
{
	catalog cata;
	
	if (m_catalogtree->IsOpen()) m_catalogtree->Close();
	CString strSQL = _T("select * from catalogtree;");
	BOOL a = m_catalogtree->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("查询catalogtree失败！！"));
	if (!m_catalogtree->IsEOF()) {
		m_catalogtree->MoveFirst();
	}
	//long b = m_catalogtree->GetRecordCount();
	for (int i = 0; !m_catalogtree->IsEOF(); i++)
	{
		m_catalogtree->GetFieldValue(_T("ID"), cata.Id);
		m_catalogtree->GetFieldValue(_T("NAME"), cata.Name);
		m_catalogtree->GetFieldValue(_T("FATHER_ID"), cata.Father_Id);
		cata.iscatalog = TRUE;
		catalogseq++;
		catalogmap.insert(make_pair(catalogseq, cata));
		m_catalogtree->MoveNext();
	}


	if (m_casetree->IsOpen()) m_casetree->Close();
	CString strSQL1 = _T("select * from casetree;");
	BOOL b = m_casetree->Open(CRecordset::snapshot, strSQL1);
	if (!b)
		AfxMessageBox(_T("查询casetree失败！！"));
	if (!m_casetree->IsEOF()) {
		m_casetree->MoveFirst();
	}
	for (int i = 0; !m_casetree->IsEOF(); i++)
	{
		m_casetree->GetFieldValue(_T("CASEID"), cata.Id);
		m_casetree->GetFieldValue(_T("CASENAME"), cata.Name);
		m_casetree->GetFieldValue(_T("CATALOGID"), cata.Father_Id);
		cata.iscatalog = FALSE;
		catalogseq++;
		catalogmap.insert(make_pair(catalogseq,cata));
		m_casetree->MoveNext();
	}

	recursion(_T("0"));

}

void CCaseView::recursion(CString ID , HTREEITEM treeitem)
{
	map<int, catalog>::iterator catalogmapite = catalogmap.begin();
	for (int i=1; catalogmapite != catalogmap.end(); catalogmapite++,i++)
		{
			if (((catalog)(catalogmapite->second)).Father_Id == ID)
			{
				HTREEITEM hItem = m_wndCaseView.InsertItem(((catalog)(catalogmapite->second)).Name, 1, 1, treeitem);
				m_wndCaseView.SetItemData(hItem, (DWORD_PTR)&(catalogmapite->second));
				/*本来此处写的是m_wndCaseView.SetItemData(hItem, (DWORD_PTR)&catalogvecite);
				直接拿迭代器的地址当作tree中某一子项的附加数据，但是实践发现，迭代器的指针似乎指向的是一个
				不明确的地址，不能直接使用地址，只能用vector的[]操作获得想要的数据*/
				/*再次修改，本来此处使用的是vector，每次保存vector中元素的地址，但是vector存在一个问题，就是
				元素数一旦多余capacity()预留的元素数，则会重新分配地址，以前保存的地址就失效了。所以此处改为使用map，
				map的元素增加，但是每个元素的地址不会变*/
				if (((catalog)(catalogmapite->second)).iscatalog)
					recursion(((catalog)(catalogmapite->second)).Id, hItem);
			}
		}
}


void CCaseView::OnContextMenu(CWnd* pWnd, CPoint point)
{
 	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndCaseView;
	ASSERT_VALID(pWndTree);

	//GetCursorPos(&point);//获得鼠标点击的位置
	//ScreenToClient(&point);//转化为客户坐标
	//UINT uFlags;

	//HTREEITEM CurrentItem;
	//CurrentItem = m_wndCaseView.HitTest(point, &uFlags);//获得当前点击节点的ITEM

	////获得该节点的父节点
	//// HTREEITEM ParentItem=m_videotree.GetParentItem(CurrentItem);
	//if (CurrentItem == NULL)
	//	return;
	//catalog *cata = (catalog*)m_wndCaseView.GetItemData(CurrentItem);


	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	HTREEITEM hTreeItem = 0;
	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	catalog *a = (catalog*)pWndTree->GetItemData(hTreeItem);
	if (((catalog*)pWndTree->GetItemData(hTreeItem))->iscatalog)
	{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_CATALOG);
	
		CMenu* pSumMenu = menu.GetSubMenu(0);
	
		if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
		{
			CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
	
			if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
				return;
	
			((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
			UpdateDialogControls(this, FALSE);
		}
	}
	else
	{
		CMenu menu;
		menu.LoadMenu(IDR_POPUP_CASE);

		CMenu* pSumMenu = menu.GetSubMenu(0);

		if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
		{
			CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

			if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
				return;

			((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
			UpdateDialogControls(this, FALSE);
		}
	}
}

void CCaseView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	//int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndCaseView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 1, rectClient.Width() - 2, rectClient.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CCaseView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CCaseView::OnSort(UINT id)
{
	/*if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CCaseViewMenuButton* pButton = DYNAMIC_DOWNCAST(CCaseViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}*/
}

void CCaseView::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CCaseView::OnCaseAddMemberFunction()
{
	AfxMessageBox(_T("添加成员函数..."));
}

void CCaseView::OnCaseAddMemberVariable()
{
	// TODO: 在此处添加命令处理程序代码
}

void CCaseView::OnCaseDefinition()
{
	// TODO: 在此处添加命令处理程序代码
}

void CCaseView::OnCaseProperties()
{
	// TODO: 在此处添加命令处理程序代码
}

void CCaseView::OnNewFolder()
{
	AfxMessageBox(_T("新建文件夹..."));
}

void CCaseView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndCaseView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CCaseView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndCaseView.SetFocus();
}

void CCaseView::OnChangeVisualStyle()
{
	m_CaseViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_CaseViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_CaseViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndCaseView.SetImageList(&m_CaseViewImages, TVSIL_NORMAL);

	//m_wndToolBar.CleanUpLockedImages();
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}


void CCaseView::OnNewCase()
{	

	// TODO: 在此添加命令处理程序代码
	HTREEITEM item = m_wndCaseView.GetSelectedItem();
	BOOL isCatalog = ((catalog*)m_wndCaseView.GetItemData(item))->iscatalog;
	catalog cata;
	cata.iscatalog = FALSE;
	if (isCatalog)
	{
		TmpItem = m_wndCaseView.InsertItem(_T("newcase"), 1, 1, item);
		m_wndCaseView.ModifyStyle(NULL, TVS_EDITLABELS);
		CEdit* pmyEdit = m_wndCaseView.EditLabel(TmpItem);
		pmyEdit->GetWindowTextW(cata.Name);
		cata.Father_Id = ((catalog*)m_wndCaseView.GetItemData(item))->Id;
	}
	else
	{
		TmpItem = m_wndCaseView.InsertItem(_T("newcase"), 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
		m_wndCaseView.ModifyStyle(NULL, TVS_EDITLABELS);
		m_wndCaseView.EditLabel(TmpItem);
 		cata.Father_Id = ((catalog*)m_wndCaseView.GetItemData((HTREEITEM)m_wndCaseView.GetParentItem(item)))->Id;
		//cata.Name = m_wndCaseView.GetItemText(TmpItem);

	}

	cata.Id = getCaseTreeSeqNext();
	
	undoDataDeal undocata{ INSERTCASE, TmpItem, cata };
	undoDataDealVec.push_back(undocata);

	catalogseq++;
	catalogmap.insert(make_pair(catalogseq, cata));

	m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);

}


void CCaseView::OnRename()
{
	HTREEITEM item = m_wndCaseView.GetSelectedItem();
	CStringA g_sSelectStr;
	g_sSelectStr = m_wndCaseView.GetItemText(m_wndCaseView.GetSelectedItem());
	char cTem[100], cDest[100];
	strcpy(cTem, g_sSelectStr);
	char *sTem = cTem;
	memcpy(cDest, sTem, 8);
	cDest[8] = '\0';
	string sCompare;
	sCompare = cDest;
	m_wndCaseView.ModifyStyle(NULL, TVS_EDITLABELS);
	TmpItem = m_wndCaseView.GetSelectedItem();
	m_wndCaseView.EditLabel(TmpItem);

	undoDataDeal undocata;
	if (((catalog*)m_wndCaseView.GetItemData(TmpItem))->iscatalog)
		undoDataDealVec.push_back(undoDataDeal{ UPDATECATALOG, TmpItem, *(catalog*)m_wndCaseView.GetItemData(TmpItem)});
	else
		undoDataDealVec.push_back(undoDataDeal{ UPDATECASE, TmpItem, *(catalog*)m_wndCaseView.GetItemData(TmpItem) });


	// TODO: 在此添加命令处理程序代码
}



void CCaseView::OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here  
	m_wndCaseView.GetEditControl()->LimitText(1024);
	*pResult = 0;
}


void CCaseView::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here  
	//HTREEITEM m_hInsertItem;
	CString strName; //修改后的数据  
	m_wndCaseView.GetEditControl()->GetWindowText(strName);
	if (strName.IsEmpty())
	{
		MessageBox(_T("数据项名称不能为空，请重新输入!"));
		CEdit *pEdit = m_wndCaseView.EditLabel(TmpItem);
		return;
	}
	/*if (strName == g_sSelectStr)
	{
		return;
	}*/
	//HTREEITEM hRoot = m_wndCaseView.GetRootItem();
	//HTREEITEM hFind = FindItem(hRoot, strName);          //判断数据是否相同  
	//if (hFind == NULL)
	//{
		//char msg[64] = { 0 };
		//sprintf(msg, _T("修改信息为%s,确定吗?"), strName);
		//if (MessageBox(msg, "提示", MB_OKCANCEL) == IDOK)
		//{
			CString strText;
			m_wndCaseView.GetEditControl()->GetWindowText(strText.GetBuffer(200), 200);
			m_wndCaseView.SetItemText(TmpItem, strText);//设置编辑后的文本为结点  
			*pResult = TRUE;

	//	}
	//	else
	//	{
	//		m_TreeCtrl.DeleteItem(m_hInsertItem);
	//	}
	//}

	*pResult = 0;
}


void CCaseView::insertCaseTree(catalog cata)
{

	CString strSQL = _T("select * from casetree where caseid=\'")\
		+ cata.Id + _T("\';");
	if (m_casetree->IsOpen())
		m_casetree->Close();
	BOOL a = m_casetree->Open(CRecordset::snapshot, strSQL);
	long b = m_casetree->GetRecordCount();
	if (b == 0)
	{
		m_casetree->AddNew();
		m_casetree->m_CASEID = _ttoi(cata.Id);
		m_casetree->m_CASENAME = cata.Name;
		m_casetree->m_catalogid = _ttoi(cata.Father_Id);
		m_casetree->m_CREATETIME = CTime::GetCurrentTime();
		m_casetree->m_MODIFYTIME = CTime::GetCurrentTime();
		m_casetree->m_EXPIREDATE = CTime(2030, 01, 01, 00, 00, 00);
		m_casetree->m_AUTHER = _T("liugl5");
		m_casetree->m_ISUSED = 1;

		m_casetree->Update();
	}
	else
	{
		CString errmsg;
		errmsg.Format(_T("已经存在相同caseID的案例，caseId为%s"), cata.Id);
		AfxMessageBox(errmsg);
	}
	m_casetree->Close();

	return;
}






void CCaseView::OnNewcatalog()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM item = m_wndCaseView.GetSelectedItem();
	BOOL isCatalog = ((catalog*)m_wndCaseView.GetItemData(item))->iscatalog;
	catalog cata;
	cata.iscatalog = TRUE;

	if (isCatalog)
	{
		TmpItem = m_wndCaseView.InsertItem(_T("newcatalog"), 1, 1, item);
		m_wndCaseView.ModifyStyle(NULL, TVS_EDITLABELS);
		m_wndCaseView.EditLabel(TmpItem);
 		cata.Father_Id = ((catalog*)m_wndCaseView.GetItemData(item))->Id;
		//cata.Name = m_wndCaseView.GetItemText(TmpItem);
	}
	else
	{
		TmpItem = m_wndCaseView.InsertItem(_T("newcatalog"), 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
		m_wndCaseView.ModifyStyle(NULL, TVS_EDITLABELS);
		m_wndCaseView.EditLabel(TmpItem);
		cata.Father_Id = ((catalog*)m_wndCaseView.GetItemData(m_wndCaseView.GetParentItem(item)))->Id;
		//cata.Name = m_wndCaseView.GetItemText(TmpItem);
	}

	cata.Id = getCatalogTreeSeqNext();

	undoDataDeal undocata{ INSERTCATALOG,TmpItem, cata };
	undoDataDealVec.push_back(undocata);

	catalogseq++;
	catalogmap.insert(make_pair(catalogseq, cata));

	m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);
}


void CCaseView::insertCaseCatalog(catalog cata)
{

	CString strSQL = _T("select * from catalogtree where id=\'")\
		+ cata.Id + _T("\';");
	if (m_catalogtree->IsOpen())
		m_catalogtree->Close();
	BOOL a = m_catalogtree->Open(CRecordset::snapshot, strSQL);
	long b = m_catalogtree->GetRecordCount();
	if (b == 0)
	{
		m_catalogtree->AddNew();
		m_catalogtree->m_ID = _ttoi(cata.Id);
		m_catalogtree->m_NAME = cata.Name;
		m_catalogtree->m_FATHER_ID = _ttoi(cata.Father_Id);
		m_catalogtree->m_CREATETIME = CTime::GetCurrentTime();
		m_catalogtree->m_MODIFYTIME = CTime::GetCurrentTime();
		m_catalogtree->m_EXPIREDATE = CTime(2030,01,01,00,00,00);
		m_catalogtree->m_AUTHER = _T("liugl5");
		m_casetree->m_ISUSED = 1;

		m_catalogtree->Update();
	}
	else
	{
		CString errmsg;
		errmsg.Format(_T("已经存在相同caseID的目录，caseId为%s"), cata.Id);
		AfxMessageBox(errmsg);
	}
	m_catalogtree->Close();

	return;
}


void CCaseView::OnTreeNMKillfocus(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (undoDataDealVec.size() == 0)
		return;

	vector<undoDataDeal>::iterator undoDDVecitr = undoDataDealVec.begin();
	while (undoDDVecitr != undoDataDealVec.end())
	{
		switch (undoDDVecitr->actionType)
		{
		case 1:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			((catalog*)m_wndCaseView.GetItemData(undoDDVecitr->item))->Name = undoDDVecitr->cata.Name;
			insertCaseTree(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
		case 2:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			((catalog*)m_wndCaseView.GetItemData(undoDDVecitr->item))->Name = undoDDVecitr->cata.Name;
			insertCaseCatalog(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
		case 3:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			((catalog*)m_wndCaseView.GetItemData(undoDDVecitr->item))->Name = undoDDVecitr->cata.Name;
			updateCaseTree(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
		case 4:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			((catalog*)m_wndCaseView.GetItemData(undoDDVecitr->item))->Name = undoDDVecitr->cata.Name;
			updateCatalogTree(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
		case 5:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			deleteCaseTree(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
			break;
		case 6:
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			undoDDVecitr->cata.Name = m_wndCaseView.GetItemText(undoDDVecitr->item);
			deleteCatalogTree(undoDDVecitr->cata);
			undoDDVecitr = undoDataDealVec.erase(undoDDVecitr);
			break;
			break;
		default:
			break;
		}
		((CMainFrame*)AfxGetMainWnd())->m_wndOutput.m_wndOutputBuild.AddString(_T("更新一条数据。"));

	}

	return;
}

void CCaseView::updateCaseTree(catalog cata)
{
	CString strSQL = _T("select * from casetree  where caseid=\'")\
		+ cata.Id + _T("\';");
	if (m_casetree->IsOpen())
		m_casetree->Close();
	BOOL a = m_casetree->Open(CRecordset::snapshot, strSQL);
	long b = m_casetree->GetRecordCount();
	if (b == 0)
	{
		CString errmsg;
		errmsg.Format(_T("数据库中不存在该案例caseid为 %d"), cata.Id);
		AfxMessageBox(errmsg);
		
	}
	else
	{
		m_casetree->Edit();
		m_casetree->m_CASEID = _ttoi(cata.Id);
		m_casetree->m_CASENAME = cata.Name;
		m_casetree->m_catalogid = _ttoi(cata.Father_Id);
		m_casetree->m_MODIFYTIME = CTime::GetCurrentTime();
		m_casetree->Update();
	}
	m_casetree->Close();

	return;
}

void CCaseView::updateCatalogTree(catalog cata)
{
	CString strSQL = _T("select * from catalogtree  where id=\'")\
		+ cata.Id + _T("\';");
	if (m_catalogtree->IsOpen())
		m_catalogtree->Close();
	BOOL a = m_catalogtree->Open(CRecordset::snapshot, strSQL);
	long b = m_catalogtree->GetRecordCount();
	if (b == 0)
	{
		CString errmsg;
		errmsg.Format(_T("数据库中不存在该案例caseid为 %d"), cata.Id);
		AfxMessageBox(errmsg);

	}
	else
	{
		m_catalogtree->Edit();
		m_catalogtree->m_ID = _ttoi(cata.Id);
		m_catalogtree->m_NAME = cata.Name;
		m_catalogtree->m_FATHER_ID = _ttoi(cata.Father_Id);
		m_catalogtree->m_MODIFYTIME = CTime::GetCurrentTime();
		m_catalogtree->Update();
	}
	m_catalogtree->Close();

	return;
}


void CCaseView::OnDelete()
{
	OnTreeNMKillfocus(0, 0);
	TmpItem = m_wndCaseView.GetSelectedItem();

	undoDataDeal undocata;
	if (((catalog*)m_wndCaseView.GetItemData(TmpItem))->iscatalog)
	{
		undoDataDealVec.push_back(undoDataDeal{ DELETECATALOG, TmpItem, *(catalog*)m_wndCaseView.GetItemData(TmpItem) });
		m_wndCaseView.DeleteItem(TmpItem);
	}
	else
	{
		undoDataDealVec.push_back(undoDataDeal{ DELETECASE, TmpItem, *(catalog*)m_wndCaseView.GetItemData(TmpItem) });
		m_wndCaseView.DeleteItem(TmpItem);	
	}
}


void CCaseView::deleteCaseTree(catalog cata)
{
	CString strSQL = _T("select * from casetree  where caseid=\'")\
		+ cata.Id + _T("\';");
	if (m_casetree->IsOpen())
		m_casetree->Close();
	BOOL a = m_casetree->Open(CRecordset::snapshot, strSQL);
	long b = m_casetree->GetRecordCount();
	if (b == 0)
	{
		CString errmsg;
		errmsg.Format(_T("数据库中不存在该案例caseid为 %d"), cata.Id);
		AfxMessageBox(errmsg);

	}
	else
	{
		m_casetree->Edit();
		m_casetree->m_ISUSED = 0;
		m_casetree->Update();
	}
	m_casetree->Close();

	return;
}

void CCaseView::deleteCatalogTree(catalog cata)
{
	CString strSQL = _T("select * from catalogtree  where id=\'")\
		+ cata.Id + _T("\';");
	if (m_catalogtree->IsOpen())
		m_catalogtree->Close();
	BOOL a = m_catalogtree->Open(CRecordset::snapshot, strSQL);
	long b = m_catalogtree->GetRecordCount();
	if (b == 0)
	{
		CString errmsg;
		errmsg.Format(_T("数据库中不存在该案例caseid为 %d"), cata.Id);
		AfxMessageBox(errmsg);

	}
	else
	{
		m_catalogtree->Edit();
		m_catalogtree->m_ISUSED = 0;
		m_catalogtree->Update();
	}
	m_catalogtree->Close();

	return;
}


void CCaseView::OnCopycase()
{
	notPasteCopyCase = m_wndCaseView.GetSelectedItem();
	notPasteCutCase = 0;
}

void CCaseView::OnCutcase()
{
	// TODO: 在此添加命令处理程序代码
	notPasteCutCase = m_wndCaseView.GetSelectedItem();
	notPasteCopyCase = 0;

}



void CCaseView::OnPastecase()
{
	OnTreeNMKillfocus(0, 0);
	// TODO: 在此添加命令处理程序代码
	HTREEITEM item = m_wndCaseView.GetSelectedItem();
	BOOL isCatalog = ((catalog*)m_wndCaseView.GetItemData(item))->iscatalog;
	catalog tmpcata;
	if (notPasteCopyCase != 0)
	{
		tmpcata = *(catalog*)m_wndCaseView.GetItemData(notPasteCopyCase);

		if (!isCatalog)
		{
			if (!tmpcata.iscatalog)
			{
				TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
				tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData((HTREEITEM)m_wndCaseView.GetParentItem(item)))->Id;

				tmpcata.Id = getCaseTreeSeqNext();
				tmpcata.iscatalog = FALSE;
				undoDataDeal undocata{ INSERTCASE, TmpItem, tmpcata };
				undoDataDealVec.push_back(undocata);

				catalogseq++;
				catalogmap.insert(make_pair(catalogseq, tmpcata));
				m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);

				CMainFrame * pMainFrame = (CMainFrame*)AfxGetMainWnd();
				CChildFrame* pChild = (CChildFrame*)pMainFrame->GetActiveFrame();
				::SendMessage(pChild->rightview->m_hWnd, WM_COPYCASE, 
					_ttoi(((catalog*)m_wndCaseView.GetItemData(item))->Id), _ttoi(tmpcata.Id));

			}
			else
			{
				//TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
				//tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData((HTREEITEM)m_wndCaseView.GetParentItem(item)))->Id;
				//需要考虑复制目录时，目录下还有子目录，要递归，比较麻烦。
				AfxMessageBox(_T("暂时不支持复制目录。"));	
			}
		}
		else
		{
			if (tmpcata.iscatalog)
			{
				TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, item);
				tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData(item))->Id;
				tmpcata.Id = getCatalogTreeSeqNext();
				tmpcata.iscatalog = FALSE;
				undoDataDeal undocata{ INSERTCATALOG, TmpItem, tmpcata };
				undoDataDealVec.push_back(undocata);

				catalogseq++;
				catalogmap.insert(make_pair(catalogseq, tmpcata));
				m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);
			}
			else
			{
				//TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
				//tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData((HTREEITEM)m_wndCaseView.GetParentItem(item)))->Id;
				AfxMessageBox(_T("暂时不支持复制目录。"));
			}
			
		}
	}
	else if (notPasteCutCase != 0)
	{

		tmpcata = *(catalog*)m_wndCaseView.GetItemData(notPasteCutCase);

		if (!isCatalog) //点击的是案例，粘贴在该案例同目录下
		{
			if (!tmpcata.iscatalog)
			{	//剪切案例

				TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, (HTREEITEM)m_wndCaseView.GetParentItem(item));
				tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData((HTREEITEM)m_wndCaseView.GetParentItem(item)))->Id;

				undoDataDeal undocata{ UPDATECASE, TmpItem, tmpcata };
				undoDataDealVec.push_back(undocata);

				catalogseq++;
				catalogmap.insert(make_pair(catalogseq, tmpcata));
				m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);

				m_wndCaseView.DeleteItem(notPasteCutCase);
			}
			else
			{
				AfxMessageBox(_T("暂时不支持剪切目录。"));
			}

		}
		else//点击的是目录，粘贴在该目录下
		{
			if (!tmpcata.iscatalog)
			{	//剪切案例

				TmpItem = m_wndCaseView.InsertItem(tmpcata.Name, 1, 1, item);
				tmpcata.Father_Id = ((catalog*)m_wndCaseView.GetItemData(item))->Id;

				undoDataDeal undocata{ UPDATECASE, TmpItem, tmpcata };
				undoDataDealVec.push_back(undocata);

				catalogseq++;
				catalogmap.insert(make_pair(catalogseq, tmpcata));
				m_wndCaseView.SetItemData(TmpItem, (DWORD_PTR)&catalogmap[catalogseq]);

				m_wndCaseView.DeleteItem(notPasteCutCase);
			}
			else
			{
				AfxMessageBox(_T("暂时不支持剪切目录。"));
			}

		}

	}

	else
		AfxMessageBox(_T("没有成功复制/剪切任何案例。"));
}

CString CCaseView::getCatalogTreeSeqNext()
{
	CString CatalogTreeSeqValue;
	sequenceRecSet *m_seqRecSet = new sequenceRecSet();
	if (m_seqRecSet->IsOpen()) m_seqRecSet->Close();

	CString strSQL = _T("select catalogtreeseq.nextval from dual;");
	BOOL a = m_seqRecSet->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("查询BSXDRDEFINE失败！！"));

	m_seqRecSet->GetFieldValue(_T("NEXTVAL"), CatalogTreeSeqValue);

	delete m_seqRecSet;
	return CatalogTreeSeqValue;
}

CString CCaseView::getCaseTreeSeqNext()
{
	CString CaseTreeSeqValue;

	sequenceRecSet *m_seqRecSet = new sequenceRecSet();
	if (m_seqRecSet->IsOpen()) m_seqRecSet->Close();

	CString strSQL = _T("select casetreeseq.nextval from dual;");
	BOOL a = m_seqRecSet->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("查询BSXDRDEFINE失败！！"));

	m_seqRecSet->GetFieldValue(_T("NEXTVAL"), CaseTreeSeqValue);

	delete m_seqRecSet;
	return CaseTreeSeqValue;
}



void CCaseView::OnExec()
{
	// TODO: 在此添加命令处理程序代码
	if (isExecuting == TRUE)
	{
		AfxMessageBox(_T("当前有任务正在执行。"));
		return;
	}
	execCaseVec.clear();
	isExecuting = TRUE;
	HTREEITEM item = m_wndCaseView.GetSelectedItem();
	CString caseId =  ((catalog*)m_wndCaseView.GetItemData(item))->Id;

	execCaseVec.push_back(caseId);

	AfxBeginThread(RUNTIME_CLASS(CExecCaseThread));

	isExecuting = FALSE;

}
