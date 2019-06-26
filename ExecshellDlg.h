#pragma once

#include "stdafx.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "MyButton.h"
#include "afxcmn.h"
#include "defaultxml.h"
#include "MainFrm.h"
#include "ChildFrm.h"

// CExecshellDlg 对话框



class CExecshellDlgData
{
public:
	int abc;
	BOOL checkshel;
	BOOL checkdefault;
	CString busitype;
	CString flowtype;
	CString configxml;

	BOOL setDialogDatafromxml(XMLElement* xmlconfig);

};

BOOL CExecshellDlgData::setDialogDatafromxml(XMLElement* xmlconfig)
{
	AfxMessageBox(_T("设置数据"));
	return TRUE;
}


class CExecshellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExecshellDlg)

public:
	CExecshellDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExecshellDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXECSHELL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_busitype;
	CComboBox m_flowtype;
	CButton m_checkshell;
	CButton m_checkdefault;
	virtual BOOL OnInitDialog();
	XMLElement* CreateDiaLog(XMLElement* xmlconfig, CExecshellDlgData* data, int buttonseq);
	BOOL setDialogData(CExecshellDlgData* _data);
	CRichEditCtrl m_xmledit;
	afx_msg void OnBnClickedOk();
	DefaultXmlRecSet *m_defaultxml;
	afx_msg void OnCbnselchangeCombo1();
	afx_msg void OnCbnselchangeCombo2();
	void analysexml(XMLElement* xmlconfig);
	BOOL m_checkshellvalue;
	BOOL m_checkdefaultvalue;
	CString m_flowtypevalue;
	CString m_busitypevalue;
	CString m_xmleditvalue;
	XMLElement* generatexml(CExecshellDlgData* data, int buttonseq);
	static BOOL Exec(XMLElement* xmlConfig);

};



typedef CMyButton<CExecshellDlgData, CExecshellDlg>  ExecshellDlgBut;


IMPLEMENT_DYNAMIC(CExecshellDlg, CDialogEx)

CExecshellDlg::CExecshellDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EXECSHELL_DIALOG, pParent)
	, m_checkshellvalue(FALSE)
	, m_checkdefaultvalue(FALSE)
	, m_flowtypevalue(_T(""))
	, m_busitypevalue(_T(""))
	, m_xmleditvalue(_T(""))
{
	m_defaultxml = new DefaultXmlRecSet();
}

CExecshellDlg::~CExecshellDlg()
{
}

void CExecshellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_busitype); //业务类型，gsm ggprs sms
	DDX_Control(pDX, IDC_COMBO1, m_flowtype); //模块类型 decode rpling rating
	DDX_Control(pDX, IDC_CHECK1, m_checkshell);
	DDX_Control(pDX, IDC_CHECK2, m_checkdefault);
	DDX_Control(pDX, IDC_RICHEDIT21, m_xmledit);
	DDX_Check(pDX, IDC_CHECK1, m_checkshellvalue);
	DDX_Check(pDX, IDC_CHECK2, m_checkdefaultvalue);
	DDX_CBString(pDX, IDC_COMBO2, m_flowtypevalue); //业务类型，gsm ggprs sms
	DDX_CBString(pDX, IDC_COMBO1, m_busitypevalue); //模块类型 decode rpling rating
	DDX_Text(pDX, IDC_RICHEDIT21, m_xmleditvalue);
}


BEGIN_MESSAGE_MAP(CExecshellDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CExecshellDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CExecshellDlg::OnCbnselchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CExecshellDlg::OnCbnselchangeCombo1)
END_MESSAGE_MAP()

XMLElement* CExecshellDlg::CreateDiaLog(XMLElement* xmlconfig, CExecshellDlgData* data, int buttonseq)
{
	if (xmlconfig != NULL)
		analysexml(xmlconfig);

	if (IDOK == DoModal())
	{
		setDialogData(data);
	}

	xmlconfig = generatexml(data, buttonseq);

	return xmlconfig;

}


BOOL CExecshellDlg::setDialogData(CExecshellDlgData* _data)
{
	_data->checkshel = m_checkshellvalue;
	_data->checkdefault = m_checkdefaultvalue;
	_data->busitype = m_busitypevalue;
	_data->flowtype = m_flowtypevalue;
	_data->configxml = m_xmleditvalue;

	return TRUE;
}
// CExecshellDlg 消息处理程序

BOOL CExecshellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_busitype.AddString(_T("GSM"));
	m_busitype.AddString(_T("GPRS"));
	m_busitype.AddString(_T("GGPRS"));
	m_busitype.AddString(_T("SMS"));
	m_busitype.AddString(_T("ENTSMS"));
	m_busitype.AddString(_T("ISMG"));

	m_flowtype.AddString(_T("decode"));
	m_flowtype.AddString(_T("rpling"));
	m_flowtype.AddString(_T("rating"));
	m_flowtype.AddString(_T("dispatch"));
	m_flowtype.AddString(_T("dataloader"));
	m_flowtype.AddString(_T("chkdup"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CExecshellDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_checkdefault.GetCheck())
	{
		CString m_strbusitype;
		CString m_strflowtype;
		CString m_strdefaultxml;
		m_busitype.GetWindowText(m_strbusitype);
		m_flowtype.GetWindowText(m_strflowtype);
		m_xmledit.GetWindowText(m_strdefaultxml);
		CString strSQL = _T("select * from defaultxml where busitype=\'")\
			+ m_strbusitype + _T("\' and flowtype=\'") + m_strflowtype + _T("\';");
		if (m_defaultxml->IsOpen())
			m_defaultxml->Close();
		BOOL a = m_defaultxml->Open(CRecordset::snapshot, strSQL);
		long b = m_defaultxml->GetRecordCount();
		if (b == 0)
		{
			int abc = m_defaultxml->m_nFields;
			m_defaultxml->AddNew();
			m_defaultxml->busitype = m_strbusitype;
			m_defaultxml->flowtype = (CStringA)m_strflowtype;
			m_defaultxml->defaultxml = (CStringA)m_strdefaultxml;
			m_defaultxml->Update();
			//insert
		}
		else
		{
			m_defaultxml->Edit();
			m_defaultxml->defaultxml = m_strdefaultxml;
			m_defaultxml->Update();
			//update
		}
	}
	CDialogEx::OnOK();
}



void CExecshellDlg::OnCbnselchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_flowtype.GetCurSel() != CB_ERR)
	{
		if (m_busitype.GetCurSel() != CB_ERR)
		{
			if (m_defaultxml->IsOpen())
				m_defaultxml->Close();
			CString strSQL = _T("select BUSITYPE,FLOWTYPE,DEFAULTXML from defaultxml where busitype=\'");
			CString m_strbusitype;
			CString m_strflowtype;
			int num1 = m_busitype.GetCurSel();
			m_busitype.GetLBText(num1, m_strbusitype);
			int num2 = m_flowtype.GetCurSel();
			m_flowtype.GetLBText(num2, m_strflowtype);

			strSQL = strSQL + m_strbusitype + _T("\' and flowtype=\'") + m_strflowtype + _T("\';");
			BOOL a = m_defaultxml->Open(CRecordset::snapshot, strSQL);
			if (!a)
				AfxMessageBox(_T("查询BSXDRDEFINE失败！！"));
			if (!m_defaultxml->IsEOF()) {
				m_defaultxml->MoveFirst();
			}
			long b = m_defaultxml->GetRecordCount();
			if (b == 0)
			{
				m_xmledit.SetWindowText(_T(""));
				return;
			}
			CString m_strdefaultxml;
			m_defaultxml->GetFieldValue(_T("DEFAULTXML"), m_strdefaultxml);
			m_xmledit.SetWindowText(m_strdefaultxml);
			}
	}
}


void CExecshellDlg::OnCbnselchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_flowtype.GetCurSel() != CB_ERR)
	{
		if (m_busitype.GetCurSel() != CB_ERR)
		{
			if (m_defaultxml->IsOpen())
				m_defaultxml->Close();
			CString strSQL = _T("select BUSITYPE,FLOWTYPE,DEFAULTXML from defaultxml where busitype=\'");
			CString m_strbusitype;
			CString m_strflowtype;
			int num1 = m_busitype.GetCurSel();
			m_busitype.GetLBText(num1, m_strbusitype);
			int num2 = m_flowtype.GetCurSel();
			m_flowtype.GetLBText(num2, m_strflowtype);

			strSQL = strSQL + m_strbusitype + _T("\' and flowtype=\'") + m_strflowtype + _T("\';");
			BOOL a = m_defaultxml->Open(CRecordset::snapshot, strSQL);
			if (!a)
				AfxMessageBox(_T("查询BSXDRDEFINE失败！！"));
			if (!m_defaultxml->IsEOF()) {
				m_defaultxml->MoveFirst();
			}
			long b = m_defaultxml->GetRecordCount();
			if (b == 0)
			{
				m_xmledit.SetWindowText(_T(""));
					return;
			}
			CString m_strdefaultxml;
			m_defaultxml->GetFieldValue(_T("DEFAULTXML"), m_strdefaultxml);
			m_xmledit.SetWindowText(m_strdefaultxml);
		}
	}
}

void CExecshellDlg::analysexml(XMLElement* xmlconfig)
{
	XMLElement* node_config = xmlconfig->FirstChildElement("node_config");
	m_checkshellvalue = ((atoi((node_config->FirstChildElement("checkshel"))->GetText())==1) ? TRUE : FALSE);
	m_checkdefaultvalue = ((atoi((node_config->FirstChildElement("checkdefault"))->GetText()) == 1) ? TRUE : FALSE);
	m_flowtypevalue = node_config->FirstChildElement("flowtype")->GetText();
	m_busitypevalue = node_config->FirstChildElement("busitype")->GetText();

	CMainFrame * pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame* pChild = (CChildFrame*)pMainFrame->GetActiveFrame();

	CContentView *rightview = pChild->rightview;

	m_xmleditvalue = ((CContentPage2*)rightview->pSheet->GetPage(1))->m_caseconfig;


	/*DDX_Check(pDX, IDC_CHECK1, m_checkshellvalue);
	DDX_Check(pDX, IDC_CHECK2, m_checkdefaultvalue);
	DDX_CBString(pDX, IDC_COMBO2, m_flowtypevalue);
	DDX_CBString(pDX, IDC_COMBO1, m_busitypevalue);*/
}



XMLElement* CExecshellDlg::generatexml(CExecshellDlgData* data, int buttonseq)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	XMLElement* xmlconfigtmp = doc->NewElement("flow");
	XMLElement* flow_name = doc->NewElement("flow_name");
	XMLElement* flow_seq = doc->NewElement("flow_seq");
	XMLElement* node_config = doc->NewElement("node_config");
	XMLElement* checkshel = doc->NewElement("checkshel");
	XMLElement* checkdefault = doc->NewElement("checkdefault");
	XMLElement* busitype = doc->NewElement("busitype");
	XMLElement* flowtype = doc->NewElement("flowtype");

	doc->InsertEndChild(xmlconfigtmp);
	xmlconfigtmp->InsertEndChild(flow_name);
	xmlconfigtmp->InsertEndChild(flow_seq);
	xmlconfigtmp->InsertEndChild(node_config);
	node_config->InsertEndChild(checkshel);
	node_config->InsertEndChild(checkdefault);
	node_config->InsertEndChild(busitype);
	node_config->InsertEndChild(flowtype);


	XMLText* flow_name_text = doc->NewText("EXECSHELL");
	flow_name->InsertEndChild(flow_name_text);
	XMLText* flow_seq_text = doc->NewText(buttonseq);
	flow_seq->InsertEndChild(flow_seq_text);
	XMLText* checkshel_text = doc->NewText(data->checkshel);
	checkshel->InsertEndChild(checkshel_text);
	XMLText* checkdefault_text = doc->NewText(data->checkdefault);
	checkdefault->InsertEndChild(checkdefault_text);
	XMLText* busitype_text = doc->NewText(data->busitype);
	busitype->InsertEndChild(busitype_text);
	XMLText* flowtype_text = doc->NewText(data->flowtype);
	flowtype->InsertEndChild(flowtype_text);

	return xmlconfigtmp;
}

BOOL CExecshellDlg::Exec(XMLElement* xmlConfig)
{
	return 0;
}