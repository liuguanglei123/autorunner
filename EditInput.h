#pragma once
#include "GridCtrl_src\GridCtrl.h"
#include "stdafx.h"
#include "MyButton.h"
#include "stdafx.h"
#include "MFCApplication1.h"
#include "afxdialogex.h"
#include "afxwin.h"
#include "afxcmn.h"
// CEditInput 对话框

class CEditInputData
{
public:
	CString intputXdr;
	BOOL setDialogDatafromxml(XMLElement* xmlconfig);
};

BOOL CEditInputData::setDialogDatafromxml(XMLElement* xmlconfig)
{
	AfxMessageBox(_T("设置数据"));
	return TRUE;
}



class CEditInput : public CDialog
{
	DECLARE_DYNAMIC(CEditInput)

public:
	CEditInput(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditInput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUTEDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_pGrid;

	XMLElement* CreateDiaLog(XMLElement* xmlconfig, CEditInputData* data, int buttonseq);
	BOOL setDialogData(CEditInputData* _data);

	virtual BOOL OnInitDialog();
	void GridCtrlInit();

	afx_msg void OnEnChangeEdit1();
	CRichEditCtrl m_inputedit;
	afx_msg void OnEnChangeRichedit22();
	CString m_inputeditvalue;
	void analysexml(XMLElement* xmlconfig);
	CStringA judgexdrtype();
	CString analyseeditvalue(int col, int row,BOOL isUpdata = FALSE);
	XMLElement* generatexml(CEditInputData* data, int buttonseq);
	static BOOL Exec(XMLElement* xmlConfig);

};




typedef CMyButton<CEditInputData, CEditInput>  EditInputBut;

IMPLEMENT_DYNAMIC(CEditInput, CDialog)

CEditInput::CEditInput(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_INPUTEDIT, pParent)
	, m_inputeditvalue(_T(""))
{

}

CEditInput::~CEditInput()
{
}

void CEditInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_GridControl(pDX, IDC_GRIDCTRL, m_pGrid);
	DDX_Control(pDX, IDC_RICHEDIT22, m_inputedit);
	DDX_Text(pDX, IDC_RICHEDIT22, m_inputeditvalue);
}


BEGIN_MESSAGE_MAP(CEditInput, CDialog)
	ON_EN_CHANGE(IDC_RICHEDIT22, &CEditInput::OnEnChangeEdit1)
END_MESSAGE_MAP()

XMLElement* CEditInput::CreateDiaLog(XMLElement* xmlconfig, CEditInputData* data, int buttonseq)
{
	if (CMFCApplication1App::bsXdrDefineLoadFinish == FALSE)
	{
		AfxMessageBox(_T("bs_xdr_define正在加载，请稍后重试。"));
		return xmlconfig;
	}
	if (xmlconfig != NULL)
		analysexml(xmlconfig);

	if (IDOK == DoModal())
	{
		setDialogData(data);
	}

	xmlconfig = generatexml(data, buttonseq);
	
	return xmlconfig;

}


BOOL CEditInput::setDialogData(CEditInputData* _data)
{

	_data->intputXdr = m_inputeditvalue;
	return TRUE;
}
// CEditInput 消息处理程序


BOOL CEditInput::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GridCtrlInit();

	m_inputedit.SetEventMask(m_inputedit.GetEventMask()|ENM_SCROLL|ENM_CHANGE|ENM_SELCHANGE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CEditInput::GridCtrlInit()
{
	m_pGrid.SetEditable(true);
	m_pGrid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//黄色背景
	CStringA xdrtype;
	if (m_inputeditvalue == _T(""))
		xdrtype = "dr_cs";
	else
		xdrtype = judgexdrtype();

	int	rownum = xdrdefinemap[xdrtype].size();
	//else
	//	linenum = judgexdrtype();

	m_pGrid.SetRowCount(rownum+1);
	CString rowCountNum = m_inputeditvalue;
	int rowCount = rowCountNum.Replace(_T("\n"), _T("\t"));
	if(rowCount>=1)
		m_pGrid.SetColumnCount(rowCount+2);
	else if(m_inputeditvalue.GetLength()>100)
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


void CEditInput::OnEnChangeEdit1()
{
	CStringA xdrtype;
	m_inputedit.GetWindowTextW(m_inputeditvalue);
	if (m_inputeditvalue == _T(""))
		xdrtype = "dr_cs";
	else
		xdrtype = judgexdrtype();

	int	rownum = xdrdefinemap[xdrtype].size();

	m_pGrid.SetRowCount(rownum+1);
	CString rowCountNum = m_inputeditvalue;
	int colCount = rowCountNum.Replace(_T("\n"), _T("\t"));
	if (colCount >= 1)
		m_pGrid.SetColumnCount(colCount + 2);
	else if (m_inputeditvalue.GetLength()>100)
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


	/*int i, nLineCount = m_inputedit.GetLineCount();
	CString strText, strLine;
	int len = m_inputedit.LineLength(m_inputedit.LineIndex(0));
	m_inputedit.GetLine(0, strText.GetBuffer(len), len);
	strText.ReleaseBuffer(len);

	int charcount=0;
	for (int numindex = 0; numindex < len; )
	{
		numindex = strText.Find(_T(";"), numindex+1);
		if (numindex != -1)
		{
			charcount++;
		}
		else
			break;
	}

	for (int a = 0; a < xdrdefinemap.size(); a++)
	{
		if (charcount == xdrdefinemap["dr_cs"].size() || charcount == xdrdefinemap["dr_cs"].size() + 2)
		{
			int linenum = xdrdefinemap["dr_cs"].size();
			m_pGrid.SetRowCount(linenum);
			for (int row = 0; row < linenum; row++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;
				Item.row = row;
				Item.col = 0;
				if (row == 0)
				{
					continue;
				}
				else
				{
						Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
						Item.strText.Format((CString)xdrdefinemap["dr_cs"][row].xdr_field_name, row);
				}
				m_pGrid.SetItem(&Item);
			}
		}
		else if (charcount == xdrdefinemap["dr_ps"].size() || charcount == xdrdefinemap["dr_ps"].size() + 2)
		{
			int linenum = xdrdefinemap["dr_ps"].size();
			m_pGrid.SetRowCount(linenum);
			for (int row = 0; row < linenum; row++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;
				Item.row = row;
				Item.col = 0;
				if (row == 0)
				{
					continue;
				}
				else
				{
					Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					Item.strText.Format((CString)xdrdefinemap["dr_ps"][row].xdr_field_name, row);
				}
				m_pGrid.SetItem(&Item);
			}
		}
		else if (charcount == xdrdefinemap["dr_sms"].size() || charcount == xdrdefinemap["dr_sms"].size() + 2)
		{
			int linenum = xdrdefinemap["dr_sms"].size();
			m_pGrid.SetRowCount(linenum);
			for (int row = 0; row < linenum; row++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;
				Item.row = row;
				Item.col = 0;
				if (row == 0)
				{
					continue;
				}
				else
				{
					Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					Item.strText.Format((CString)xdrdefinemap["dr_sms"][row].xdr_field_name, row);
				}
				m_pGrid.SetItem(&Item);
			}
		}
		else if (charcount == xdrdefinemap["dr_ismp"].size() || charcount == xdrdefinemap["dr_ismp"].size() + 2)
		{
			int linenum = xdrdefinemap["dr_ismp"].size();
			m_pGrid.SetRowCount(linenum);
			for (int row = 0; row < linenum; row++)
			{
				GV_ITEM Item;
				Item.mask = GVIF_TEXT | GVIF_FORMAT;
				Item.row = row;
				Item.col = 0;
				if (row == 0)
				{
					continue;
				}
				else
				{
					Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
					Item.strText.Format((CString)xdrdefinemap["dr_ismp"][row].xdr_field_name, row);
				}
				m_pGrid.SetItem(&Item);
			}
		}
	}*/
	


}



void CEditInput::analysexml(XMLElement* xmlconfig)
{
	XMLElement* node_config = xmlconfig->FirstChildElement("node_config");
	m_inputeditvalue = (node_config->FirstChildElement("xdr"))->GetText();
}


CStringA CEditInput::judgexdrtype()
{
	int index = m_inputeditvalue.Find(_T("\n"));
	CString strResult = m_inputeditvalue.Left(index);
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


CString CEditInput::analyseeditvalue(int row, int col, BOOL isUpdata)
{
	CString tmpeditvalue;
	if(isUpdata==TRUE)
		m_inputedit.GetWindowTextW(tmpeditvalue);
	else
		tmpeditvalue = m_inputeditvalue;
	int length = tmpeditvalue.GetLength();
	int startIndex = 0;
	int endIndex = 0;
	CString strResult;
	for (int i = 1; i <= row; i++)
	{
		endIndex = (tmpeditvalue.Find(_T("\n"))==-1)? tmpeditvalue.GetLength(): tmpeditvalue.Find(_T("\n"));
		int lineEndIndex = endIndex;
		CString tmptmpeditvalue = tmpeditvalue.Mid(startIndex, endIndex);
		int tmpIndex = 0;
		for (int j = 1;j <= col; j++)
		{
			tmpIndex = tmptmpeditvalue.Find(_T(";"));
			strResult = tmptmpeditvalue.Mid(startIndex, tmpIndex);
			tmptmpeditvalue = tmptmpeditvalue.Right( endIndex -= (tmpIndex+1));

		}
		tmpeditvalue = tmpeditvalue.Right(length -= (lineEndIndex + 1));
	}
	return strResult;
}


XMLElement* CEditInput::generatexml(CEditInputData* data, int buttonseq)
{
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	XMLElement* xmlconfigtmp = doc->NewElement("flow");
	XMLElement* flow_name = doc->NewElement("flow_name");
	XMLElement* flow_seq = doc->NewElement("flow_seq");
	XMLElement* node_config = doc->NewElement("node_config");
	XMLElement* xdr = doc->NewElement("xdr");

	doc->InsertEndChild(xmlconfigtmp);
	xmlconfigtmp->InsertEndChild(flow_name);
	xmlconfigtmp->InsertEndChild(flow_seq);
	xmlconfigtmp->InsertEndChild(node_config);
	node_config->InsertEndChild(xdr);


	XMLText* flow_name_text = doc->NewText("INPUTEDIT");
	flow_name->InsertEndChild(flow_name_text);
	XMLText* flow_seq_text = doc->NewText(buttonseq);
	flow_seq->InsertEndChild(flow_seq_text);
	XMLText* checkshel_text = doc->NewText(data->intputXdr);
	xdr->InsertEndChild(checkshel_text);

	return xmlconfigtmp;

}


BOOL EditInputExec(XMLElement* xmlConfig)
{
	CString inputXdr;
	XMLElement* node_config = xmlConfig->FirstChildElement("node_config");
	inputXdr = (node_config->FirstChildElement("xdr"))->GetText();
	return TRUE;
}