#pragma once

#include "stdafx.h"


class sequenceRecSet : public CRecordset
{
public:
	sequenceRecSet(CDatabase* pDatabase);
	sequenceRecSet();

	DECLARE_DYNAMIC(sequenceRecSet)

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��

	float nextval;


public:

	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

