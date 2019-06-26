// ContentView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ContentView.h"
#include "ChildFrm.h"
#include "MainFrm.h"

int CContentView::m_nButSeq = 1;
buttonattr butattr;


// CContentView

IMPLEMENT_DYNCREATE(CContentView, CFormView)

CContentView::CContentView()
	: CFormView(IDD_CONTENTVIEW)
{
	m_caseattirecset = new CaseAttiSet();
}

CContentView::~CContentView()
{
}

void CContentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CContentView, CFormView)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_CREATEBUT_CLEANENV, &CContentView::OnCreatebutCleanenv)
	ON_MESSAGE(WM_CREATEBUT_PREDATA, &CContentView::OnCreatebutPredata)
	ON_MESSAGE(WM_CREATEBUT_EXECSHELL, &CContentView::OnCreatebutExecShell)
	ON_MESSAGE(WM_CREATEBUT_INPUTEDIT, &CContentView::OnCreatebuInputEdit)
	ON_MESSAGE(WM_CREATEBUT_COMPAREFILE, &CContentView::OnCreatebutCompareData)
	ON_MESSAGE(WM_CREATEBUT_COMPAREDATA, &CContentView::OnCreatebutCompareFile)
	ON_MESSAGE(WM_CATALOGSHOW, &CContentView::OnShowCatalog)

	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_COPYCASE, &CContentView::OnCopycase)
END_MESSAGE_MAP()

// CContentView 诊断

#ifdef _DEBUG
void CContentView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CContentView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CContentView 消息处理程序


HBRUSH CContentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


afx_msg LRESULT CContentView::OnCreatebutCleanenv(WPARAM wParam, LPARAM lParam)
{
	
	return TRUE;
}


afx_msg LRESULT CContentView::OnCreatebutPredata(WPARAM wParam, LPARAM lParam)
{
	int active_index = pSheet->GetActiveIndex();
	if (0 == active_index)
		pSheet->SetActivePage(1);
	int buttionid;
	buttionid=((CContentPage2*)pSheet->GetPage(1))->CreateBut(m_nButSeq, PREDATA);
	if (buttionid == 0)
	{
		return FALSE;
	}
	buttonattrpair newbutattr(buttionid, { PREDATA,m_nButSeq });
	butattr.insert(newbutattr);
	m_nButSeq++;

	saveCaseToMemory();
	return TRUE;
}


afx_msg LRESULT CContentView::OnCreatebutExecShell(WPARAM wParam, LPARAM lParam)
{
	int active_index = pSheet->GetActiveIndex();
	if (0 == active_index)
		pSheet->SetActivePage(1);
	int buttionid;
	buttionid = ((CContentPage2*)pSheet->GetPage(1))->CreateBut(m_nButSeq, EXECSHELL);
	if (buttionid == 0)
	{
		return FALSE;
	}
	buttonattrpair newbutattr(buttionid, { EXECSHELL,m_nButSeq });
	butattr.insert(newbutattr);
	m_nButSeq++;
	return TRUE;
}

afx_msg LRESULT CContentView::OnCreatebuInputEdit(WPARAM wParam, LPARAM lParam)
{
	int active_index = pSheet->GetActiveIndex();
	if (0 == active_index)
		pSheet->SetActivePage(1);
	int buttionid;
	buttionid = ((CContentPage2*)pSheet->GetPage(1))->CreateBut(m_nButSeq, INPUTEDIT);
	if (buttionid == 0)
	{
		return TRUE;
	}
	buttonattrpair newbutattr(buttionid, { INPUTEDIT,m_nButSeq });
	butattr.insert(newbutattr);
	m_nButSeq++;
	return TRUE;
}

afx_msg LRESULT CContentView::OnCreatebutCompareData(WPARAM wParam, LPARAM lParam)
{
	int active_index = pSheet->GetActiveIndex();
	if (0 == active_index)
		pSheet->SetActivePage(1);
	int buttionid;
	buttionid = ((CContentPage2*)pSheet->GetPage(1))->CreateBut(m_nButSeq, COMPAREDATA);
	if (buttionid == 0)
	{
		return TRUE;
	}
	buttonattrpair newbutattr(buttionid, { COMPAREDATA ,m_nButSeq });
	butattr.insert(newbutattr);
	m_nButSeq++;
	return TRUE;
}

afx_msg LRESULT CContentView::OnCreatebutCompareFile(WPARAM wParam, LPARAM lParam)
{

	return TRUE;
}


afx_msg LRESULT CContentView::OnShowCatalog(WPARAM wParam, LPARAM lParam)
{
	int active_index = pSheet->GetActiveIndex();
	if (0 == active_index)
		pSheet->SetActivePage(1);
	
	saveCaseToDatabase();
	DestroyAllItem();


	if (m_caseattirecset->IsOpen())
		m_caseattirecset->Close();
	CString strSQL;
	strSQL.Format(_T("select CASEID,CESHIMUDI,YUZHITIAOJIAN,YUQIJIEGUO,ZUIHOUXIUGAIZHE,SUOSHUYEWU,SUOSHUMOKUAI,CASECONTENT,CASECONFIGXML\
					 from caseatti a where caseid=%d;"), wParam);
	m_caseid.Format(_T("%d"),wParam);
	if (!lParam)
	{
		BOOL a = m_caseattirecset->Open(CRecordset::snapshot, strSQL);
		if (!a)
			AfxMessageBox(_T("查询caseatti表失败！！"));
		if (!m_caseattirecset->IsEOF()) {
			m_caseattirecset->MoveFirst();
		}

		if (m_caseattirecset->GetRecordCount() == 0)
		{
			CreateNewXml();
			return TRUE;
		}

		m_caseattirecset->GetFieldValue(_T("CASEID"), m_caseid);
		/*m_caseattirecset->GetFieldValue(_T("CESHIMUDI"), m_ceshimudi);
		m_caseattirecset->GetFieldValue(_T("YUZHITIAOJIAN"), m_yuzhitiaojian);
		m_caseattirecset->GetFieldValue(_T("YUZHITIAOJIAN"), m_yuqijieguo);
		m_caseattirecset->GetFieldValue(_T("ZUIHOUXIUGAIZHE"), m_zuihouxiugaizhe);
		m_caseattirecset->GetFieldValue(_T("SUOSHUYEWU"), m_suoshuyewu);

		m_caseattirecset->GetFieldValue(_T("SUOSHUMOKUAI"), m_suoshumokuai);*/
		m_caseattirecset->GetFieldValue(_T("CASECONTENT"), ((CContentPage2*)pSheet->GetPage(1))->m_casexml);
		m_caseattirecset->GetFieldValue(_T("CASECONFIGXML"), ((CContentPage2*)pSheet->GetPage(1))->m_caseconfig);
		((CContentPage2*)pSheet->GetPage(1))->analysexml();

	}


	//AfxMessageBox(_T("消息到达了contentview"));
	return TRUE;
}

void CContentView::OnInitialUpdate()
{
 	CFormView::OnInitialUpdate();
	RECT rect;
	CString changkuanggao;
	(((CChildFrame*)GetParentFrame())->rightview)->GetClientRect(&rect);
	changkuanggao.Format(_T("rightview %d %d"), rect.bottom-rect.top,rect.right-rect.left);

	AfxGetMainWnd()->GetClientRect(&rect);
	changkuanggao.Format(_T("mainframe %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndOutput).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndOutput %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndCaseView).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndCaseView %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndProperties).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndProperties %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndMenuBar).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndMenuBar %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndStatusBar).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndStatusBar %d %d"), rect.bottom - rect.top, rect.right - rect.left);

	(((CMainFrame*)AfxGetMainWnd())->m_wndToolBar).GetClientRect(&rect);
	changkuanggao.Format(_T("m_wndToolBar %d %d"), rect.bottom - rect.top, rect.right - rect.left);


	pSheet = new CContentSheet(_T("TEST"), this, NULL);
	//pSheet ->Create(this, WS_CHILD | WS_VISIBLE/*|WS_TILEDWINDOW*/, WS_EX_TOPMOST); 
	

	pSheet->Create(this, WS_CHILD | WS_VISIBLE);
	
	pSheet->SetWindowPos(NULL,0,0,1500,900,SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE);  
	pSheet->MoveWindow(0, 0, 1500, 900, TRUE);
	pSheet->ShowWindow(SW_SHOW);


	// TODO: 在此添加专用代码和/或调用基类
}


void CContentView::DestroyAllItem()
{
	//当点击一个新的case的时候，首先调用这个函数，用来销毁ccontentpage1和ccontentpage2中的所有内容
	//未完成内容  清除ccontentpage1的所有内容
	//((CContentPage2*)pSheet->GetPage(1))->m_casexml
	((CContentPage2*)pSheet->GetPage(1))->DeleteAllItems();
	butattr.clear();
	CContentView::m_nButSeq = 1;
}


void CContentView::CreateNewXml()
{
	
	/*((CContentPage2*)pSheet->GetPage(1))->m_casexml=_T("");
	((CContentPage2*)pSheet->GetPage(1))->m_caseconfig = _T("");*/

	((CContentPage2*)pSheet->GetPage(1))->CreateNewXml();
}




void CContentView::saveCaseToMemory()
{
	return ;
}

void CContentView::saveCaseToDatabase()
{
	if (m_caseattirecset->IsOpen())
	{
		if (m_caseattirecset->GetRecordCount() == 0)
		{
			//insert
			int abc = m_caseattirecset->m_nFields;
			m_caseattirecset->AddNew();
			m_caseattirecset->m_caseid = _ttoi(m_caseid);
			m_caseattirecset->m_casexml = ((CContentPage2*)pSheet->GetPage(1))->m_casexml;
			m_caseattirecset->m_caseconfig = ((CContentPage2*)pSheet->GetPage(1))->m_caseconfig;
			m_caseattirecset->Update();
		}
		else
		{
			//update
			m_caseattirecset->Edit();
			m_caseattirecset->m_casexml = ((CContentPage2*)pSheet->GetPage(1))->m_casexml;
			m_caseattirecset->m_caseconfig = ((CContentPage2*)pSheet->GetPage(1))->m_caseconfig;
			m_caseattirecset->Update();
		}
	}
	else
	{
		//AfxMessageBox(_T("要先选中一个案例才能保存。"));
	}

	return;
}

void CContentView::OnKillFocus(CWnd* pNewWnd)
{
	CFormView::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
}


afx_msg LRESULT CContentView::OnCopycase(WPARAM wParam, LPARAM lParam)
{
	//wparam 保存的需要复制的caseid，lparam保存的是新的新的caseid
	if (m_caseattirecset->IsOpen())
		m_caseattirecset->Close();
	undocasecontent tmpcopycase;
	CString strSQL;
	strSQL.Format(_T("select CASEID,CESHIMUDI,YUZHITIAOJIAN,YUQIJIEGUO,ZUIHOUXIUGAIZHE,SUOSHUYEWU,SUOSHUMOKUAI,CASECONTENT,CASECONFIGXML\
					 from caseatti a where caseid=%d;"), wParam);
	BOOL a = m_caseattirecset->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("插入caseatti表失败！！"));
	if (m_caseattirecset->GetRecordCount() == 0)
	{
		AfxMessageBox(_T("被复制的案例没有内容"));
		return TRUE;
	}
	CString tmpceshimudi, tmpyuzhitiaojian, tmpyuqijieguo, tmpzuihouxiugaizhe, tmpsuoshuyewu, tmpsuoshumokuai, tmpcasecml, tmpcaseconfig;

	/*m_caseattirecset->GetFieldValue(_T("CASEID"), m_caseid);
	m_caseattirecset->GetFieldValue(_T("CESHIMUDI"), m_ceshimudi);
	m_caseattirecset->GetFieldValue(_T("YUZHITIAOJIAN"), m_yuzhitiaojian);
	m_caseattirecset->GetFieldValue(_T("YUZHITIAOJIAN"), m_yuqijieguo);
	m_caseattirecset->GetFieldValue(_T("ZUIHOUXIUGAIZHE"), m_zuihouxiugaizhe);
	m_caseattirecset->GetFieldValue(_T("SUOSHUYEWU"), m_suoshuyewu);

	m_caseattirecset->GetFieldValue(_T("SUOSHUMOKUAI"), m_suoshumokuai);*/
	m_caseattirecset->GetFieldValue(_T("CASECONTENT"), tmpcasecml);
	m_caseattirecset->GetFieldValue(_T("CASECONFIGXML"), tmpcaseconfig);

	m_caseattirecset->AddNew();
	m_caseattirecset->m_caseid = lParam;
	m_caseattirecset->m_casexml = tmpcasecml;
	m_caseattirecset->m_caseconfig = tmpcaseconfig;
	m_caseattirecset->Update();


	m_caseattirecset->Close();
	return 0;
}
