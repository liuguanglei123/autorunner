#include "stdafx.h"
#include "bsxdrdefine.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// BsxdrdefineRecSet 实现

// 代码生成在 Saturday, November 18, 2017, 3:41 PM

IMPLEMENT_DYNAMIC(BsxdrdefineRecSet, CRecordset)


BsxdrdefineRecSet::BsxdrdefineRecSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	xdr_field_name = "";
	xdr_dr_type = "";
	xdr_field_type = 0;
	xdr_field_index = 0;

	m_nDefaultType = snapshot;
	//m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

BsxdrdefineRecSet::BsxdrdefineRecSet()
{
	xdr_field_name = "";
	xdr_dr_type = "";
	xdr_field_type = 0;
	xdr_field_index = 0;
	m_nDefaultType = snapshot;
	//m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
}

void BsxdrdefineRecSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// RFX_Text() 和 RFX_Int() 这类宏依赖的是
	// 成员变量的类型，而不是数据库字段的类型。
	// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[XDR_FIELD_NAME]"), xdr_field_name);
	RFX_Text(pFX, _T("[XDR_DR_TYPE]"), xdr_dr_type);
	RFX_Single(pFX, _T("[XDR_FIELD_TYPE]"), xdr_field_type);
	RFX_Single(pFX, _T("[XDR_FIELD_INDEX]"), xdr_field_index);
}

#ifdef _DEBUG
void BsxdrdefineRecSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void BsxdrdefineRecSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG