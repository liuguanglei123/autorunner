#include "stdafx.h"
#include "sequenceRecSet.h"
#include "MFCApplication1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// BsxdrdefineRecSet ʵ��

// ���������� Saturday, November 18, 2017, 3:41 PM

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
	// RFX_Text() �� RFX_Int() �������������
	// ��Ա���������ͣ����������ݿ��ֶε����͡�
	// ODBC �����Զ�����ֵת��Ϊ�����������
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