#pragma once
#include "MyButton.h"
#include "stdafx.h"
#include "predatasheetdlg\DialogUserInfo.h"
#include "predatasheetdlg\DialogUserAttr.h"
#include "predatasheetdlg\DialogUserGroup.h"
#include "predatasheetdlg\DialogUserSprom.h"
#include "MFCApplication1.h"
#include "ContentPage2.h"
#include "PreDataDlg.h"

// CPreDataDlg
class cuserinfo
{
public:
	LONGLONG acctid;
	LONGLONG servid;
	LONGLONG custid;
	int region_code;
	CString imsi;
	CString user_number;
	DATE uservaliddate;
	DATE userexpioredate;
	int usercycle;
	int usersts;
	int mgntsts;
	int acctsts;
	int opersts;
	DATE stsvaliddate;
	DATE stsexpiredate;
	int cycletype;
	int cyclelength;
	int cycleproperty;
	int cycleendday;
	DATE cyclevaliddate;
	DATE cycleexpiredate;
	BOOL setdata();
	BOOL getdata();
};



class CPreDataData
{
public:
	cuserinfo userdata;
	BOOL setDialogDatafromxml(XMLElement* xmlconfig);
	int abd;

};




class CPreDataDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CPreDataDlg)

public:
	//CPreDataData data;
	CPreDataDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPreDataDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPreDataDlg();
	virtual ~CPreDataDlg();
	XMLElement* CreateDiaLog(XMLElement* xmlconfig, CPreDataData* data, int buttonseq);
	BOOL setDialogData(CPreDataData* _data);
	afx_msg LRESULT   OnQuerySiblings(WPARAM wParam, LPARAM lParam);
	void analysexml();
	XMLElement* generatexml(CPreDataData* data, int buttonseq);

	BOOL getDialogData(XMLElement* xmlconfig, CPreDataData* dialogdata);
protected:
	DECLARE_MESSAGE_MAP()
	
};

typedef CMyButton<CPreDataData, CPreDataDlg>  PreDataBut;

// CPreDataDlg 消息处理程序

BOOL CPreDataData::setDialogDatafromxml(XMLElement* xmlconfig)
{
	XMLElement* userinfo = xmlconfig->FirstChildElement("userinfo");
	userdata.acctid = atoll((userinfo->FirstChildElement("acctid"))->GetText());
	userdata.servid = atoll((userinfo->FirstChildElement("servid"))->GetText());
	userdata.custid = atoll((userinfo->FirstChildElement("custid"))->GetText());
	userdata.region_code = atoi((userinfo->FirstChildElement("region_code"))->GetText());
	userdata.imsi = (userinfo->FirstChildElement("imsi"))->GetText();
	userdata.user_number = (userinfo->FirstChildElement("user_number"))->GetText();

	return TRUE;
}

IMPLEMENT_DYNAMIC(CPreDataDlg, CPropertySheet)

CPreDataDlg::CPreDataDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

BOOL CPreDataDlg::getDialogData(XMLElement* xmlconfig, CPreDataData* dialogdata)
{
	AfxMessageBox(_T("here"));

	return TRUE;
}


BOOL CPreDataDlg::setDialogData(CPreDataData* _data)
{
	_data->userdata.acctid = ((CDialogUserInfo*)GetPage(0))->m_nAcctid;
	_data->userdata.servid = ((CDialogUserInfo*)GetPage(0))->m_nServid;
	_data->userdata.custid = ((CDialogUserInfo*)GetPage(0))->m_nCustid;
	_data->userdata.region_code = ((CDialogUserInfo*)GetPage(0))->m_nRegioncode;
	_data->userdata.imsi = ((CDialogUserInfo*)GetPage(0))->m_strImsi;
	_data->userdata.user_number = ((CDialogUserInfo*)GetPage(0))->m_strMsisdn;

	return TRUE;
}


XMLElement* CPreDataDlg::CreateDiaLog(XMLElement* xmlconfig, CPreDataData* data, int buttonseq)
{
	//AfxMessageBox(  dialogdata->userdata.acctid);


	CDialogUserInfo *page1 = (xmlconfig == NULL ? new CDialogUserInfo() : new CDialogUserInfo(xmlconfig));
	CDialogUserAttr page2;
	CDialogUserGroup page3;
	CDialogUserSprom page4;
	AddPage(page1);
	AddPage(&page2);
	AddPage(&page3);
	AddPage(&page4);


	if (IDOK == DoModal())
	{
		setDialogData(data);
	}

	xmlconfig = generatexml(data, buttonseq);

	/*if (xmlconfig == NULL)
	xmlconfig = generatexml(data,buttonseq);
	else
	xmlconfig = modifyxml(data, buttonseq);*/
	return xmlconfig;
}



CPreDataDlg::CPreDataDlg()
{

}

CPreDataDlg::CPreDataDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CPreDataDlg::~CPreDataDlg()
{
}

afx_msg LRESULT  CPreDataDlg::OnQuerySiblings(WPARAM wParam, LPARAM lParam)
{
	//AfxMessageBox(_T("CPreDataDlg::OnQuerySiblings"));
	GetPage(2)->SendMessage(PSM_QUERYSIBLINGS, wParam, lParam);
	return 0;
}


BEGIN_MESSAGE_MAP(CPreDataDlg, CPropertySheet)
	ON_MESSAGE(PSM_QUERYSIBLINGS, &CPreDataDlg::OnQuerySiblings)
END_MESSAGE_MAP()


void CPreDataDlg::analysexml()
{

}

XMLElement* CPreDataDlg::generatexml(CPreDataData* data, int buttonseq)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	XMLElement* xmlconfigtmp = doc->NewElement("flow");
	XMLElement* flow_name = doc->NewElement("flow_name");
	XMLElement* flow_seq = doc->NewElement("flow_seq");
	XMLElement* node_config = doc->NewElement("node_config");
	XMLElement* userinfo = doc->NewElement("userinfo");
	XMLElement* acctid = doc->NewElement("acctid");
	XMLElement* servid = doc->NewElement("servid");
	XMLElement* custid = doc->NewElement("custid");
	XMLElement* region_code = doc->NewElement("region_code");
	XMLElement* imsi = doc->NewElement("imsi");
	XMLElement* user_number = doc->NewElement("user_number");

	doc->InsertEndChild(xmlconfigtmp);
	xmlconfigtmp->InsertEndChild(flow_name);
	xmlconfigtmp->InsertEndChild(flow_seq);
	xmlconfigtmp->InsertEndChild(node_config);
	node_config->InsertEndChild(userinfo);
	userinfo->InsertEndChild(acctid);
	userinfo->InsertEndChild(servid);
	userinfo->InsertEndChild(custid);
	userinfo->InsertEndChild(region_code);
	userinfo->InsertEndChild(imsi);
	userinfo->InsertEndChild(user_number);

	XMLText* flow_name_text = doc->NewText("PREDATA");
	flow_name->InsertEndChild(flow_name_text);
	XMLText* flow_seq_text = doc->NewText(buttonseq);
	flow_seq->InsertEndChild(flow_seq_text);
	XMLText* acctid_text = doc->NewText(data->userdata.acctid);
	acctid->InsertEndChild(acctid_text);
	XMLText* servid_text = doc->NewText(data->userdata.servid);
	servid->InsertEndChild(servid_text);
	XMLText* custid_text = doc->NewText(data->userdata.custid);
	custid->InsertEndChild(custid_text);
	XMLText* region_code_text = doc->NewText(data->userdata.region_code);
	region_code->InsertEndChild(region_code_text);
	XMLText* imsi_text = doc->NewText(data->userdata.imsi);
	imsi->InsertEndChild(imsi_text);
	XMLText* user_number_text = doc->NewText(data->userdata.user_number);
	user_number->InsertEndChild(user_number_text);

	XMLPrinter printer;
	doc->Print(&printer);
	CStringA abc = printer.CStr();
	return xmlconfigtmp;
}


BOOL PreDataDlgExec(XMLElement* xmlConfig)
{
	CDialogUserInfo::Exec(xmlConfig);
	return 0;
}

