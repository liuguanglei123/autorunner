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
*                     佛祖保佑        永无BUG
*/
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"
#include <map>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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

#define WM_CATALOGSHOW      WM_USER+200 //点击最左侧case区域后，向contentview视图发送显示该案例下按钮的消息
#define WM_COPYCASE      WM_USER+201 //复制一个新的案例后，向contenrview发送该消息，在消息参数中传入复制的案例ID


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

