#pragma once



// CExecCaseThread
class CaseAttiSet;

struct funcstruct
{
	int func_seq;
	CString func_name;
	int background_execution;
};
class CExecCaseThread : public CWinThread
{
	DECLARE_DYNCREATE(CExecCaseThread)

protected:
	CExecCaseThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CExecCaseThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
	virtual BOOL OnIdle(LONG lCount);
	CaseAttiSet* m_caseattirecset;
	vector<funcstruct> func_assemble;  //�����洢func_define�����ݣ���contentview�е�butattr��������
	map<int, XMLElement*> node_assemble;//�����洢xml������������

	BOOL queryXml(CString strCaseId);
	CString m_casexml;
	CString m_caseconfig;
	BOOL analyseXml();
	BOOL execEachStep();
	BOOL InitSock();
};


