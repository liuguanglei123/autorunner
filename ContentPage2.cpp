// ContentPage2.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ContentPage2.h"
#include "afxdialogex.h"
#include "MyButton.h"
#include "EditInput.h"
#include "PreDataDlg.h"
#include "CompareDataDlg.h"
#include "ExecshellDlg.h"
#include "ContentView.h"

STR_ENUM_BEGIN()
STR_ENUM_ITEM(_T("CLEANENV"), CLEANENV)
STR_ENUM_ITEM(_T("PREDATA"), PREDATA)
STR_ENUM_ITEM(_T("INPUTEDIT"), INPUTEDIT)
STR_ENUM_ITEM(_T("EXECSHELL"), EXECSHELL)
STR_ENUM_ITEM(_T("COMPAREFILE"), COMPAREFILE)
STR_ENUM_ITEM(_T("COMPAREDATA"), COMPAREDATA)
STR_ENUM_END()


extern buttonattr butattr;
// CContentPage2 对话框
IMPLEMENT_DYNAMIC(CContentPage2, CPropertyPage)

CContentPage2::CContentPage2()
	: CPropertyPage(IDD_ContentDlg2)
{
	m_casexml = _T("");
	m_caseconfig = _T("");
}

CContentPage2::~CContentPage2()
{
}

void CContentPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CContentPage2, CPropertyPage)
	ON_COMMAND_RANGE(IDC_D_BTN, IDC_D_BTN+100,createnewdialog)
END_MESSAGE_MAP()


// CDialogUserAttr 消息处理程序


BOOL CContentPage2::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	RECT rect;
	this->GetClientRect(&rect);

	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);


	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CContentPage2::createnewdialog(UINT nID)
{
	switch(butattr[nID].buttontype)
	{
	case CLEANENV:
		return;
	case PREDATA:
		PreDataBut *prebutton;
		prebutton = (PreDataBut *)GetDlgItem(nID);
		CPreDataData *predata;
		node_assemble[butattr[nID].buttonseq] = prebutton->CreateDiaLog(node_assemble[butattr[nID].buttonseq], butattr[nID].buttonseq);
		break;
	case INPUTEDIT:
		EditInputBut *editbutton;
		editbutton = (EditInputBut *)GetDlgItem(nID);
		CEditInputData *editdata;
		node_assemble[butattr[nID].buttonseq] = editbutton->CreateDiaLog(node_assemble[butattr[nID].buttonseq], butattr[nID].buttonseq);
		break;
	case EXECSHELL:
		ExecshellDlgBut *execshellbutton;
		execshellbutton = (ExecshellDlgBut *)GetDlgItem(nID);
		CExecshellDlgData *execshelldata;
		node_assemble[butattr[nID].buttonseq] = execshellbutton->CreateDiaLog(node_assemble[butattr[nID].buttonseq], butattr[nID].buttonseq);
		m_caseconfig = execshellbutton->m_buttonData->configxml;
		break;
	case COMPAREFILE:
		break;
	case COMPAREDATA:
		CompareDataBut *comparedatabutton;
		comparedatabutton = (CompareDataBut *)GetDlgItem(nID);
		CCompareDatadata *comparedatadata;
		node_assemble[butattr[nID].buttonseq] = comparedatabutton->CreateDiaLog(node_assemble[butattr[nID].buttonseq], butattr[nID].buttonseq);
		break;
	}
	XMLElement* tmpXmlelement;
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->Parse(m_casexml);
	tmpXmlelement = doc->FirstChildElement("root")->FirstChildElement("flows")->FirstChildElement("flow");
	XMLNode* flowsNode = doc->FirstChildElement("root")->FirstChildElement("flows");

	if (tmpXmlelement == NULL)
	{
		insertEleToCaseXml(node_assemble[butattr[nID].buttonseq], flowsNode, doc);
	}
	else
	{
		int needreturn = 0;
		while (tmpXmlelement)
		{
			int tmpFlowSeq = atoi((tmpXmlelement->FirstChildElement("flow_seq"))->GetText());
			if (butattr[nID].buttonseq == tmpFlowSeq)
			{
				needreturn = 1;
				flowsNode->DeleteChild(tmpXmlelement);
				insertEleToCaseXml(node_assemble[butattr[nID].buttonseq], flowsNode, doc);
				break;
			}
			tmpXmlelement = tmpXmlelement->NextSiblingElement();
		}
		if(needreturn == 0)
			insertEleToCaseXml(node_assemble[butattr[nID].buttonseq], flowsNode, doc);

	}
	//NextSiblingElement
	//m_checkshellvalue = ((atoi((node_config->FirstChildElement("checkshel"))->GetText()) == 1) ? TRUE : FALSE);
	XMLPrinter printer;
	doc->Print(&printer);

	m_casexml = printer.CStr();
	
}


int CContentPage2::CreateBut(int seq, int buttype, BOOL isbatch)
{

	int buttionid;
	switch (buttype)
	{
	case PREDATA:
	{
		PreDataBut *pre_Button = new PreDataBut();//动态创建按钮
		buttionid = pre_Button->CreateBut(this, seq, PREDATA); //创建按钮
		if (!isbatch)
		{
			func_struct tmpfunc;
			tmpfunc.func_seq = seq;
			tmpfunc.func_name = _T("PREDATA");
			tmpfunc.background_execution = 0;
			func_assemble.push_back(tmpfunc);
			node_assemble[seq] = NULL;
		}
		break;
	}
	case EXECSHELL:
	{
		ExecshellDlgBut *exec_Button = new ExecshellDlgBut();//动态创建按钮
		buttionid = exec_Button->CreateBut(this, seq, EXECSHELL); //创建按钮
		if (!isbatch)
		{
			func_struct tmpfunc;
			tmpfunc.func_seq = seq;
			tmpfunc.func_name = _T("EXECSHELL");
			tmpfunc.background_execution = 0;
			func_assemble.push_back(tmpfunc);
			node_assemble[seq] = NULL;
		}
		break;
	}
	case INPUTEDIT:
	{
		EditInputBut *edit_Button = new EditInputBut();//动态创建按钮
		buttionid = edit_Button->CreateBut(this, seq, INPUTEDIT); //创建按钮
		if (!isbatch)
		{
			func_struct tmpfunc;
			tmpfunc.func_seq = seq;
			tmpfunc.func_name = _T("INPUTEDIT");
			tmpfunc.background_execution = 0;
			func_assemble.push_back(tmpfunc);
			node_assemble[seq] = NULL;
		}
		break;
	}
	case COMPAREDATA:
	{
		CompareDataBut *comdata_Button = new CompareDataBut();//动态创建按钮
		buttionid = comdata_Button->CreateBut(this, seq, COMPAREDATA); //创建按钮
		if (!isbatch)
		{
			func_struct tmpfunc;
			tmpfunc.func_seq = seq;
			tmpfunc.func_name = _T("COMPAREDATA");
			tmpfunc.background_execution = 0;
			func_assemble.push_back(tmpfunc);
			node_assemble[seq] = NULL;
		}
		break;
	}
	case CLEANENV:
		return 0;
	}
	if (!isbatch)
	{
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->Parse(m_casexml);

		XMLElement* function = doc->NewElement("function");
		XMLElement* func_seq = doc->NewElement("func_seq");
		XMLText* func_seq_text = doc->NewText(seq);
		XMLElement* func_name = doc->NewElement("func_name");
		XMLText* func_name_text = doc->NewText(func_assemble[seq-1].func_name);
		XMLElement* background_execution = doc->NewElement("background_execution");
		XMLText* background_execution_text = doc->NewText(0);
		XMLElement* root = doc->RootElement();
		XMLElement* func_define = root->FirstChildElement("func_define");

		func_define->InsertEndChild(function);
		function->InsertEndChild(func_seq);
		func_seq->InsertEndChild(func_seq_text);
		function->InsertEndChild(func_name);
		func_name->InsertEndChild(func_name_text);
		function->InsertEndChild(background_execution);
		background_execution->InsertEndChild(background_execution_text);

		XMLPrinter printer;
		doc->Print(&printer);
		USES_CONVERSION;
		m_casexml.Format(_T("%s"), A2W(printer.CStr()));
	}

	return buttionid;

	
}

void CContentPage2::analysexml()
{
	func_assemble.clear();
	node_assemble.clear();
	butattr.clear();
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	doc->Parse(m_casexml);

	XMLElement* root = doc->FirstChildElement("root");

	XMLElement* func_define = root->FirstChildElement("func_define");
	XMLElement* function = func_define->FirstChildElement("function");

	while (function)
	{
		func_struct tmp_funcstruct;
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
	createbatchbutton();


	return;
}


void CContentPage2::createbatchbutton()
{
	for (int i = 1; i <= func_assemble.size(); i++)
	{
		vector<func_struct>::iterator funcite;
		for (funcite= func_assemble.begin();funcite!= func_assemble.end();funcite++)
		{
			int buttonid;
			if (funcite->func_seq == i)
			{
				switch (STR_ENUM_GET(funcite->func_name))
				{
				case CLEANENV:
				{
					buttonid = CreateBut(i, CLEANENV,TRUE);
					buttonattrpair newbutattr(buttonid, { CLEANENV,i });
					butattr.insert(newbutattr);
					break;
				}
				case PREDATA:
				{
					buttonid = CreateBut(i, PREDATA, TRUE);
					buttonattrpair newbutattr(buttonid, { PREDATA,i });
					butattr.insert(newbutattr);
					break;
				}
				case INPUTEDIT:
				{
					buttonid = CreateBut(i, INPUTEDIT, TRUE);
					buttonattrpair newbutattr(buttonid, { INPUTEDIT,i });
					butattr.insert(newbutattr);
					break;
				}
				case EXECSHELL:
				{
					buttonid = CreateBut(i, EXECSHELL, TRUE);
					buttonattrpair newbutattr(buttonid, { EXECSHELL,i });
					butattr.insert(newbutattr);
					break;
				}
				case COMPAREFILE:
				{
					buttonid = CreateBut(i, COMPAREFILE, TRUE);
					buttonattrpair newbutattr(buttonid, { COMPAREFILE,i });
					butattr.insert(newbutattr);
					break;
				}
				case COMPAREDATA:
				{
					buttonid = CreateBut(i, COMPAREDATA, TRUE);
					buttonattrpair newbutattr(buttonid, { COMPAREDATA,i });
					butattr.insert(newbutattr);
					break;
				}
				//enum DialogType { CLEANENV, PREDATA, INPUTEDIT, EXECSHELL, COMPAREFILE, COMPAREDATA };
				default:
					break;
				}
			}
		}
		CContentView::m_nButSeq = i + 1;
	}
}



void CContentPage2::DeleteAllItems()
{
	map<int, butcont>::iterator iter = butattr.begin();
	while (iter != butattr.end())
	{
		switch(iter->second.buttontype)
		{
			case PREDATA:
				(PreDataBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			case CLEANENV:
				(PreDataBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			case INPUTEDIT:
				(EditInputBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			case EXECSHELL:
				(ExecshellDlgBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			case COMPAREFILE:
				(PreDataBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			case COMPAREDATA:
				(CompareDataBut*)GetDlgItem(iter->first)->DestroyWindow();
				break;
			default:
				break;
		}
		iter++;
	}
	func_assemble.clear();
	node_assemble.clear();
	butattr.clear();
}


void CContentPage2::generatexml()
{
	//tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	//doc.Parse(declaration);




}

void CContentPage2::CreateNewXml()
{
	/*((CContentPage2*)pSheet->GetPage(1))->m_casexml=_T("");
	((CContentPage2*)pSheet->GetPage(1))->m_caseconfig = _T("");*/
	const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
	tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();
	doc.Parse(declaration);
	XMLElement* root = doc.NewElement("root");
	doc.InsertEndChild(root);
	XMLElement* func_define = doc.NewElement("func_define");
	root->InsertEndChild(func_define);
	XMLElement* flows = doc.NewElement("flows");
	root->InsertEndChild(flows);

	XMLPrinter printer;
	doc.Print(&printer);
	USES_CONVERSION;
	m_casexml.Format(_T("%s"), A2W(printer.CStr()));
}


void CContentPage2::getPage2Xml()
{
	//vector<func_struct> func_assemble;  //用来存储func_define的数据，与contentview中的butattr变量类似
	//map<int, XMLElement*> node_assemble;//用来存储xml化的配置内容

	//tinyxml2::XMLDocument doc = new tinyxml2::XMLDocument();



}
void CContentPage2::insertEleToCaseXml(XMLElement *in, XMLNode *out,tinyxml2::XMLDocument* doc)
{
	while (in)
	{
		XMLNode *copy = in->ShallowClone(doc);
		XMLNode *out1 = out->InsertEndChild(copy);
		XMLElement *in1 = in->FirstChildElement();
		if (in1 == NULL)
		{
			const char* abc = out1->Value();
			XMLText* text = doc->NewText(in->GetText());
			XMLText* copytext = doc->NewText(text->Value());
			out1->InsertEndChild(copytext);
		}
		else
		{
			insertEleToCaseXml(in1, out1, doc);
		}
		out->InsertEndChild(copy);
		in = in->NextSiblingElement();
	}

	return;
}

