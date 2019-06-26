#pragma once

class CCaseTreeRecSet : public CRecordset
{
public:
	CCaseTreeRecSet(CDatabase* pDatabase);
	CCaseTreeRecSet();

	DECLARE_DYNAMIC(CCaseTreeRecSet)

	// 字段/参数数据

	// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
	// 数据类型的 CStringW)的实际数据类型。
	//  这是为防止 ODBC 驱动程序执行可能
	// 不必要的转换。如果希望，可以将这些成员更改为
	// CString 类型，ODBC 驱动程序将执行所有必要的转换。
	// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
	// 以同时支持 Unicode 和这些转换)。

	float	m_CASEID;
	CStringA	m_CASENAME;
	CTime	m_CREATETIME;
	CTime	m_MODIFYTIME;
	CTime	m_EXPIREDATE;
	float	m_ISUSED;
	CStringA	m_AUTHER;
	CTime  m_executetime;
	float  m_laststatus;
	float	m_catalogid;



public:
	//virtual CString GetDefaultConnect();	// 默认连接字符串

	//virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

														// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};