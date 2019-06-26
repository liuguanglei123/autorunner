#pragma once

#include "ViewTree.h"
#include "catalogtreeret.h"
#include "casetreeret.h"

struct catalog
{
	CString Id;
	CString Father_Id;
	CString Name;
	BOOL iscatalog; //为true时为目录，为false时为case

};
enum dealType
{
	NODO=0,INSERTCASE,INSERTCATALOG,UPDATECASE,UPDATECATALOG,DELETECASE,DELETECATALOG
};


struct undoDataDeal
{
	int actionType;//0为不处理，1为新增案例，2为新增目录，3为更新案例，4为更新目录，5为删除案例，6为删除目录
	HTREEITEM item; //需要更新的树中节点的句柄
	catalog cata;	//需要更新的树中节点句柄对应的data，对应的函数包括getitemdata和setitemdata
};


class CCaseToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CCaseView : public CDockablePane
{
public:
	CCaseView();
	virtual ~CCaseView();

	void AdjustLayout();
	void OnChangeVisualStyle();

protected:
	//CClassToolBar m_wndToolBar;
	CViewTree m_wndCaseView;
	CImageList m_CaseViewImages;
	UINT m_nCurrSort;

	void FillCaseView();

	// 重写
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCaseAddMemberFunction();
	afx_msg void OnCaseAddMemberVariable();
	afx_msg void OnCaseDefinition();
	afx_msg void OnCaseProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);
	afx_msg void recursion(CString ID,HTREEITEM treeeitem = (HTREEITEM)0);

	afx_msg void OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);  //开始编辑  
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);   //结束编辑 

	DECLARE_MESSAGE_MAP()

private:
	CCatalogTreeRecSet *m_catalogtree;
	CCaseTreeRecSet *m_casetree;
	int catalogseq;
	map<int,catalog> catalogmap;
	HTREEITEM notPasteCopyCase; //被复制的caseid
	HTREEITEM notPasteCutCase;  //被剪切的caseid
	CString getCatalogTreeSeqNext();
	CString getCaseTreeSeqNext();

public:
	afx_msg void OnNewCase();
	afx_msg void OnRename();
	HTREEITEM TmpItem;
	BOOL isExecuting;
	void insertCaseTree(catalog cata); //插入一条新的casetree数据
	void insertCaseCatalog(catalog cata); //插入一条新的casetree数据

	void deleteCaseTree(catalog cata); //删除一条casetree数据
	void deleteCatalogTree(catalog cata); //删除一条casetree数据

	void updateCaseTree(catalog cata); //更新一条casetree数据
	void updateCatalogTree(catalog cata); //更新一条casetree数据


	afx_msg void OnNewcatalog();
	vector<undoDataDeal> undoDataDealVec;
	afx_msg void OnTreeNMKillfocus(NMHDR* pNMHDR, LRESULT* pResult);  //树失去焦点

	afx_msg void OnDelete();
	afx_msg void OnCopycase();
	afx_msg void OnPastecase();
	afx_msg void OnCutcase();
	afx_msg void OnExec();
};


