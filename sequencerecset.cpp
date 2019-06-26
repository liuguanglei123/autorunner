#include "stdafx.h"
#include "sequenceRecSet.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// BsxdrdefineRecSet 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(sequenceRecSet, CRecordset)


sequenceRecSet::sequenceRecSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	nextval = 0;

	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

sequenceRecSet::sequenceRecSet()
{
	nextval = 0;
	m_nDefaultType = dynaset;
	m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void sequenceRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Single(pFX, _T("[NEXTVAL]"), nextval);
}

#ifdef _DEBUG
void sequenceRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void sequenceRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG