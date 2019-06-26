// ContentView.cpp : ʵ���ļ�
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

// CContentView ���

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


// CContentView ��Ϣ�������


HBRUSH CContentView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	hbr = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));

	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)::GetStockObject(WHITE_BRUSH);  // ���ñ���ɫ

	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
			AfxMessageBox(_T("��ѯcaseatti��ʧ�ܣ���"));
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


	//AfxMessageBox(_T("��Ϣ������contentview"));
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


	// TODO: �ڴ����ר�ô����/����û���
}


void CContentView::DestroyAllItem()
{
	//�����һ���µ�case��ʱ�����ȵ��������������������ccontentpage1��ccontentpage2�е���������
	//δ�������  ���ccontentpage1����������
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
		//AfxMessageBox(_T("Ҫ��ѡ��һ���������ܱ��档"));
	}

	return;
}

void CContentView::OnKillFocus(CWnd* pNewWnd)
{
	CFormView::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
}


afx_msg LRESULT CContentView::OnCopycase(WPARAM wParam, LPARAM lParam)
{
	//wparam �������Ҫ���Ƶ�caseid��lparam��������µ��µ�caseid
	if (m_caseattirecset->IsOpen())
		m_caseattirecset->Close();
	undocasecontent tmpcopycase;
	CString strSQL;
	strSQL.Format(_T("select CASEID,CESHIMUDI,YUZHITIAOJIAN,YUQIJIEGUO,ZUIHOUXIUGAIZHE,SUOSHUYEWU,SUOSHUMOKUAI,CASECONTENT,CASECONFIGXML\
					 from caseatti a where caseid=%d;"), wParam);
	BOOL a = m_caseattirecset->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("����caseatti��ʧ�ܣ���"));
	if (m_caseattirecset->GetRecordCount() == 0)
	{
		AfxMessageBox(_T("�����Ƶİ���û������"));
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
