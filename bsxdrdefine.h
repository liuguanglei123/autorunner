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

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA xdr_field_name;
	CStringA	xdr_dr_type;
	float 	xdr_field_type;
	float	xdr_field_index;


public:

	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

