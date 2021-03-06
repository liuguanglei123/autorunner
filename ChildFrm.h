
// ChildFrm.h : CChildFrame 类的接口
//

#pragma once
#include "ContentView.h"
#include "cctrlview.h"


class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 特性
public:

// 操作
public:

// 重写
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
	cctrlview *leftview;  //左侧ctrl视图类
	CContentView *rightview; //右侧content视图类
	CSplitterWnd m_wndSplitter; //分割窗口类
	virtual void ActivateFrame(int nCmdShow = -1);
};
