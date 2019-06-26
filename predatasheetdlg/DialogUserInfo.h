#pragma once
#include "atltime.h"
#include "ATLComTime.h"
#include "cuserinfo.h"

// CDialogUserInfo 对话框

class CDialogUserInfo : public CPropertyPage
{
	DECLARE_DYNAMIC(CDialogUserInfo)

public:
	CDialogUserInfo();
	CDialogUserInfo(XMLElement* xmlconfig);
	
	virtual ~CDialogUserInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_CUSERINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL analysexml(XMLElement* xmlconfig);

	DECLARE_MESSAGE_MAP()
public:
	LONGLONG m_nAcctid;
	LONGLONG m_nServid;
	CString m_strImsi;
	CString m_strMsisdn;
	int m_nUserCycle;
	int m_nUsersts;
	int m_nMgntsts;
	int m_nAcctsts;
	int m_nOperSts;
	int m_nCycletype;
	int m_nCyclelength;
	int m_nCycleProperty;
	int m_nCycleendday;
	LONGLONG m_nCustid;
	int m_nRegioncode;
	CTime m_dUserValid;
	CTime m_tUserValid;
	CTime m_dUserExpire;
	CTime m_tUserExpire;
	CTime m_dCycleValid;
	CTime m_tCycleValid;
	CTime m_dCycleExpire;
	CTime m_tCycleExpire;
	CTime m_dBillCycleValid;
	CTime m_tBillCycleValid;
	CTime m_dBillCycleExpire;
	CTime m_tBillCycleExpire;
public:
	static BOOL Exec(XMLElement* xmlConfig);
	static const char* getValueFromXml(const char* nodename,XMLElement* xmlConfig);
	
};
