/*
* Websphere.cpp 
*
* Created on 2007年9月26日, 上午10:24 By 苏合
* Modified on 2007-10-16 By 苏合
*          增加对英文版WebSphere的支持
* 
*
* 通过XML取得WebSphere的一些性能参数
* 
*/

// Websphere.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Websphere.h"
#include "tinyxml.h"
#include "funcGeneral.h"
#include <string>
#include <map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CWebsphereApp

BEGIN_MESSAGE_MAP(CWebsphereApp, CWinApp)
END_MESSAGE_MAP()

int WriteLog(const char* str)
{
#ifndef _DEBUG
	return 0;
#endif

	char timeBuf[128], dateBuf[128], wyt[4096];
	
	_tzset();
	
	_strtime( timeBuf );
	_strdate( dateBuf );
	
    sprintf(wyt, "%s %s\t", dateBuf, timeBuf );
	
	FILE* log;
		
	log = fopen("WebSphereMonitor.log", "a+");
	
	if(log != NULL)
	{
		strcat(wyt, str);
		fprintf(log, "%s\n", wyt);
		fclose(log);
	}
	
	return 0;
}

void ConvertUtf8ToGBK(CString &strUtf8) 
{ 
	int len= ::MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0); 
	unsigned short * wszGBK = new unsigned short[len+1]; 
	memset(wszGBK, 0, len * 2 + 2); 
	::MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, len); 
	len = ::WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL); 
	char *szGBK=new char[len + 1]; 
	memset(szGBK, 0, len + 1); 
	::WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL,NULL); 
	strUtf8 = szGBK; 
	delete[] szGBK; 
	delete[] wszGBK; 
}

BOOL GetSourceHtml(char* theUrl, char* saveFileName) 
{
	CInternetSession session;
	CInternetFile* file = NULL;
	try
	{
		// 试着连接到指定URL
		file = (CInternetFile*) session.OpenURL(theUrl); 
	}
	catch (CInternetException* m_pException)
	{
		// 如果有错误的话，置文件为空
		file = NULL; 
		m_pException->Delete();
		return FALSE;
	}

	// 用dataStore来保存读取的网页文件
	CStdioFile dataStore;

	if (file)
	{
		CString  somecode;							//也可采用LPTSTR类型，将不会删除文本中的\n回车符

		BOOL bIsOk = dataStore.Open(saveFileName,
			  CFile::modeCreate 
			| CFile::modeWrite 
			| CFile::shareDenyWrite 
			| CFile::typeText);

		if (!bIsOk)
			return FALSE;

		// 读写网页文件，直到为空
		bool flagReplace = false;
		int replaceNum = 0;
		while (file->ReadString(somecode) != NULL) //如果采用LPTSTR类型，读取最大个数nMax置0，使它遇空字符时结束
		{
			if (!flagReplace)
			{
				replaceNum = somecode.Replace("encoding=\"UTF-8\"" ,"encoding=\"gb2312\"");
				if (0 != replaceNum)
				{
					flagReplace = true;
				}
			}
			ConvertUtf8ToGBK(somecode);
			dataStore.WriteString(somecode);
			dataStore.WriteString("\n");		   //如果somecode采用LPTSTR类型,可不用此句
		}

		file->Close();
		delete file;
	}
	else
	{
		dataStore.WriteString(_T("到指定服务器的连接建立失败..."));	
		return FALSE;
	}

	return TRUE;
}

// CWebsphereApp 构造

CWebsphereApp::CWebsphereApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CWebsphereApp 对象

CWebsphereApp theApp;


// CWebsphereApp 初始化

BOOL CWebsphereApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Bean(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');           //避免类似“a.a.a.xml”的文件名，在后面用 TiXmlDocument 打开会有错误

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );
	

	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "beanModule")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();

	while ((0 != perfElement) && (0 != strcmp(perfElement->Value(), "creates")))
	{
		WriteLog(perfElement->Value());
		perfElement = perfElement->NextSiblingElement();
		
	}

	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		perfElement = perfElement->NextSiblingElement();
	}

	
	sprintf(strReturn, "%screates=%s$", strReturn, listPerf["creates"].c_str());

	sprintf(strReturn, "%sremoves=%s$", strReturn, listPerf["removes"].c_str());

	sprintf(strReturn, "%sactivates=%s$", strReturn, listPerf["activates"].c_str());

	sprintf(strReturn, "%spassivates=%s$", strReturn, listPerf["passivates"].c_str());

	sprintf(strReturn, "%sinstantiates=%s$", strReturn, listPerf["instantiates"].c_str());

	sprintf(strReturn, "%sdestroys=%s$", strReturn, listPerf["destroys"].c_str());

	//sprintf(strReturn, "%sloads=%s$", strReturn, listPerf["LoadCount"].c_str());

	//sprintf(strReturn, "%sstores=%s$", strReturn, listPerf["StoreCount"].c_str());

	//sprintf(strReturn, "%sconcurrentActives=%s$", strReturn, listPerf["MethodReadyCount"].c_str());

	sprintf(strReturn, "%sreadyCount=%s$", strReturn, listPerf["readyCount"].c_str());
	
	sprintf(strReturn, "%sconcurrentLives=%s$", strReturn, listPerf["concurrentLives"].c_str());

	sprintf(strReturn, "%stotalMethodCalls=%s$", strReturn, listPerf["totalMethodCalls"].c_str());

	sprintf(strReturn, "%savgMethodRt=%s$", strReturn, listPerf["avgMethodRt"].c_str());

	sprintf(strReturn, "%savgCreateTime=%s$", strReturn, listPerf["avgCreateTime"].c_str());

	sprintf(strReturn, "%savgRemoveTime=%s$", strReturn, listPerf["avgRemoveTime"].c_str());

	sprintf(strReturn, "%sactiveMethods=%s$", strReturn, listPerf["activeMethods"].c_str());

	sprintf(strReturn, "%sactivationTime=%s$", strReturn, listPerf["activationTime"].c_str());

	sprintf(strReturn, "%spassivationTime=%s$", strReturn, listPerf["passivationTime"].c_str());



	//sprintf(strReturn, "%sgetsFromPool=%s$", strReturn, listPerf["RetrieveFromPoolCount"].c_str());

	//sprintf(strReturn, "%sgetsFound=%s$", strReturn, listPerf["RetrieveFromPoolSuccessCount"].c_str());

	//sprintf(strReturn, "%sreturnsToPool=%s$", strReturn, listPerf["ReturnsToPoolCount"].c_str());

	//sprintf(strReturn, "%sreturnsDiscarded=%s$", strReturn, listPerf["ReturnsDiscardCount"].c_str());

	//sprintf(strReturn, "%sdrainsFromPool=%s$", strReturn, listPerf["DrainsFromPoolCount"].c_str());

	//sprintf(strReturn, "%savgDrainSize=%s$", strReturn, listPerf["DrainSize"].c_str());

	//sprintf(strReturn, "%spoolSize=%s$", strReturn, "0");

	DeleteFile(xmlFileName);

	strInput = strReturn;

	WriteLog(strReturn);
	MakeCharByString(strReturn, nSize, strInput);

	return TRUE;
}

extern "C" _declspec (dllexport) BOOL Cache(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	
	const char* pInput=strParas;
	while(*pInput)
	{
		WriteLog(pInput);

		pInput=pInput+strlen(pInput)+1;
	}


	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	WriteLog(tmpUrl);
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	WriteLog(xmlFileName);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	DeleteFile(xmlFileName);
	WriteLog("成功打开文件！");


	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
//	TiXmlElement *statRootElement = serverElement->FirstChildElement();
	TiXmlElement *statElement = serverElement->FirstChildElement();

	WriteLog("\n Value=");
	WriteLog(statElement->Value());

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "cacheModule")))
	{
		statElement = statElement->NextSiblingElement();
		WriteLog("\n name=");
		WriteLog(statElement->Value());
	}

	
	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");

		WriteLog(strReturn);

		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->NextSiblingElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		
		perfElement = perfElement->NextSiblingElement();
	}

	map<string,string>::iterator list_index=listPerf.begin();
	WriteLog("\n");
	WriteLog(list_index->first.c_str());
	WriteLog("=");
	WriteLog(list_index->second.c_str());

	sprintf(strReturn, "%smaxInMemoryCacheSize=%s$", strReturn, listPerf["maxInMemoryCacheSize"].c_str());

	sprintf(strReturn, "%sinMemoryCacheSize=%s$", strReturn, listPerf["inMemoryCacheSize"].c_str());

	sprintf(strReturn, "%stotalTimeoutInvalidations=%s$", strReturn, listPerf["totalTimeoutInvalidations"].c_str());

	//sprintf(strReturn, "%spoolSize=%s$", strReturn, listPerf["poolSize"].c_str());

	//sprintf(strReturn, "%spercentMaxed=%s$", strReturn, listPerf["percentMaxed"].c_str());

	

	strInput = strReturn;

	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}
extern "C" _declspec (dllexport) BOOL JVM(const char * strParas, char * strReturn, int& nSize)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");
	
	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );

	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();
	/*
	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "JVM 运行时")) && (0 != strcmp(statElement->Attribute("name"), "JVM Runtime"))))
	{
		statElement = statElement->NextSiblingElement();
	}
	*/
	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "jvmRuntimeModule"))) 
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());

		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	long nValue = 0;
	double dValue = 0;
	double percentMemory;

	nValue = atol(listPerf["freeMemory"].c_str());
	dValue = nValue/1024.00;
	sprintf(strReturn, "%sfreeMemory=%.2f$", strReturn, dValue);

	nValue = atol(listPerf["usedMemory"].c_str());
	percentMemory = nValue;       //percentMemory 临时保留接下来要计算的分子值
	dValue = nValue/1024.00;
	sprintf(strReturn, "%susedMemory=%.2f$", strReturn, dValue);

	nValue = atol(listPerf["totalMemory"].c_str());
	percentMemory = 100 * percentMemory / nValue;
	dValue = nValue/1024.00;
	sprintf(strReturn, "%stotalMemory=%.2f$", strReturn, dValue);

	sprintf(strReturn, "%spercentMemory=%.2f$", strReturn, percentMemory);

	strInput = strReturn;

	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL OrbPerf(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	
	const char* pInput=strParas;
	while(*pInput)
	{
		WriteLog(pInput);

		pInput=pInput+strlen(pInput)+1;
	}


	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	WriteLog(tmpUrl);
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	WriteLog(xmlFileName);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	WriteLog("成功打开文件！");

	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
//	TiXmlElement *statRootElement = serverElement->FirstChildElement();
	TiXmlElement *statElement = serverElement->FirstChildElement();

	WriteLog("\n Value=");
	WriteLog(statElement->Value());

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "orbPerfModule")))
	{
		statElement = statElement->NextSiblingElement();
		WriteLog("\n name=");
		WriteLog(statElement->Value());
	}

	
	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");

		WriteLog(strReturn);

		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->NextSiblingElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		
		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	map<string,string>::iterator list_index=listPerf.begin();
	WriteLog("\n");
	WriteLog(list_index->first.c_str());
	WriteLog("=");
	WriteLog(list_index->second.c_str());

	sprintf(strReturn, "%sreferenceLookupTime=%s$", strReturn, listPerf["referenceLookupTime"].c_str());

	sprintf(strReturn, "%stotalRequests=%s$", strReturn, listPerf["totalRequests"].c_str());

	sprintf(strReturn, "%sconcurrentRequests=%s$", strReturn, listPerf["concurrentRequests"].c_str());

	strInput = strReturn;

	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL ThreadPool(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	
	const char* pInput=strParas;
	while(*pInput)
	{
		WriteLog(pInput);

		pInput=pInput+strlen(pInput)+1;
	}


	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	WriteLog(tmpUrl);
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	WriteLog(xmlFileName);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	WriteLog("成功打开文件！");

	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
//	TiXmlElement *statRootElement = serverElement->FirstChildElement();
	TiXmlElement *statElement = serverElement->FirstChildElement();

	WriteLog("\n Value=");
	WriteLog(statElement->Value());

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "threadPoolModule")))
	{
		statElement = statElement->NextSiblingElement();
		WriteLog("\n name=");
		WriteLog(statElement->Value());
	}

	
	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");

		WriteLog(strReturn);

		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		
		/*char pstr[10];
		sprintf(pstr,"%s=%s",strName.c_str(),strValue.c_str());
		WriteLog(pstr);*/

		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	map<string,string>::iterator list_index=listPerf.begin();
	WriteLog("\n");
	WriteLog(list_index->first.c_str());
	WriteLog("=");
	WriteLog(list_index->second.c_str());

	sprintf(strReturn, "%sthreadCreates=%s$", strReturn, listPerf["threadCreates"].c_str());

	sprintf(strReturn, "%sthreadDestroys=%s$", strReturn, listPerf["threadDestroys"].c_str());

	sprintf(strReturn, "%sactiveThreads=%s$", strReturn, listPerf["activeThreads"].c_str());

	sprintf(strReturn, "%spoolSize=%s$", strReturn, listPerf["poolSize"].c_str());

	sprintf(strReturn, "%spercentMaxed=%s$", strReturn, listPerf["percentMaxed"].c_str());

	strInput = strReturn;

	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}


/*
extern "C" _declspec (dllexport) BOOL ConnectionPool(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		OutputDebugString("我在错误中，文件名是");
		OutputDebugString(xmlFileName);
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		return FALSE;
	}
	OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
	OutputDebugString("我出来了");
	OutputDebugString(xmlFileName);
	OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();

	while ((0 != statElement) && ((0 != strcmp(statElement->Attribute("name"), "JDBC 连接池")) && (0 != strcmp(statElement->Attribute("name"), "JDBC Connection Pools"))))
	{
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		OutputDebugString(statElement->Attribute("name"));
		OutputDebugString("\n+++++++++++++++++++++++++++++sxc+++++++++++++++++++++++++++++\n");
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement()->FirstChildElement()->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Attribute("name");
		if (0 != perfElement->Attribute("count"))
		{
			strValue = perfElement->Attribute("count");
		}
		else if (0 != perfElement->Attribute("value"))
		{
			strValue = perfElement->Attribute("value");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		perfElement = perfElement->NextSiblingElement();
	}

	sprintf(strReturn, "%snumCreates=%s$", strReturn, listPerf["CreateCount"].c_str());
	sprintf(strReturn, "%snumDestroys=%s$", strReturn, listPerf["CloseCount"].c_str());
	sprintf(strReturn, "%snumAllocates=%s$", strReturn, listPerf["AllocateCount"].c_str());
	sprintf(strReturn, "%snumReturns=%s$", strReturn, listPerf["ReturnCount"].c_str());
	sprintf(strReturn, "%spoolSize=%s$", strReturn, listPerf["PoolSize"].c_str());
	sprintf(strReturn, "%sconcurrentWaiters=%s$", strReturn, listPerf["WaitingThreadCount"].c_str());
	sprintf(strReturn, "%savgWaitTime=%s$", strReturn, listPerf["WaitTime"].c_str());
	sprintf(strReturn, "%spercentUsed=%s$", strReturn, listPerf["PercentUsed"].c_str());
	sprintf(strReturn, "%spercentMaxed=%s$", strReturn, listPerf["PercentMaxed"].c_str());
	sprintf(strReturn, "%sprepStmtCacheDiscards=%s$", strReturn, listPerf["PrepStmtCacheDiscardCount"].c_str());
	
	strInput = strReturn;
	OutputDebugString("\n+++++++++++++++++++++++++++++返回值+++++++++++++++++++++++++++++\n");
	OutputDebugString("strReturn");
	OutputDebugString("\n+++++++++++++++++++++++++++++返回值+++++++++++++++++++++++++++++\n");
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}
*/

extern "C" _declspec (dllexport) BOOL WebApp(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();
	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "webAppModule")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();

	while ((0 != perfElement) && (0 == strcmp(perfElement->Value(), "WebModule")))
	{
		WriteLog(perfElement->Value());
		perfElement = perfElement->NextSiblingElement();
		
	}

	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		//else if (0 != pvalueElement->Attribute("currentValue"))
		//{
		//	strValue = pvalueElement->Attribute("currentValue");
		//}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());

		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	sprintf(strReturn, "%snumLoadedServlets=%s$", strReturn, listPerf["numLoadedServlets"].c_str());
	sprintf(strReturn, "%snumReloads=%s$", strReturn, listPerf["numReloads"].c_str());
	sprintf(strReturn, "%stotalRequests=%s$", strReturn, listPerf["totalRequests"].c_str());
	sprintf(strReturn, "%sconcurrentRequests=%s$", strReturn, listPerf["concurrentRequests"].c_str());
	sprintf(strReturn, "%sresponseTime=%s$", strReturn, listPerf["responseTime"].c_str());
	sprintf(strReturn, "%snumErrors=%s$", strReturn, listPerf["numErrors"].c_str());

	strInput = strReturn;
	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL ServletSessions(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "servletSessionsModule")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		
		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	sprintf(strReturn, "%screatedSessions=%s$", strReturn, listPerf["createdSessions"].c_str());

	sprintf(strReturn, "%sinvalidatedSessions=%s$", strReturn, listPerf["invalidatedSessions"].c_str());

	sprintf(strReturn, "%ssessionLifeTime=%s$", strReturn, listPerf["sessionLifeTime"].c_str());

	sprintf(strReturn, "%sactiveSessions=%s$", strReturn, listPerf["activeSessions"].c_str());

	sprintf(strReturn, "%sliveSessions=%s$", strReturn, listPerf["liveSessions"].c_str());

	sprintf(strReturn, "%snoRoomForNewSession=%s$", strReturn, listPerf["noRoomForNewSession"].c_str());

	sprintf(strReturn, "%scacheDiscards=%s$", strReturn, listPerf["cacheDiscards"].c_str());

	sprintf(strReturn, "%sexternalReadTime=%s$", strReturn, listPerf["externalReadTime"].c_str());

	sprintf(strReturn, "%sexternalReadSize=%s$", strReturn, listPerf["externalReadSize"].c_str());

	sprintf(strReturn, "%sexternalWriteTime=%s$", strReturn, listPerf["externalWriteTime"].c_str());

	sprintf(strReturn, "%sexternalWriteSize=%s$", strReturn, listPerf["externalWriteSize"].c_str());

	sprintf(strReturn, "%saffinityBreaks=%s$", strReturn, listPerf["affinityBreaks"].c_str());

	sprintf(strReturn, "%stimeSinceLastActivated=%s$", strReturn, listPerf["timeSinceLastActivated"].c_str());

	sprintf(strReturn, "%sinvalidatedViaTimeout=%s$", strReturn, listPerf["invalidatedViaTimeout"].c_str());

	sprintf(strReturn, "%sactivateNonExistSessions=%s$", strReturn, listPerf["activateNonExistSessions"].c_str());

	strInput = strReturn;
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}

extern "C" _declspec (dllexport) BOOL System(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	
	const char* pInput=strParas;
	while(*pInput)
	{
		WriteLog(pInput);

		pInput=pInput+strlen(pInput)+1;
	}


	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	WriteLog(tmpUrl);
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	WriteLog(xmlFileName);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	WriteLog("成功打开文件！");

	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
//	TiXmlElement *statRootElement = serverElement->FirstChildElement();
	TiXmlElement *statElement = serverElement->FirstChildElement();

	WriteLog("\n Value=");
	WriteLog(statElement->Value());

	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "systemModule")))
	{
		statElement = statElement->NextSiblingElement();
		WriteLog("\n name=");
		WriteLog(statElement->Value());
	}

	
	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");

		WriteLog(strReturn);

		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());

		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("currentValue"))
		{
			strValue = pvalueElement->Attribute("currentValue");
		}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		
		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	map<string,string>::iterator list_index=listPerf.begin();
	WriteLog("\n");
	WriteLog(list_index->first.c_str());
	WriteLog("=");
	WriteLog(list_index->second.c_str());

	sprintf(strReturn, "%scpuUtilization=%s$", strReturn, listPerf["cpuUtilization"].c_str());

	sprintf(strReturn, "%savgCpuUtilization=%s$", strReturn, listPerf["avgCpuUtilization"].c_str());

	sprintf(strReturn, "%sfreeMemory=%s$", strReturn, listPerf["freeMemory"].c_str());

	strInput = strReturn;

	WriteLog(strReturn);

	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}


extern "C" _declspec (dllexport) BOOL Transaction(const char * strParas, char * strReturn, int& nSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strInput;  //用于转换返回值strReturn的临时变量

	CStringList lstParas;
	MakeStringListByChar(lstParas, strParas);

	CString strUrl=_T("");
	CString strServer=_T("");
	CString strMonitorID=_T("");

	strUrl = GetValueFromList("_URL",lstParas);
	strServer = GetValueFromList("_Server",lstParas);
	strMonitorID = GetValueFromList("_MonitorID", lstParas);
	strMonitorID.Replace('.', '_');

	//strServer = "server1";

	if(strUrl.IsEmpty())
	{
		sprintf(strReturn,"error=URL不能为空$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	//strUrl = "http://192.168.0.162:9080/wasPerfTool/servlet/perfservlet";

	//下载xml文件
	char *tmpUrl = strUrl.GetBuffer(strUrl.GetLength());
	char *tmpMonitorID = strMonitorID.GetBuffer(strMonitorID.GetLength());
	char xmlFileName[30] = {0}; 
	sprintf(xmlFileName, "Websphere_%s.xml" ,tmpMonitorID);
	if(!GetSourceHtml(tmpUrl, xmlFileName))
	{
		sprintf(strReturn,"error=Internet Connect fail$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	strUrl.ReleaseBuffer( );
	strMonitorID.ReleaseBuffer( );


	//分析XML文件
	TiXmlDocument *myDocument = new TiXmlDocument(xmlFileName);
	if (!myDocument->LoadFile())
	{
		sprintf(strReturn,"error=打开xml文件失败，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}
	TiXmlElement *rootElement = myDocument->RootElement();  

	TiXmlElement *nodeElement = rootElement->FirstChildElement(); 
	TiXmlElement *serverElement = nodeElement->FirstChildElement();
	//TiXmlElement *statRootElement = serverElement->FirstChildElement();

	TiXmlElement *statElement = serverElement->FirstChildElement();
	while ((0 != statElement) && (0 != strcmp(statElement->Value(), "transactionModule")))
	{
		statElement = statElement->NextSiblingElement();
	}

	if (0 == statElement)
	{
		sprintf(strReturn,"error=找不到所选项目，请查看配置是否正确$");
		strInput = strReturn;
		MakeCharByString(strReturn, nSize, strInput);
		return FALSE;
	}

	map<string, string> listPerf;
	string strName;
	string strValue;
	TiXmlElement *perfElement = statElement->FirstChildElement();	
	while (0 != perfElement)
	{
		strName = perfElement->Value();
		WriteLog(strName.c_str());
		TiXmlElement* pvalueElement=perfElement->FirstChildElement();

		if (0 != pvalueElement->Attribute("val"))
		{
			strValue = pvalueElement->Attribute("val");
		}
		else if (0 != pvalueElement->Attribute("mean"))
		{
			strValue = pvalueElement->Attribute("mean");
		}
		else
		{
			strValue = "error data";
		}
		listPerf[strName] = strValue;
		WriteLog(strValue.c_str());
		perfElement = perfElement->NextSiblingElement();
	}

	DeleteFile(xmlFileName);

	sprintf(strReturn, "%sglobalTransBegun=%s$", strReturn, listPerf["globalTransBegun"].c_str());

	sprintf(strReturn, "%sglobalTransInvolved=%s$", strReturn, listPerf["globalTransInvolved"].c_str());

	sprintf(strReturn, "%slocalTransBegun=%s$", strReturn, listPerf["localTransBegun"].c_str());

	sprintf(strReturn, "%sactiveGlobalTrans=%s$", strReturn, listPerf["activeGlobalTrans"].c_str());

	sprintf(strReturn, "%sactiveLocalTrans=%s$", strReturn, listPerf["activeLocalTrans"].c_str());

	sprintf(strReturn, "%sglobalTranDuration=%s$", strReturn, listPerf["globalTranDuration"].c_str());


	sprintf(strReturn, "%slocalTranDuration=%s$", strReturn, listPerf["localTranDuration"].c_str());

	sprintf(strReturn, "%sglobalBeforeCompletionDuration=%s$", strReturn, listPerf["globalBeforeCompletionDuration"].c_str());

	sprintf(strReturn, "%sglobalPrepareDuration=%s$", strReturn, listPerf["globalPrepareDuration"].c_str());

	sprintf(strReturn, "%sglobalCommitDuration=%s$", strReturn, listPerf["globalCommitDuration"].c_str());

	sprintf(strReturn, "%slocalBeforeCompletionDuration=%s$", strReturn, listPerf["localBeforeCompletionDuration"].c_str());

	sprintf(strReturn, "%slocalCommitDuration=%s$", strReturn, listPerf["localCommitDuration"].c_str()); 


	sprintf(strReturn, "%snumOptimization=%s$", strReturn, listPerf["numOptimization"].c_str());

	sprintf(strReturn, "%sglobalTransCommitted=%s$", strReturn, listPerf["globalTransCommitted"].c_str());

	sprintf(strReturn, "%slocalTransCommitted=%s$", strReturn, listPerf["localTransCommitted"].c_str());

	sprintf(strReturn, "%sglobalTransRolledBack=%s$", strReturn, listPerf["globalTransRolledBack"].c_str());

	sprintf(strReturn, "%slocalTransRolledBack=%s$", strReturn, listPerf["localTransRolledBack"].c_str());

	sprintf(strReturn, "%sglobalTransTimeout=%s$", strReturn, listPerf["globalTransTimeout"].c_str());

	sprintf(strReturn, "%slocalTransTimeout=%s$", strReturn, listPerf["localTransTimeout"].c_str());

	strInput = strReturn;
	WriteLog(strReturn);
	MakeCharByString(strReturn, nSize, strInput);
	return TRUE;
}