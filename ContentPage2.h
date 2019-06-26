#pragma once



// CContentPage2 �Ի���

class CContentPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CContentPage2)

public:
	CContentPage2();   // ��׼���캯��
	virtual ~CContentPage2();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ContentDlg2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void createnewdialog(UINT nID);
	int CreateBut( int seq,int buttype,BOOL isbatch=FALSE);
	CString m_casexml;
	CString m_caseconfig;
	void analysexml();
	vector<func_struct> func_assemble;  //�����洢func_define�����ݣ���contentview�е�butattr��������
	map<int, XMLElement*> node_assemble;//�����洢xml������������
	void createbatchbutton();
	void DeleteAllItems();
	void generatexml();
	void CreateNewXml();

	void getPage2Xml();

	void CContentPage2::insertEleToCaseXml(XMLElement *in, XMLNode *out, tinyxml2::XMLDocument* doc);

};
