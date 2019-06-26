#include "stdafx.h"
#include "casetreeret.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccuserret1Set 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(CCaseTreeRecSet, CRecordset)


CCaseTreeRecSet::CCaseTreeRecSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CASEID = 0.0;
	m_CASENAME = "";
	m_CREATETIME;
	m_MODIFYTIME;
	m_EXPIREDATE;
	m_ISUSED = 0.0;
	m_AUTHER = "";
	m_executetime;
	m_laststatus = 0;
	m_catalogid = 0;
	m_nFields = 10;

	m_nDefaultType = snapshot;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

CCaseTreeRecSet::CCaseTreeRecSet()
{
	m_CASEID = 0.0;
	m_CASENAME = "";
	m_CREATETIME;
	m_MODIFYTIME;
	m_EXPIREDATE;
	m_ISUSED = 0.0;
	m_AUTHER = "";
	m_executetime;
	m_laststatus = 0;
	m_catalogid = 0;
	m_nFields = 10;

	m_nDefaultType = snapshot;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void CCaseTreeRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Single(pFX, _T("[CASEID]"), m_CASEID);
	RFX_Text(pFX, _T("[CASENAME]"), m_CASENAME);
	RFX_Date(pFX, _T("[CREATETIME]"), m_CREATETIME);
	RFX_Date(pFX, _T("[MODIFYTIME]"), m_MODIFYTIME);
	RFX_Date(pFX, _T("[EXPIRETIME]"), m_EXPIREDATE);
	RFX_Single(pFX, _T("[ISUSED]"), m_ISUSED);
	RFX_Text(pFX, _T("[AUTHER]"), m_AUTHER);
	RFX_Date(pFX, _T("[EXECUTETIME]"), m_executetime);
	RFX_Single(pFX, _T("[LASTSTATUS]"), m_laststatus);
	RFX_Single(pFX, _T("[CATALOGID]"), m_catalogid);
}

#ifdef _DEBUG
void CCaseTreeRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCaseTreeRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG