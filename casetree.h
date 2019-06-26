#pragma once

#include "ViewTree.h"
#include "catalogtreeret.h"
#include "casetreeret.h"

struct catalog
{
	CString Id;
	CString Father_Id;
	CString Name;
	BOOL iscatalog; //ΪtrueʱΪĿ¼��ΪfalseʱΪcase

};
enum dealType
{
	NODO=0,INSERTCASE,INSERTCATALOG,UPDATECASE,UPDATECATALOG,DELETECASE,DELETECATALOG
};


struct undoDataDeal
{
	int actionType;//0Ϊ������1Ϊ����������2Ϊ����Ŀ¼��3Ϊ���°�����4Ϊ����Ŀ¼��5Ϊɾ��������6Ϊɾ��Ŀ¼
	HTREEITEM item; //��Ҫ���µ����нڵ�ľ��
	catalog cata;	//��Ҫ���µ����нڵ�����Ӧ��data����Ӧ�ĺ�������getitemdata��setitemdata
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

	// ��д
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

	afx_msg void OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);  //��ʼ�༭  
	afx_msg void OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult);   //�����༭ 

	DECLARE_MESSAGE_MAP()

private:
	CCatalogTreeRecSet *m_catalogtree;
	CCaseTreeRecSet *m_casetree;
	int catalogseq;
	map<int,catalog> catalogmap;
	HTREEITEM notPasteCopyCase; //�����Ƶ�caseid
	HTREEITEM notPasteCutCase;  //�����е�caseid
	CString getCatalogTreeSeqNext();
	CString getCaseTreeSeqNext();

public:
	afx_msg void OnNewCase();
	afx_msg void OnRename();
	HTREEITEM TmpItem;
	BOOL isExecuting;
	void insertCaseTree(catalog cata); //����һ���µ�casetree����
	void insertCaseCatalog(catalog cata); //����һ���µ�casetree����

	void deleteCaseTree(catalog cata); //ɾ��һ��casetree����
	void deleteCatalogTree(catalog cata); //ɾ��һ��casetree����

	void updateCaseTree(catalog cata); //����һ��casetree����
	void updateCatalogTree(catalog cata); //����һ��casetree����


	afx_msg void OnNewcatalog();
	vector<undoDataDeal> undoDataDealVec;
	afx_msg void OnTreeNMKillfocus(NMHDR* pNMHDR, LRESULT* pResult);  //��ʧȥ����

	afx_msg void OnDelete();
	afx_msg void OnCopycase();
	afx_msg void OnPastecase();
	afx_msg void OnCutcase();
	afx_msg void OnExec();
};


