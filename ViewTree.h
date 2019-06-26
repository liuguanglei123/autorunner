
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewTree : public CTreeCtrl
{
// 构造
public:
	CViewTree();

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMKillfocus(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnTvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
};
