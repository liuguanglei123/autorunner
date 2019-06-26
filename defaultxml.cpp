#include "stdafx.h"
#include "defaultxml.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//   DefaultXmlRecSet 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(DefaultXmlRecSet, CRecordset)


DefaultXmlRecSet::DefaultXmlRecSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	busitype = "";
	flowtype = "";
	defaultxml = "";
	m_nFields = 3;

	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

DefaultXmlRecSet::DefaultXmlRecSet()
{
	busitype = "";
	flowtype = "";
	defaultxml = "";
	m_nFields = 3;

	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void   DefaultXmlRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[BUSITYPE]"), busitype);
	RFX_Text(pFX, _T("[FLOWTYPE]"), flowtype);
	RFX_Text(pFX, _T("[DEFAULTXML]"), defaultxml,240000);
}

#ifdef _DEBUG
void   DefaultXmlRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void   DefaultXmlRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG