
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	cs.style |= WS_MAXIMIZEBOX;

	/*RECT rect;
	CString changkuangao;
	GetClientRect(&rect);
	changkuangao.Format(_T("%d,%d,%d,%d"), rect.top, rect.bottom, rect.left, rect.right);
	AfxMessageBox(changkuangao);*/


	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	RECT rect;


	m_wndSplitter.CreateStatic(this, 1, 2);
	
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(cctrlview),
		CSize(200, 1000), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CContentView),
		CSize(1000, 2000), pContext);

	leftview = (cctrlview*)m_wndSplitter.GetPane(0, 0);

	rightview = (CContentView*)m_wndSplitter.GetPane(0, 1);
	return true;
}


void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: 在此添加专用代码和/或调用基类
	nCmdShow = SW_MAXIMIZE;

	CMDIChildWndEx::ActivateFrame(nCmdShow);
}
