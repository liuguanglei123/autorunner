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
	CExecCaseThread();           // 动态创建所使用的受保护的构造函数
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
	vector<funcstruct> func_assemble;  //用来存储func_define的数据，与contentview中的butattr变量类似
	map<int, XMLElement*> node_assemble;//用来存储xml化的配置内容

	BOOL queryXml(CString strCaseId);
	CString m_casexml;
	CString m_caseconfig;
	BOOL analyseXml();
	BOOL execEachStep();
	BOOL InitSock();
};


