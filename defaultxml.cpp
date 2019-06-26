#include "stdafx.h"
#include "defaultxml.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//   DefaultXmlRecSet ʵ��

// ���������� Saturday, November 18, 2017, 3:41 PM

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
	// RFX_Text() �� RFX_Int() �������������
	// ��Ա���������ͣ����������ݿ��ֶε����͡�
	// ODBC �����Զ�����ֵת��Ϊ�����������
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