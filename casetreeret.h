#pragma once

class CCaseTreeRecSet : public CRecordset
{
public:
	CCaseTreeRecSet(CDatabase* pDatabase);
	CCaseTreeRecSet();

	DECLARE_DYNAMIC(CCaseTreeRecSet)

	// �ֶ�/��������

	// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
	// �������͵� CStringW)��ʵ���������͡�
	//  ����Ϊ��ֹ ODBC ��������ִ�п���
	// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
	// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
	// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
	// ��ͬʱ֧�� Unicode ����Щת��)��

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
	//virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	//virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

														// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};