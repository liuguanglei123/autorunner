// ExecCaseThread.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ExecCaseThread.h"
#include "MainFrm.h"
#include "caseattirecset.h"
#include "ContentPage2.h"

//#include "libssh2_config.h"
//#include <libssh2.h>
//#include <libssh2_sftp.h>

// CExecCaseThread

WSADATA wsadata;

extern CMainFrame* m_pCWnd;
extern vector<CString> execCaseVec;
extern int _string2enum(CString name);
extern BOOL PreDataDlgExec(XMLElement* xmlConfig);

IMPLEMENT_DYNCREATE(CExecCaseThread, CWinThread)

CExecCaseThread::CExecCaseThread()
{
	m_caseattirecset = new CaseAttiSet();
}

CExecCaseThread::~CExecCaseThread()
{
}

BOOL CExecCaseThread::InitInstance()
{
	// TODO:    在此执行任意逐线程初始化
	return TRUE;
}

int CExecCaseThread::ExitInstance()
{
	// TODO:    在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CExecCaseThread, CWinThread)
END_MESSAGE_MAP()


// CExecCaseThread 消息处理程序


int CExecCaseThread::Run()
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinThread::Run();
}


BOOL CExecCaseThread::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类
	//m_pCWnd->m_wndOutput.m_wndOutputBuild.AddString(_T("1234"));
	//_sleep(10000);
	vector<CString>::iterator itr= execCaseVec.begin();
	int i = 0;
	for (int i = 0; itr != execCaseVec.end(); )
	{
		queryXml(execCaseVec[i]);

		InitSock();

		analyseXml();

		execEachStep();

		itr = execCaseVec.erase(itr);
	}


	return CWinThread::OnIdle(lCount);
}


BOOL CExecCaseThread::queryXml(CString strCaseId)
{

	if (m_caseattirecset->IsOpen())
		m_caseattirecset->Close();
	CString strSQL;
	strSQL.Format(_T("select CASEID,CESHIMUDI,YUZHITIAOJIAN,YUQIJIEGUO,ZUIHOUXIUGAIZHE,SUOSHUYEWU,SUOSHUMOKUAI,CASECONTENT,CASECONFIGXML\
					 from caseatti a where caseid=%s;"), strCaseId);

	BOOL a = m_caseattirecset->Open(CRecordset::snapshot, strSQL);
	if (!a)
		AfxMessageBox(_T("查询caseatti表失败！！"));
	if (!m_caseattirecset->IsEOF()) {
		m_caseattirecset->MoveFirst();
	}

	if (m_caseattirecset->GetRecordCount() == 0)
	{
		return TRUE;
	}

	m_caseattirecset->GetFieldValue(_T("CASECONTENT"), m_casexml);
	m_caseattirecset->GetFieldValue(_T("CASECONFIGXML"), m_caseconfig);

	return 0;
}


BOOL CExecCaseThread::analyseXml()
{
	func_assemble.clear();
	node_assemble.clear();
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->Parse(m_casexml);
	XMLElement* root = doc->FirstChildElement("root");

	XMLElement* func_define = root->FirstChildElement("func_define");
	XMLElement* function = func_define->FirstChildElement("function");

	while (function)
	{
		funcstruct tmp_funcstruct;
		tmp_funcstruct.func_seq = atoi((function->FirstChildElement("func_seq"))->GetText());
		tmp_funcstruct.func_name = (function->FirstChildElement("func_name"))->GetText();
		tmp_funcstruct.background_execution = atoi((function->FirstChildElement("background_execution"))->GetText());

		func_assemble.push_back(tmp_funcstruct);
		function = function->NextSiblingElement();
	}

	XMLElement* flows = root->FirstChildElement("flows");
	XMLElement* flow = flows->FirstChildElement("flow");

	while (flow)
	{
		pair<int, XMLElement*> tmp_nodeasseble;
		//tmp_funcstruct.func_seq = atoi((flow->FirstChildElement("flow_name"))->GetText());
		int seqno = atoi((flow->FirstChildElement("flow_seq"))->GetText());
		node_assemble[seqno] = flow;
		flow = flow->NextSiblingElement();
	}

	return 0;
}


BOOL CExecCaseThread::execEachStep()
{
	for (int i = 1; i <= func_assemble.size(); i++)
	{
		vector<funcstruct>::iterator funcite;
		for (funcite = func_assemble.begin(); funcite != func_assemble.end(); funcite++)
		{
			if (funcite->func_seq == i)
			{
				switch (STR_ENUM_GET(funcite->func_name))
				{
				case CLEANENV:
				{	break;	}
				case PREDATA:
				{	
					PreDataDlgExec(node_assemble[funcite->func_seq]);
					break;	
				}
				case INPUTEDIT:
				{	break;	}
				case EXECSHELL:
				{	break;	}
				case COMPAREFILE:
				{	break;	}
				case COMPAREDATA:
				{	break;	}
				default:
					break;

				}
			}
		}
	}


	return 0;
}



BOOL CExecCaseThread::InitSock()
{
//	int err;
//
//	err = WSAStartup(MAKEWORD(2, 0), &wsadata);
//	if (err != 0) {
//		CString errmsg;
//		errmsg.Format(_T("WSAStartup failed with error: %d\n"), err);
//		AfxMessageBox(errmsg);
//		return FALSE; 
//	}
//
//	unsigned long hostaddr;
//	const char *username = "liuguanglei";
//	const char *password = "744868";
//
//	hostaddr = htonl(0xC0A85686);//写死的十六进制地址192.168.86.134
//
//	int rc;
//	rc = libssh2_init(0);
//	if (rc != 0) {
//		fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
//		return FALSE;
//	}
//
//	int sock;
//	sock = socket(AF_INET, SOCK_STREAM, 0);
//
//	struct sockaddr_in sin;
//
//	sin.sin_family = AF_INET;
//	sin.sin_port = htons(22);
//	sin.sin_addr.s_addr = hostaddr;
//	if (connect(sock, (struct sockaddr*)(&sin),
//		sizeof(struct sockaddr_in)) != 0) {
//		fprintf(stderr, "failed to connect!\n");
//		return FALSE;
//	}
//	LIBSSH2_SESSION *session;
//	session = libssh2_session_init();
//	if (!session)
//		return FALSE;
//	libssh2_session_set_blocking(session, 1);
//	rc = libssh2_session_handshake(session, sock);
//
//	if (rc) {
//		fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
//		return FALSE;
//	}
//	if (libssh2_userauth_password(session, username, password)) {
//
//		fprintf(stderr, "Authentication by password failed.\n");
//		return FALSE;
//	}
//	LIBSSH2_SFTP *sftp_session;
//	LIBSSH2_SFTP_HANDLE *sftp_handle;
//	sftp_session = libssh2_sftp_init(session);
//	if (!sftp_session) {
//		fprintf(stderr, "Unable to init SFTP session\n");
//		return FALSE;
//	}
//
//	const char *sftppath = "/tmp/TEST";
//	const char* xdr = ";090707;50001;;;;;;;;;;;;;;;;00861053946522;;;;00861053946524;01053946524;;20171209114854;4;;1\
//;0;;;;;;;;10;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;1;;0;;;;;;;;;;as1.bj.chi;;;;000;<>;254;0;;;1000333610;0;;;;;;;;1;;;;\
//NEWCENTREXAS2017120911481042.dat;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;";
//	sftp_handle = libssh2_sftp_open(sftp_session, sftppath,
//
//			LIBSSH2_FXF_WRITE | LIBSSH2_FXF_CREAT | LIBSSH2_FXF_TRUNC,
//			LIBSSH2_SFTP_S_IRUSR | LIBSSH2_SFTP_S_IWUSR |
//			LIBSSH2_SFTP_S_IRGRP | LIBSSH2_SFTP_S_IROTH);
//
//	rc = libssh2_sftp_write(sftp_handle, xdr, sizeof(*xdr)*strlen(xdr));
//
//	libssh2_sftp_close(sftp_handle);
//
//	libssh2_sftp_shutdown(sftp_session);
//
	return TRUE;
}