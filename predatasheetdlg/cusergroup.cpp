#include "..\stdafx.h"
#include "stdafx.h"

#include "cusergroup.h"
#include "../MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccuserret1Set 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(CCUserGroupRecSet, CRecordset)


CCUserGroupRecSet::CCUserGroupRecSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SERV_ID = 0.0;
	m_GROUP_TYPE = 0.0;
	m_GROUP_ID = 0.0;
	m_PROPERTY = "";
	m_REGION_CODE = 0.0;
	m_BEGIN_DATE;
	m_VALID_DATE;
	m_EXPIRE_DATE;
	m_SID = 0.0;
	m_SO_NBR = 0.0;
	m_REMARK = "";
	m_PRIORITY = 0.0;
	m_GROUP_REGION_CODE = 0.0;
	m_nFields = 13;

	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

CCUserGroupRecSet::CCUserGroupRecSet()
{
	m_SERV_ID = 0.0;
	m_GROUP_TYPE = 0.0;
	m_GROUP_ID = 0.0;
	m_PROPERTY = "";
	m_REGION_CODE = 0.0;
	m_BEGIN_DATE;
	m_VALID_DATE;
	m_EXPIRE_DATE;
	m_SID = 0.0;
	m_SO_NBR = 0.0;
	m_REMARK = "";
	m_PRIORITY = 0.0;
	m_GROUP_REGION_CODE = 0.0;
	m_nFields = 13;

	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void CCUserGroupRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Double(pFX, _T("[SERV_ID]"), m_SERV_ID);
	RFX_Double(pFX, _T("[GROUP_TYPE]"), m_GROUP_TYPE);
	RFX_Double(pFX, _T("[GROUP_ID]"), m_GROUP_ID);
	RFX_Text(pFX, _T("[PROPERTY]"), m_PROPERTY);
	RFX_Double(pFX, _T("[REGION_CODE]"), m_REGION_CODE);
	RFX_Date(pFX, _T("[BEGIN_DATE]"), m_BEGIN_DATE);
	RFX_Date(pFX, _T("[VALID_DATE]"), m_VALID_DATE);
	RFX_Date(pFX, _T("[EXPIRE_DATE]"), m_EXPIRE_DATE);
	RFX_Double(pFX, _T("[SID]"), m_SID);
	RFX_Double(pFX, _T("[SO_NBR]"), m_SO_NBR);
	RFX_Text(pFX, _T("[REMARK]"), m_REMARK);
	RFX_Double(pFX, _T("[PRIORITY]"), m_PRIORITY);
	RFX_Double(pFX, _T("[GROUP_REGION_CODE]"), m_GROUP_REGION_CODE);
}

#ifdef _DEBUG
void CCUserGroupRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCUserGroupRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG