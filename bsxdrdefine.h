#pragma once

#include "stdafx.h"

typedef struct xdrdefine {
	CStringA xdr_field_name;
	CStringA xdr_dr_type;
	CStringA xdr_field_type;
	CStringA xdr_field_index;
} xdrdefineattr;


//typedef vector<xdrdefineattr> xdrdefineattrvec;

//typedef map<CStringA, xdrdefineattrvec> xdrdefineattrmap;


class BsxdrdefineRecSet : public CRecordset
{
public:
	BsxdrdefineRecSet(CDatabase* pDatabase);
	BsxdrdefineRecSet();

	DECLARE_DYNAMIC(BsxdrdefineRecSet)

	// 字段/参数数据

	// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
	// 数据类型的 CStringW)的实际数据类型。
	//  这是为防止 ODBC 驱动程序执行可能
	// 不必要的转换。如果希望，可以将这些成员更改为
	// CString 类型，ODBC 驱动程序将执行所有必要的转换。
	// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
	// 以同时支持 Unicode 和这些转换)。

	CStringA xdr_field_name;
	CStringA	xdr_dr_type;
	float 	xdr_field_type;
	float	xdr_field_index;


public:

	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

														// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

