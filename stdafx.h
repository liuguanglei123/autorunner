/**
*                             _ooOoo_
*                            o8888888o
*                            88" . "88
*                            (| -_- |)
*                            O\  =  /O
*                         ____/`---'\____
*                       .'  \\|     |//  `.
*                      /  \\|||  :  |||//  \
*                     /  _||||| -:- |||||-  \
*                     |   | \\\  -  /// |   |
*                     | \_|  ''\---/''  |   |
*                     \  .-\__  `-`  ___/-. /
*                   ___`. .'  /--.--\  `. . __
*                ."" '<  `.___\_<|>_/___.'  >'"".
*               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
*               \  \ `-.   \_ __\ /__ _/   .-` /  /
*          ======`-.____`-.___\_____/___.-`____.-'======
*                             `=---='
*          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
*                     ���汣��        ����BUG
*/
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"
#include <map>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <afxdb.h>        // ODBC
#include "bsxdrdefine.h"

#include <map>
#include <vector>
#include <list>
#include <string>
#include <afxdlgs.h>
using namespace std;





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#define WM_CREATEBUT_CLEANENV WM_USER+100
#define WM_CREATEBUT_EXECSHELL WM_USER+101
#define WM_CREATEBUT_PREDATA WM_USER+102
#define WM_CREATEBUT_INPUTEDIT WM_USER+103
#define WM_CREATEBUT_COMPAREFILE WM_USER+104
#define WM_CREATEBUT_COMPAREDATA WM_USER+105

#define IDC_D_BTN                       10000

#define WM_CATALOGSHOW      WM_USER+200 //��������case�������contentview��ͼ������ʾ�ð����°�ť����Ϣ
#define WM_COPYCASE      WM_USER+201 //����һ���µİ�������contenrview���͸���Ϣ������Ϣ�����д��븴�Ƶİ���ID


enum DialogType { CLEANENV, PREDATA, INPUTEDIT, EXECSHELL, COMPAREFILE, COMPAREDATA ,OTHER};



#define STR_ENUM_BEGIN() \
int _string2enum(CString name) \
{

#define STR_ENUM_ITEM(e,num) \
if(e==name) \
	return num;

#define STR_ENUM_END() \
else return OTHER;\
}

// get enum string   
#define STR_ENUM_GET(name) _string2enum(name)
// enum2string macro
//#define STRING2ENUM(name, num)  STR_ENUM_GET(name, num)




#include "tinyxml2.h"

using namespace tinyxml2;

struct func_struct
{
	int func_seq;
	CString func_name;
	int background_execution;
};

