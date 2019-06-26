#pragma once

#include "ContentPage1.h"
#include "ContentPage2.h"


// CSelectSheet

class CContentSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CContentSheet)

public:
	CContentSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CContentSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CContentSheet();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CContentPage1 m_ContentPage1;
	CContentPage2 m_ContentPage2;
};


