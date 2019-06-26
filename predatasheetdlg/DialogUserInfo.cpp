// DialogUserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "..\stdafx.h"
#include "..\MFCApplication1.h"
#include "DialogUserInfo.h"
#include "afxdialogex.h"

// CDialogUserInfo 对话框

IMPLEMENT_DYNAMIC(CDialogUserInfo, CPropertyPage)

CDialogUserInfo::CDialogUserInfo()
	: CPropertyPage(IDD_PROPPAGE_CUSERINFO)
	, m_nAcctid(0)
	, m_nServid(0)
	, m_strImsi(_T(""))
	, m_strMsisdn(_T(""))
	, m_nUserCycle(0)
	, m_nUsersts(0)
	, m_nMgntsts(0)
	, m_nAcctsts(0)
	, m_nOperSts(0)
	, m_nCycletype(0)
	, m_nCyclelength(0)
	, m_nCycleProperty(0)
	, m_nCycleendday(0)
	, m_nCustid(0)
	, m_nRegioncode(0)
	, m_dUserValid(0)
	, m_tUserValid(0)
	, m_dUserExpire(0)
	, m_tUserExpire(0)
	, m_dCycleValid(0)
	, m_tCycleValid(0)
	, m_dCycleExpire(0)
	, m_tCycleExpire(0)
	, m_dBillCycleValid(0)
	, m_tBillCycleValid(0)
	, m_dBillCycleExpire(0)
	, m_tBillCycleExpire(0)
{
	
}


CDialogUserInfo::CDialogUserInfo(XMLElement* xmlconfig):
	CPropertyPage(IDD_PROPPAGE_CUSERINFO)
{
	if(xmlconfig!=NULL)
		analysexml(xmlconfig);
}

CDialogUserInfo::~CDialogUserInfo()
{


}

void CDialogUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ACCTID, m_nAcctid);
	DDX_Text(pDX, IDC_EDIT_SERVID, m_nServid);
	DDX_Text(pDX, IDC_EDIT_IMSI, m_strImsi);
	DDX_Text(pDX, IDC_EDIT_MSISDN, m_strMsisdn);
	DDX_Text(pDX, IDC_EDIT_USERCYCLE, m_nUserCycle);
	DDX_Text(pDX, IDC_EDIT_USERSTS, m_nUsersts);
	DDX_Text(pDX, IDC_EDIT_MGNTSTS, m_nMgntsts);
	DDX_Text(pDX, IDC_EDIT_ACCTSTS, m_nAcctsts);
	DDX_Text(pDX, IDC_EDIT_OPERSTS, m_nOperSts);
	DDX_Text(pDX, IDC_EDIT_CYCLETYPE, m_nCycletype);
	DDX_Text(pDX, IDC_EDIT_CYCLELENGTH, m_nCyclelength);
	DDX_Text(pDX, IDC_EDIT_CYCLEPROPERTY, m_nCycleProperty);
	DDX_Text(pDX, IDC_EDIT_CYCLEENDDAY, m_nCycleendday);
	DDX_Text(pDX, IDC_EDIT_CUSTID, m_nCustid);
	DDX_Text(pDX, IDC_EDIT_REGIONCODE, m_nRegioncode);
	DDX_DateTimeCtrl(pDX, IDC_DATE_USERVALID, m_dUserValid);
	DDX_DateTimeCtrl(pDX, IDC_TIME_USERVALID, m_tUserValid);
	DDX_DateTimeCtrl(pDX, IDC_DATE_USEREXPIRE, m_dUserExpire);
	DDX_DateTimeCtrl(pDX, IDC_TIME_USEREXPIRE, m_tUserExpire);
	DDX_DateTimeCtrl(pDX, IDC_DATE_CYCLEVALID, m_dCycleValid);
	DDX_DateTimeCtrl(pDX, IDC_TIME_CYCLEVALID, m_tCycleValid);
	DDX_DateTimeCtrl(pDX, IDC_DATE_CYCLEEXPIRE, m_dCycleExpire);
	DDX_DateTimeCtrl(pDX, IDC_TIME_CYCLEEXPIRE, m_tCycleExpire);
	DDX_DateTimeCtrl(pDX, IDC_DATE_BILLCYCLEVALID, m_dBillCycleValid);
	DDX_DateTimeCtrl(pDX, IDC_TIME_BILLCYCLEVALID, m_tBillCycleValid);
	DDX_DateTimeCtrl(pDX, IDC_DATE_BILLCYCLEEXPIRE, m_dBillCycleExpire);
	DDX_DateTimeCtrl(pDX, IDC_TIME_BILLCYCLEEXPIRE, m_tBillCycleExpire);
}


BEGIN_MESSAGE_MAP(CDialogUserInfo, CPropertyPage)
END_MESSAGE_MAP()


// CDialogUserInfo 消息处理程序


BOOL CDialogUserInfo::analysexml(XMLElement* xmlconfig)
{
	XMLElement* userinfo = (xmlconfig->FirstChildElement("node_config"))->FirstChildElement("userinfo");
	m_nAcctid = atoll((userinfo->FirstChildElement("acctid"))->GetText());
	m_nServid = atoll((userinfo->FirstChildElement("servid"))->GetText());
	m_nCustid = atoll((userinfo->FirstChildElement("custid"))->GetText());
	m_strImsi = (userinfo->FirstChildElement("imsi"))->GetText();
	m_strMsisdn = (userinfo->FirstChildElement("user_number"))->GetText();
	return TRUE;
}

BOOL CDialogUserInfo::Exec(XMLElement* xmlConfig)
{
	CString strSQL;
	CString servid, user_number, imsi,acctid,custid;
	servid = getValueFromXml("servid", xmlConfig);
	user_number = getValueFromXml("user_number", xmlConfig);
	imsi = getValueFromXml("imsi", xmlConfig);
	acctid = getValueFromXml("acctid", xmlConfig);
	custid = getValueFromXml("custid", xmlConfig);



	strSQL.Format(_T("insert into bjzg.i_user_0101 (SERV_ID, MSISDN, IMSI, ACCT_ID, CUST_ID, USER_STS, USER_TYPE, BRAND, \
		PROD_FLAG, BILL_TYPE, SUB_STATUS, ACCT_REGION_CODE, REGION_CODE, COUNTY_CODE, CREATE_DATE, BEGIN_DATE, VALID_DATE, \
		EXPIRE_DATE, OPER_TYPE, SID, SO_NBR, REMARK, USER_PROPERTY, SPEC_FLAG, BILL_CYCLE, AOC_FLAG, CTRL_FUNC, CYCLE_DAY, \
		NEXT_CYCLE_DAY, FIRST_USE_TIME, MAIN_SERV_ID)\
		values(%s, '%s', '%s', %s, %s, 1, 1, 1, 0, 1, 0, 100, 101, 1000, \
		to_date('16-07-1997', 'dd-mm-yyyy'), to_date('16-07-1997', 'dd-mm-yyyy'), to_date('16-07-1997', 'dd-mm-yyyy'), \
		to_date('01-01-2099', 'dd-mm-yyyy'), 1, 3964320, 0, null, 0, 0, 0, 0, 0, 0, 0, \
		to_date('01-01-2099', 'dd-mm-yyyy'), 0);"), servid, user_number,imsi, acctid, custid);

	CCUserInfoRecSet* m_cuserinfo = new CCUserInfoRecSet();

	try
	{
		(m_cuserinfo->m_pDatabase)->ExecuteSQL(strSQL);
	}
	catch (CDBException* pe)
	{
		// The error code is in pe->m_nRetCode
		pe->ReportError();
		pe->Delete();
	}



	return TRUE;
}

const char* CDialogUserInfo::getValueFromXml(const char* nodename,XMLElement* xmlConfig)
{
	tinyxml2::XMLDocument* doc = new  tinyxml2::XMLDocument();
	XMLNode *copy = xmlConfig->ShallowClone(doc);
	doc->InsertEndChild(copy);
	XMLPrinter printer;
	doc->Print(&printer);
	CString abc(printer.CStr());

	XMLElement* node_config = xmlConfig->FirstChildElement("node_config");

	XMLElement* userinfo = (xmlConfig->FirstChildElement("node_config"))->FirstChildElement("userinfo");
	return (userinfo->FirstChildElement(nodename)->GetText());

}
