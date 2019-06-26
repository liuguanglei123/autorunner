#pragma once

class CCUserInfoRecSet : public CRecordset
{
public:
	CCUserInfoRecSet(CDatabase* pDatabase);
	CCUserInfoRecSet();

	DECLARE_DYNAMIC(CCUserInfoRecSet)
	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��

	double	m_SERV_ID;
	double	m_GROUP_TYPE;
	double	m_GROUP_ID;
	CStringA	m_PROPERTY;
	double	m_REGION_CODE;
	CTime	m_BEGIN_DATE;
	CTime	m_VALID_DATE;
	CTime	m_EXPIRE_DATE;
	double	m_SID;
	double	m_SO_NBR;
	CStringA	m_REMARK;
	double	m_PRIORITY;
	double	m_GROUP_REGION_CODE;

public:
	//virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	//virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};