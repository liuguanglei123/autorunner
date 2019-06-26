#pragma once


// CContentView 窗体视图
typedef int buttonid;
struct butcont
{
	int buttontype; //按钮类型
	int buttonseq;  //按钮序号
};

struct undocasecontent
{
	CString	m_ceshimudi;
	CString m_yuzhitiaojian;
	CString	m_yuqijieguo;
	CString	m_zuihouxiugaizhe;
	CString	m_suoshuyewu;
	CString	m_suoshumokuai;
	CString	m_casexml;
	CString	m_caseconfig;
};

typedef map<int, butcont> buttonattr;
//map中的key值存储的是按钮的ID，bucont存储的是按钮的类型和序号
typedef pair<int, butcont> buttonattrpair;

#include "caseattirecset.h"
#include "ContentSheet.h"


class CContentView : public CFormView
{
	DECLARE_DYNCREATE(CContentView)

protected:
	CContentView();           // 动态创建所使用的受保护的构造函数
	virtual ~CContentView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTENTVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
//public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	afx_msg LRESULT OnCreatebutCleanenv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatebutPredata(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatebutExecShell(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatebuInputEdit(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatebutCompareData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCreatebutCompareFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnShowCatalog(WPARAM wParam, LPARAM lParam);

	

public:
	virtual void OnInitialUpdate();
	CContentSheet  *pSheet;
	static int m_nButSeq;
	CaseAttiSet* m_caseattirecset;
	void DestroyAllItem();
	void CreateNewXml();
	void saveCaseToMemory();
	void saveCaseToDatabase();
	CString m_caseid;

	afx_msg void OnKillFocus(CWnd* pNewWnd);
protected:
	afx_msg LRESULT OnCopycase(WPARAM wParam, LPARAM lParam);
};


