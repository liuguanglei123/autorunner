#pragma once
#include "stdafx.h"
#include "MFCApplication1.h"


// CMyButton
template <class _data,class _dialog>
class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)
public:
	_data* m_buttonData;

	CMyButton();
	~CMyButton();
	BOOL setDialogData(_data* dialogdata);
	BOOL getDialogData(XMLElement* xmlconfig);

	int CreateBut(CWnd* pParentWnd, UINT nSEQ, UINT dialogtype);
	BOOL SeqChange();

	XMLElement* CreateDiaLog(XMLElement* xmlconfig, int buttonseq); //创建_dialog类型的对话框
	BOOL UpdateData(); //同步数据



protected:
	DECLARE_MESSAGE_MAP()
};

template <class _data, class _dialog>
CMyButton<_data, _dialog>::CMyButton()
{
	CButton::CButton();
	m_buttonData = new _data();
	//m_buttonData = NULL;
}



template <class _data, class _dialog>
BOOL CMyButton<_data, _dialog>::setDialogData(_data* dialogdata)
{
	//dialogdata.setdata();
	return TRUE;
}

template <class _data, class _dialog>
BOOL CMyButton<_data, _dialog>::getDialogData(XMLElement* xmlconfig)
{
	//m_buttonData = new _data();
	m_buttonData->setDialogDatafromxml(xmlconfig);
	return TRUE;
}

template <class _data, class _dialog>
XMLElement* CMyButton<_data, _dialog>::CreateDiaLog(XMLElement* xmlconfig,int buttonseq)
{
	_dialog AssignDialog;
	//if()
	xmlconfig = AssignDialog.CreateDiaLog(xmlconfig, m_buttonData, buttonseq);
	return xmlconfig;
}


template <class _data, class _dialog>
CMyButton<_data, _dialog>::~CMyButton()
{

}

template <class _data, class _dialog>
int CMyButton<_data, _dialog>::CreateBut(CWnd* pParentWnd, UINT nSEQ, UINT dialogtype)
{
	/*attri.m_nDialogType = dialogtype;
	attri.m_nSeq = nSEQ;*/
	CRect rect;
	pParentWnd->GetClientRect(rect);
	if(nSEQ>1)
		rect.top = nSEQ * 2 + ( nSEQ - 1 )*30;
	else
		rect.top = nSEQ * 2 ;
	rect.bottom = rect.top + 30;
	switch (dialogtype)
	{
		case CLEANENV:
			CButton::Create(_T("清理环境"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		case PREDATA:
			CButton::Create(_T("预置数据"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		case INPUTEDIT:
			CButton::Create(_T("编辑输入内容"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		case EXECSHELL:
			CButton::Create(_T("执行命令"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		case COMPAREFILE:
			CButton::Create(_T("比对文件"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		case COMPAREDATA:
			CButton::Create(_T("比对数据"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				rect, pParentWnd, IDC_D_BTN + nSEQ);
			return IDC_D_BTN + nSEQ;
		default:
			return FALSE;
	}
}







//IMPLEMENT_DYNAMIC(CMyButton<_data, _dialog>, CButton)
template <class _data, class _dialog>
CRuntimeClass* PASCAL CMyButton<_data, _dialog>::_GetBaseClass()
{
	return RUNTIME_CLASS(CButton);
}

LPCSTR class_name_but("CMyButton");
template <class _data, class _dialog>
AFX_COMDAT const CRuntimeClass CMyButton<_data, _dialog>::classCMyButton = {
	class_name_but, sizeof(class CMyButton), 0xFFFF, NULL,
	&CMyButton<_data, _dialog>::_GetBaseClass, NULL, NULL };

template <class _data, class _dialog>
CRuntimeClass* PASCAL CMyButton<_data, _dialog>::GetThisClass()
{
	return _RUNTIME_CLASS(CMyButton);
}

template <class _data, class _dialog>
CRuntimeClass* CMyButton<_data, _dialog>::GetRuntimeClass() const
{
	return _RUNTIME_CLASS(CMyButton);
}


//BEGIN_MESSAGE_MAP(CMyButton, CButton)
PTM_WARNING_DISABLE
template <class _data, class _dialog>
const AFX_MSGMAP* CMyButton<_data, _dialog>::GetMessageMap() const
{
	return GetThisMessageMap();
}

template <class _data, class _dialog>
const AFX_MSGMAP* PASCAL CMyButton<_data, _dialog>::GetThisMessageMap()
{
	typedef CMyButton<_data, _dialog> ThisClass;
	typedef CButton TheBaseClass;
	static const AFX_MSGMAP_ENTRY _messageEntries[] =
	{

	END_MESSAGE_MAP()


