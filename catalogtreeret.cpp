	#include "stdafx.h"
	#include "catalogtreeret.h"
	#include "MFCApplication1.h"

	#ifdef _DEBUG
	#define new DEBUG_NEW
	#endif


	// Ccuserret1Set 实现

	// 代码生成在 Saturday, November 18, 2017, 3:41 PM

	IMPLEMENT_DYNAMIC(CCatalogTreeRecSet, CRecordset)


	CCatalogTreeRecSet::CCatalogTreeRecSet(CDatabase* pdb)
		: CRecordset(pdb)
	{
		m_ID = 0.0;
		m_NAME = "";
		m_CREATETIME;
		m_MODIFYTIME;
		m_EXPIREDATE;
		m_ISUSED = 0.0;
		m_AUTHER = "";
		m_FATHER_ID = 0.0;
		m_nFields = 8;
		m_nDefaultType = dynaset;
		m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
	}

	CCatalogTreeRecSet::CCatalogTreeRecSet()
	{
		m_ID = 0.0;
		m_NAME = "";
		m_CREATETIME;
		m_MODIFYTIME;
		m_EXPIREDATE;
		m_ISUSED = 0.0;
		m_AUTHER = "";
		m_FATHER_ID = 0.0;
		m_nFields = 8;
		m_nDefaultType = dynaset;
		m_pDatabase = &((CMFCApplication1App*)AfxGetApp())->m_database;
	}

	void CCatalogTreeRecSet::DoFieldExchange(CFieldExchange* pFX)
	{
		pFX->SetFieldType(CFieldExchange::outputColumn);
		// RFX_Text() 和 RFX_Int() 这类宏依赖的是
		// 成员变量的类型，而不是数据库字段的类型。
		// ODBC 尝试自动将列值转换为所请求的类型
		RFX_Single(pFX, _T("[ID]"), m_ID);
		RFX_Text(pFX, _T("[NAME]"), m_NAME);
		RFX_Date(pFX, _T("[CREATETIME]"), m_CREATETIME);
		RFX_Date(pFX, _T("[MODIFYTIME]"), m_MODIFYTIME);
		RFX_Date(pFX, _T("[EXPIRETIME]"), m_EXPIREDATE);
		RFX_Single(pFX, _T("[ISUSED]"), m_ISUSED);
		RFX_Text(pFX, _T("[ANTHER]"), m_AUTHER);
		RFX_Single(pFX, _T("[FATHER_ID]"), m_FATHER_ID);
	}

	#ifdef _DEBUG
	void CCatalogTreeRecSet::AssertValid() const
	{
		CRecordset::AssertValid();
	}

	void CCatalogTreeRecSet::Dump(CDumpContext& dc) const
	{
		CRecordset::Dump(dc);
	}
	#endif //_DEBUG