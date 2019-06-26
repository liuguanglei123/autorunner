#include "stdafx.h"
#include "caseattirecset.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CaseAttiSet 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(CaseAttiSet, CRecordset)


CaseAttiSet::CaseAttiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_caseid = 0;
	m_ceshimudi = "";
	m_yuzhitiaojian = "";
	m_yuqijieguo = "";
	m_zuihouxiugaizhe = "";
	m_suoshuyewu = "";
	m_suoshumokuai = "";
	m_casexml = "";
	m_caseconfig = "";
	m_nFields = 9;

	m_nDefaultType = snapshot;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

CaseAttiSet::CaseAttiSet()
{
	m_caseid = 0;
	m_ceshimudi = "";
	m_yuzhitiaojian = "";
	m_yuqijieguo = "";
	m_zuihouxiugaizhe = "";
	m_suoshuyewu = "";
	m_suoshumokuai = "";
	m_casexml = "";
	m_caseconfig = "";
	m_nFields = 9;

	m_nDefaultType = snapshot;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void CaseAttiSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Single(pFX, _T("[CASEID]"), m_caseid);
	RFX_Text(pFX, _T("[CESHIMUDI]"), m_ceshimudi);
	RFX_Text(pFX, _T("[YUZHITIAOJIAN]"), m_yuzhitiaojian);
	RFX_Text(pFX, _T("[YUQIJIEGUO]"), m_yuqijieguo);
	RFX_Text(pFX, _T("[ZUIHOUXIUGAIZHE]"), m_zuihouxiugaizhe);
	RFX_Text(pFX, _T("[SUOSHUYEWU]"), m_suoshuyewu);
	RFX_Text(pFX, _T("[SUOSHUMOKUAI]"), m_suoshumokuai);
	RFX_Text(pFX, _T("[CASECONTENT]"), m_casexml, 240000);
	RFX_Text(pFX, _T("[CASECONFIGXML]"), m_caseconfig, 240000);
}

#ifdef _DEBUG
void CaseAttiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CaseAttiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG