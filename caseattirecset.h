#pragma once

#include "stdafx.h"

class CaseAttiSet : public CRecordset
{
public:
	CaseAttiSet(CDatabase* pDatabase);
	CaseAttiSet();

	DECLARE_DYNAMIC(CaseAttiSet)

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��

	float m_caseid;
	CStringA	m_ceshimudi;
	CStringA 	m_yuzhitiaojian;
	CStringA	m_yuqijieguo;
	CStringA	m_zuihouxiugaizhe;
	CStringA	m_suoshuyewu;
	CStringA	m_suoshumokuai;
	CStringA	m_casexml;
	CStringA	m_caseconfig;


public:

	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

