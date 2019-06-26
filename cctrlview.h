#pragma once



// cctrlview 窗体视图

class cctrlview : public CFormView
{
	DECLARE_DYNCREATE(cctrlview)

protected:
	cctrlview();           // 动态创建所使用的受保护的构造函数
	virtual ~cctrlview();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCTRLVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnDoubleclickedExecshell();
	afx_msg void OnBnDoubleclickedPredata();
	afx_msg void OnBnDoubleclickedInputedit();
	afx_msg void OnBnDoubleclickedComparefile();
	afx_msg void OnBnDoubleclickedComparedata();
	afx_msg void OnBnDoubleclickedCleandata();
};


