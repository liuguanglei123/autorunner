#pragma once



// CContentPage2 对话框

class CContentPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CContentPage2)

public:
	CContentPage2();   // 标准构造函数
	virtual ~CContentPage2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ContentDlg2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void createnewdialog(UINT nID);
	int CreateBut( int seq,int buttype,BOOL isbatch=FALSE);
	CString m_casexml;
	CString m_caseconfig;
	void analysexml();
	vector<func_struct> func_assemble;  //用来存储func_define的数据，与contentview中的butattr变量类似
	map<int, XMLElement*> node_assemble;//用来存储xml化的配置内容
	void createbatchbutton();
	void DeleteAllItems();
	void generatexml();
	void CreateNewXml();

	void getPage2Xml();

	void CContentPage2::insertEleToCaseXml(XMLElement *in, XMLNode *out, tinyxml2::XMLDocument* doc);

};
