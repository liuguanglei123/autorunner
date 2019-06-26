
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
// ����/����
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
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE, OnBeginlabeleditTree1)  //��Ϣӳ��  
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, OnEndlabeleditTree1)    //��Ϣӳ�� 
	ON_NOTIFY(NM_KILLFOCUS, IDC_TREE,OnTreeNMKillfocus)

	ON_COMMAND(ID_NEWCATALOG, &CCaseView::OnNewcatalog)
	ON_COMMAND(ID_DELETE, &CCaseView::OnDelete)
	ON_COMMAND(ID_COPYCASE, &CCaseView::OnCopycase)
	ON_COMMAND(ID_PASTECASE, &CCaseView::OnPastecase)
	ON_COMMAND(ID_CUTCASE, &CCaseView::OnCutcase)
	ON_COMMAND(ID_EXEC, &CCaseView::OnExec)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaseView ��Ϣ�������

int CCaseView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS ;// | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndCaseView.Create(dwViewStyle, rectDummy, this, IDC_TREE))
	{
		TRACE0("δ�ܴ�������ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ����ͼ��: 
	//m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	//m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* ������*/);

	//OnChangeVisualStyle();

	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	//m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	//m_wndToolBar.SetOwner(this);

	//// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��: 
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

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
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
		AfxMessageBox(_T("��ѯcatalogtreeʧ�ܣ���"));
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
		AfxMessageBox(_T("��ѯcasetreeʧ�ܣ���"));
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
				/*�����˴�д����m_wndCaseView.SetItemData(hItem, (DWORD_PTR)&catalogvecite);
				ֱ���õ������ĵ�ַ����tree��ĳһ����ĸ������ݣ�����ʵ�����֣���������ָ���ƺ�ָ�����һ��
				����ȷ�ĵ�ַ������ֱ��ʹ�õ�ַ��ֻ����vector��[]���������Ҫ������*/
				/*�ٴ��޸ģ������˴�ʹ�õ���vector��ÿ�α���vector��Ԫ�صĵ�ַ������vector����һ�����⣬����
				Ԫ����һ������capacity()Ԥ����Ԫ������������·����ַ����ǰ����ĵ�ַ��ʧЧ�ˡ����Դ˴���Ϊʹ��map��
				map��Ԫ�����ӣ�����ÿ��Ԫ�صĵ�ַ�����*/
				if (((catalog)(catalogmapite->second)).iscatalog)
					recursion(((catalog)(catalogmapite->second)).Id, hItem);
			}
		}
}


void CCaseView::OnContextMenu(CWnd* pWnd, CPoint point)
{
 	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndCaseView;
	ASSERT_VALID(pWndTree);

	//GetCursorPos(&point);//����������λ��
	//ScreenToClient(&point);//ת��Ϊ�ͻ�����
	//UINT uFlags;

	//HTREEITEM CurrentItem;
	//CurrentItem = m_wndCaseView.HitTest(point, &uFlags);//��õ�ǰ����ڵ��ITEM

	////��øýڵ�ĸ��ڵ�
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
		// ѡ���ѵ�������: 
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
	AfxMessageBox(_T("��ӳ�Ա����..."));
}

void CCaseView::OnCaseAddMemberVariable()
{
	// TODO: �ڴ˴���������������
}

void CCaseView::OnCaseDefinition()
{
	// TODO: �ڴ˴���������������
}

void CCaseView::OnCaseProperties()
{
	// TODO: �ڴ˴���������������
}

void CCaseView::OnNewFolder()
{
	AfxMessageBox(_T("�½��ļ���..."));
}

void CCaseView::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

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
		TRACE(_T("�޷�����λͼ: %x\n"), uiBmpId);
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
	//m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* ����*/);
}


void CCaseView::OnNewCase()
{	

	// TODO: �ڴ���������������
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


	// TODO: �ڴ���������������
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
	CString strName; //�޸ĺ������  
	m_wndCaseView.GetEditControl()->GetWindowText(strName);
	if (strName.IsEmpty())
	{
		MessageBox(_T("���������Ʋ���Ϊ�գ�����������!"));
		CEdit *pEdit = m_wndCaseView.EditLabel(TmpItem);
		return;
	}
	/*if (strName == g_sSelectStr)
	{
		return;
	}*/
	//HTREEITEM hRoot = m_wndCaseView.GetRootItem();
	//HTREEITEM hFind = FindItem(hRoot, strName);          //�ж������Ƿ���ͬ  
	//if (hFind == NULL)
	//{
		//char msg[64] = { 0 };
		//sprintf(msg, _T("�޸���ϢΪ%s,ȷ����?"), strName);
		//if (MessageBox(msg, "��ʾ", MB_OKCANCEL) == IDOK)
		//{
			CString strText;
			m_wndCaseView.GetEditControl()->GetWindowText(strText.GetBuffer(200), 200);
			m_wndCaseView.SetItemText(TmpItem, strText);//���ñ༭����ı�Ϊ���  
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
		errmsg.Format(_T("�Ѿ�������ͬcaseID�İ�����caseIdΪ%s"), cata.Id);
		AfxMessageBox(errmsg);
	}
	m_casetree->Close();

	return;
}






void CCaseView::OnNewcatalog()
{
	// TODO: �ڴ���������������
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
		errmsg.Format(_T("�Ѿ�������ͬcaseID��Ŀ¼��caseIdΪ%s"), cata.Id);
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
		((CMainFrame*)AfxGetMainWnd())->m_wndOutput.m_wndOutputBuild.AddString(_T("����һ�����ݡ�"));

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
		errmsg.Format(_T("���ݿ��в����ڸð���caseidΪ %d"), cata.Id);
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
		errmsg.Format(_T("���ݿ��в����ڸð���caseidΪ %d"), cata.Id);
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
		errmsg.Format(_T("���ݿ��в����ڸð���caseidΪ %d"), cata.Id);
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
		errmsg.Format(_T("���ݿ��в����ڸð���caseidΪ %d"), cata.Id);
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
	// TODO: �ڴ���������������
	notPasteCutCase = m_wndCaseView.GetSelectedItem();
	notPasteCopyCase = 0;

}



void CCaseView::OnPastecase()
{
	OnTreeNMKillfocus(0, 0);
	// TODO: �ڴ���������������
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
				//��Ҫ���Ǹ���Ŀ¼ʱ��Ŀ¼�»�����Ŀ¼��Ҫ�ݹ飬�Ƚ��鷳��
				AfxMessageBox(_T("��ʱ��֧�ָ���Ŀ¼��"));	
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
				AfxMessageBox(_T("��ʱ��֧�ָ���Ŀ¼��"));
			}
			
		}
	}
	else if (notPasteCutCase != 0)
	{

		tmpcata = *(catalog*)m_wndCaseView.GetItemData(notPasteCutCase);

		if (!isCatalog) //������ǰ�����ճ���ڸð���ͬĿ¼��
		{
			if (!tmpcata.iscatalog)
			{	//���а���

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
				AfxMessageBox(_T("��ʱ��֧�ּ���Ŀ¼��"));
			}

		}
		else//�������Ŀ¼��ճ���ڸ�Ŀ¼��
		{
			if (!tmpcata.iscatalog)
			{	//���а���

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
				AfxMessageBox(_T("��ʱ��֧�ּ���Ŀ¼��"));
			}

		}

	}

	else
		AfxMessageBox(_T("û�гɹ�����/�����κΰ�����"));
}

CString CCaseView::getCatalogTreeSeqNext()
{
	CString CatalogTreeSeqValue;
	sequenceRecSet *m_seqRecSet = new sequenceRecSet();
	if (m_seqRecSet->IsOpen()) m_seqRecSet->Close();

	CString strSQL = _T("select catalogtreeseq.nextval from dual;");
	BOOL a = m_seqRecSet->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("��ѯBSXDRDEFINEʧ�ܣ���"));

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
		AfxMessageBox(_T("��ѯBSXDRDEFINEʧ�ܣ���"));

	m_seqRecSet->GetFieldValue(_T("NEXTVAL"), CaseTreeSeqValue);

	delete m_seqRecSet;
	return CaseTreeSeqValue;
}



void CCaseView::OnExec()
{
	// TODO: �ڴ���������������
	if (isExecuting == TRUE)
	{
		AfxMessageBox(_T("��ǰ����������ִ�С�"));
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
