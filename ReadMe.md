Autorunner项目简述                                                          
#项目起源
	在亚信工作的两年时间里，公司一直没有实现很好的自动化测试，手工回归工作量非常巨大，因为业务的特殊性，没有一款现成的工具可以直接使用，因此产生了设计一款自动化测试工具的想法，因为在华为外包方工作过一段时间，对华为自研的TMSS工具有一定使用经验，便尝试根据印象中的TMSS样式及功能进行开发。采用的框架是windows下的MFC，开发语言是C++。
	一款自动化测试工具功能，应当包含案例的查看，管理，执行，结果比对等。由于时间原因，最终工具实现度只有五分之一，也并不具有可用性，已经完成的部分包括工具整体框架设计实现、部分数据库交互（测试案例的层级管理和bsxdrdefine表的配置读取）、案例结构管理、xml解析、部分日志显示、案例存取等基本功能。
##基本页面
	工具界面分为四个区域，对应四个不同的MFC view可视化类

![1.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/1.png)


最左侧（图1.2）为案例列表区，
对应caseview类，内部包含tree
组件，用来展示和编辑测试用例的
目录层级。利用MFC自带的Popup
右键菜单，可以针对case或者目
录进行不同操作。所有的目录和case
结构都保存在数据库表catalogtree
和casetree中。
![2.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/2.png)



中间部分为单个案例内容编辑展
示区域，主要由两个view类组成，左
侧为ctrlview（组件视图），右侧为contentview（实际内容视图），
![3.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/3.png)


contentview中又单独分为两个dialog（两个对话框类对象），用来存放案例的文字描述和具体的操作步骤按钮（图1.3.1和图1.3.2）
![4.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/4.png)



contentview中双击左侧的组件视图中的某个按钮，可以将该步骤添加到右侧内容中。图中，左侧的“清理环境/预置资料/输入话单编辑/执行命令/文件比对/数据比对”为代码中定义好的各个步骤，双击后可以将该操作添加到右侧案例中，比如图中，就已经添加好预置数据，编辑输入内容，执行命令，比对数据四个步骤。
![5.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/5.png)




底部为预留的日志输入区域，用来展示测试用例修改和执行过程中的各种操作日志和错误输出


最右侧为预留的属性展示区域，用来展示案例的各种属性，该区域为预留，代码完全没有实现。


基本设计点说明：
1.案例编辑区域代码设计说明：
双击ctrlview中的不同按钮，会在contentview区域创建一个新的按钮，点击这个按钮，会打开不同的对话框，用来编辑测试用例中不同的步骤内容。要实现的是不同的按钮绑定不同的对话框，存储不同的内容。
以构造用户资料对话框进行说明：
创建CMyButton类，_data为存储的数据类，_dialog为展示的对话框显示类，将两者进行绑定，就可以实现动态创建一个新的按钮类时，不同的按钮，展示和存储不同的内容。
```
template <class _data,class _dialog>  
class CMyButton : public CButton  
```

比如双击打开对话框，定义的方法是，可以看到，实际调用的是绑定的对话框类_dialog的CreateDiaLog方法，并传入成员变量m_buttonData，这样就可以在每个对话框中重写CreateDiaLog，打开不同的对话框，写入不同的数据到buttonData进行存储和展示。
```
1.template <class _data, class _dialog>  
2.XMLElement* CMyButton<_data, _dialog>::CreateDiaLog(XMLElement* xmlconfig,  
3.                                                int buttonseq)  
4.{  
5.    _dialog AssignDialog;  
6.    xmlconfig = AssignDialog.CreateDiaLog(xmlconfig,   
7.                                         m_buttonData, buttonseq);  
8.    /*使用_dialog定义一个对话框对象，调用该对象的CreateDiaLog方法创建对话框*/  
9.    return xmlconfig;  
}
```
2.案例编辑区域代码设计说明：
	采用开源的xml解析代码 tinyxml2，可以将案例数据以xml形式保存到数据库中
	在数据库中设计表如下：
	
![6.png](https://github.com/liuguanglei123/httprunnerforjava_public/blob/master/src/test/showphoto/6.png)

在左侧的目录树点击对应测试用例后，会向中间区域视图发送展示案例内容的消息，contentview收到消息后，会查询数据库中该案例的内容，并解析查询到的xml文件，将各个按钮都展示出来，设计时考虑将xml解析后的对话框数据也绑定在按钮对象的m_buttonData变量中，不过并没有实现。
```
1.afx_msg LRESULT CContentView::OnShowCatalog(WPARAM wParam, LPARAM lParam)  
2.{     
3.    saveCaseToDatabase();//保存正在编辑的内容  
4.    //此处省略部分代码  
5.    ((CContentPage2*)pSheet->GetPage(1))->analysexml();//解析xml文件  
6.    //此处省略部分代码  
}
```

```
1.void CContentPage2::analysexml()  
2.{  
3.    //此处省略部分代码  
4.    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();  
5.     //创建一个xml对象  
6.    doc->Parse(m_casexml);  
7.    //此处省略部分代码  
8.    while (function)//解析xml中的按钮类别  
9.    {//此处省略部分代码} 
10.    while (flow)//解析xml中的按钮对应的数据内容  
11.    {//此处省略部分代码}  
12.    createbatchbutton();//根据保存的按钮类型和数据，创建不同的按钮 
}
```
```
1.void CContentPage2::createbatchbutton()  
2.{  
3.    //此处并没有实现将xml解析后对应的数据传入进来，否则就可以在创建按钮的同时，将内容绑定在m_buttonData变量中
4.    for (int i = 1; i <= func_assemble.size(); i++)  
5.    {  
6.        vector<func_struct>::iterator funcite;  
7.        for (funcite= func_assemble.begin();funcite!= func_assemble.end();funcite++)  
8.        {  
9.            int buttonid;  
10.            if (funcite->func_seq == i)  
11.            {  
12.                switch (STR_ENUM_GET(funcite->func_name))  
13.                {  
14.                case PREDATA:  
15.                {  
16.                    buttonid = CreateBut(i, PREDATA, TRUE);  
17.                    buttonattrpair newbutattr(buttonid, { PREDATA,i });  
18.                    butattr.insert(newbutattr);  
19.                    break;  
20.                }  
21.            }  
22.        }  
23.        CContentView::m_nButSeq = i + 1;  
24.    }  
}
```
4.简单多线程的使用
在主App类初始化时，增加线程来后台读取配置，提高启动速度。但没有采用复杂的互斥锁方式实现进程内资源访问的并发，因为配置读取是启动软件后一次性读取的，所以采用了变量条件形式。

```
1.BOOL CMFCApplication1App::InitInstance()  
2.{     
3.//此处省略部分代码  
4.AfxBeginThread(CMFCApplication1App::loadBsXdeDefine,this);  
}
```
```
1.UINT __cdecl CMFCApplication1App::loadBsXdeDefine(LPVOID pParam)  
2.{  
3.    //此处省略部分代码  
4.    bsXdrDefineLoadFinish = TRUE;   
5.     //变量条件，后续所有访问bsxdrdefine资源的地方都有变量条件的判断  
6.    return 1;  
7.  
}
```











