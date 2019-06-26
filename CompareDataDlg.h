#pragma once
#include "afxwin.h"
#include "GridCtrl_src\GridCtrl.h"
#include "stdafx.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "MyButton.h"
#include "afxcmn.h"


class CCompareDatadata
{
public:
	CString stdxdr;
	BOOL CCompareDatadata::setDialogDatafromxml(XMLElement* xmlconfig);

};

// CCompareDataDlg 对话框
BOOL CCompareDatadata::setDialogDatafromxml(XMLElement* xmlconfig)
{
	AfxMessageBox(_T("设置数据"));
	return TRUE;
}


class CCompareDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCompareDataDlg)

public:
	CCompareDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCompareDataDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_COMPAREDATA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;

	virtual BOOL OnInitDialog();
	void GridCtrlInit();

	XMLElement* CreateDiaLog(XMLElement* xmlconfig, CCompareDatadata* data, int buttonseq);
	BOOL setDialogData(CCompareDatadata* _data);
	void analysexml(XMLElement* xmlconfig);


	CRichEditCtrl m_stdXdr;
	CString m_stdXdrValue;
	CStringA judgexdrtype();
	CString analyseeditvalue(int col, int row, BOOL isUpdata = FALSE);
	XMLElement* generatexml(CCompareDatadata* data, int buttonseq);
	afx_msg void OnEnChangeRichedit21();

	static BOOL Exec(XMLElement* xmlConfig);

};

typedef CMyButton<CCompareDatadata, CCompareDataDlg>  CompareDataBut;


BOOL CCompareDataDlg::setDialogData(CCompareDatadata* _data)
{
	_data->stdxdr = m_stdXdrValue;
	return TRUE;
}

XMLElement* CCompareDataDlg::CreateDiaLog(XMLElement* xmlconfig, CCompareDatadata* data, int buttonseq)
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

IMPLEMENT_DYNAMIC(CCompareDataDlg, CDialogEx)

CCompareDataDlg::CCompareDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDC_COMPAREDATA, pParent)
	, m_stdXdrValue(_T(""))
{

}

CCompareDataDlg::~CCompareDataDlg()
{
}

void CCompareDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_COMPAREGRID, m_pGrid);
	DDX_Control(pDX, IDC_RICHEDIT21, m_stdXdr);
	DDX_Text(pDX, IDC_RICHEDIT21, m_stdXdrValue);
}


BEGIN_MESSAGE_MAP(CCompareDataDlg, CDialogEx)
	ON_EN_CHANGE(IDC_RICHEDIT21, &CCompareDataDlg::OnEnChangeRichedit21)
END_MESSAGE_MAP()


// CCompareDataDlg 消息处理程序


BOOL CCompareDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GridCtrlInit();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCompareDataDlg::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	m_pGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//黄色背景
	CStringA xdrtype;
	if (m_stdXdrValue == _T(""))
		xdrtype = "dr_cs";
	else
		xdrtype = judgexdrtype();

	int	rownum = xdrdefinemap[xdrtype].size();
	//else
	//	linenum = judgexdrtype();

	m_pGrid.SetRowCount(rownum + 1);
	CString rowCountNum = m_stdXdrValue;
	int rowCount = rowCountNum.Replace(_T("\n"), _T("\t"));
	if (rowCount >= 1)
		m_pGrid.SetColumnCount(rowCount + 2);
	else if (m_stdXdrValue.GetLength()>100)
		m_pGrid.SetColumnCount(2);
	else
		m_pGrid.SetColumnCount(1);

	m_pGrid.SetFixedRowCount(1);//表头为一行
	m_pGrid.SetFixedColumnCount(1);//表头为一列
	for (int row = 0; row < m_pGrid.GetRowCount(); row++)
	{
		for (int col = 0; col < m_pGrid.GetColumnCount(); col++)
		{
			//设置表格显示属性
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			m_pGrid.SetRowHeight(row, 25);//设置各行高
			if (col == 0)
				m_pGrid.SetColumnWidth(0, 128);//设置0列宽
			else
				m_pGrid.SetColumnWidth(col, 64);//设置各列宽
			if (row == 0 && col == 0)//第(0，0)格
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(""), col);
			}
			else if (row < 1)//设置0行表头显示
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" %d "), col);
			}
			else if (col < 1)//设置0列表头显示
			{
				if (col == 0 && row == 1)
					Item.strText.Format(_T("TRADEMARK"));
				else if (row < m_pGrid.GetRowCount())
				{
					Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					Item.strText.Format((CString)xdrdefinemap[xdrtype][row - 1].xdr_field_name);
				}
			}
			else
			{
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
				Item.strText.Format(analyseeditvalue(col, row), 2);
			}
			m_pGrid.SetItem(&Item);
		}
	}
}





void CCompareDataDlg::analysexml(XMLElement* xmlconfig)
{
	XMLElement* node_config = xmlconfig->FirstChildElement("node_config");
	m_stdXdrValue = (node_config->FirstChildElement("stdxdr"))->GetText();
}


CStringA CCompareDataDlg::judgexdrtype()
{
	int index = m_stdXdrValue.Find(_T("\n"));
	CString strResult = m_stdXdrValue.Left(index);
	int num = strResult.Replace(';', ',');


	map<CStringA, vector<xdrdefineattr>>::iterator it;
	it = xdrdefinemap.begin();
	while (it != xdrdefinemap.end())
	{
		if (it->second.size() == num || it->second.size() == num + 2)
		{
			return it->first;
		}

		it++;
	}
	return "dr_cs";
}


CString CCompareDataDlg::analyseeditvalue(int row, int col, BOOL isUpdata)
{
	CString tmpeditvalue;
	if (isUpdata == TRUE)
		m_stdXdr.GetWindowTextW(tmpeditvalue);
	else
		tmpeditvalue = m_stdXdrValue;
	int length = tmpeditvalue.GetLength();
	int startIndex = 0;
	int endIndex = 0;
	CString strResult;
	for (int i = 1; i <= row; i++)
	{
		endIndex = (tmpeditvalue.Find(_T("\n")) == -1) ? tmpeditvalue.GetLength() : tmpeditvalue.Find(_T("\n"));
		int lineEndIndex = endIndex;
		CString tmptmpeditvalue = tmpeditvalue.Mid(startIndex, endIndex);
		int tmpIndex = 0;
		for (int j = 1; j <= col; j++)
		{
			tmpIndex = tmptmpeditvalue.Find(_T(";"));
			strResult = tmptmpeditvalue.Mid(startIndex, tmpIndex);
			tmptmpeditvalue = tmptmpeditvalue.Right(endIndex -= (tmpIndex + 1));

		}
		tmpeditvalue = tmpeditvalue.Right(length -= (lineEndIndex + 1));
	}
	return strResult;
}


void CCompareDataDlg::OnEnChangeRichedit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CStringA xdrtype;
	m_stdXdr.GetWindowTextW(m_stdXdrValue);
	if (m_stdXdrValue == _T(""))
		xdrtype = "dr_cs";
	else
		xdrtype = judgexdrtype();

	int	rownum = xdrdefinemap[xdrtype].size();

	m_pGrid.SetRowCount(rownum + 1);
	CString rowCountNum = m_stdXdrValue;
	int colCount = rowCountNum.Replace(_T("\n"), _T("\t"));
	if (colCount >= 1)
		m_pGrid.SetColumnCount(colCount + 2);
	else if (m_stdXdrValue.GetLength()>100)
		m_pGrid.SetColumnCount(2);
	else
		m_pGrid.SetColumnCount(1);

	m_pGrid.SetFixedRowCount(1);//表头为一行
	m_pGrid.SetFixedColumnCount(1);//表头为一列
	for (int row = 0; row < m_pGrid.GetRowCount(); row++)
	{
		for (int col = 0; col < m_pGrid.GetColumnCount(); col++)
		{
			//设置表格显示属性
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			m_pGrid.SetRowHeight(row, 25);//设置各行高
			if (col == 0)
				m_pGrid.SetColumnWidth(0, 128);//设置0列宽
			else
				m_pGrid.SetColumnWidth(col, 64);//设置各列宽
			if (row == 0 && col == 0)//第(0，0)格
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(""), col);
			}
			else if (row < 1)//设置0行表头显示
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" %d "), col);
			}
			else if (col < 1)//设置0列表头显示
			{
				if (row < m_pGrid.GetRowCount())
				{
					Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					Item.strText.Format((CString)xdrdefinemap[xdrtype][row - 1].xdr_field_name);
				}
			}
			else
			{
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
				Item.strText.Format(analyseeditvalue(col, row, TRUE), 2);
			}
			m_pGrid.SetItem(&Item);
		}
	}

	m_pGrid.Refresh();
}



XMLElement* CCompareDataDlg::generatexml(CCompareDatadata* data, int buttonseq)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	XMLElement* xmlconfigtmp = doc->NewElement("flow");
	XMLElement* flow_name = doc->NewElement("flow_name");
	XMLElement* flow_seq = doc->NewElement("flow_seq");
	XMLElement* node_config = doc->NewElement("node_config");
	XMLElement* stdxdr = doc->NewElement("stdxdr");

	doc->InsertEndChild(xmlconfigtmp);
	xmlconfigtmp->InsertEndChild(flow_name);
	xmlconfigtmp->InsertEndChild(flow_seq);
	xmlconfigtmp->InsertEndChild(node_config);
	node_config->InsertEndChild(stdxdr);


	XMLText* flow_name_text = doc->NewText("COMPAREDATA");
	flow_name->InsertEndChild(flow_name_text);
	XMLText* flow_seq_text = doc->NewText(buttonseq);
	flow_seq->InsertEndChild(flow_seq_text);
	XMLText* stdxdr_text = doc->NewText(data->stdxdr);
	stdxdr->InsertEndChild(stdxdr_text);

	return xmlconfigtmp;

}



BOOL CCompareDataDlg::Exec(XMLElement* xmlConfig)
{

	return TRUE;
}