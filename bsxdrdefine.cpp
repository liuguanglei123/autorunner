#include "stdafx.h"
#include "bsxdrdefine.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// BsxdrdefineRecSet ʵ��

// ���������� Saturday, November 18, 2017, 3:41 PM

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
	// RFX_Text() �� RFX_Int() �������������
	// ��Ա���������ͣ����������ݿ��ֶε����͡�
	// ODBC �����Զ�����ֵת��Ϊ�����������
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