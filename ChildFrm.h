
// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once
#include "ContentView.h"
#include "cctrlview.h"


class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
public:

// ����
public:

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
	cctrlview *leftview;  //���ctrl��ͼ��
	CContentView *rightview; //�Ҳ�content��ͼ��
	CSplitterWnd m_wndSplitter; //�ָ����
	virtual void ActivateFrame(int nCmdShow = -1);
};
