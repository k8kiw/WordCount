#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>		//使用FindFirstFile来支持通配符搜索

#include "WordCount.h"

using namespace std;

//根据选项对文件计数
void CountFile(string option, string path)
{
	try
	{
		WordCount *wc = new WordCount(path.c_str());	//生成对象

		if (option == "-c")				//计算字符
		{
			cout << "文件" + path + "的字符数为:" << wc->CountCharacters() << endl << endl;
		}
		else if (option == "-w")		//计算单词
		{
			cout << "文件" + path + "的单词数为:" << wc->CountWords() << endl << endl;
		}
		else if (option == "-l")		//计算行数
		{
			cout << "文件" + path + "的行数为:" << wc->CountLines() << endl << endl;
		}
		else if (option == "-a")		//详细行数
		{
			int lines = wc->CountDetails();
			cout << "文件" + path + "的总行数为:" << lines << endl << endl;
		}
		else
		{
			cout << "没有" + option + "选项!请重试" << endl;
		}

		delete wc;
	}
	catch (int)		//处理异常 即没有成功打开文件导致的卡死
	{
		cerr << "打开文件失败" << endl;
	}

}

//wide char to string
char* wideCharToMultiByte(wchar_t* pWCStrKey)
{
	//第一次调用确认转换后单字节字符串的长度，用于开辟空间
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	//第二次调用将双字节字符串转换成单字节字符串
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	return pCStrKey;

}

//string to LPCWSTR
LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

//通配符搜索文件
void SearchFile(string option, string path)
{
	WIN32_FIND_DATA pFileData;

	//搜索第一个文件
	HANDLE hFile = FindFirstFile(stringToLPCWSTR(path), &pFileData);
	if (hFile == INVALID_HANDLE_VALUE)
		cout << "查找失败" << endl;
	else
		CountFile(option, wideCharToMultiByte(pFileData.cFileName));

	//剩下的文件
	while (FindNextFile(hFile, &pFileData))
	{
		//过滤
		if (pFileData.cFileName[0] == '.' || pFileData.cFileName[0] == '..')
			continue;

		//递归扫描子目录
		/*if (pFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//文件名转string
			string fileName = pFileData.cFileName;
			//取得子目录路径
			string nextPath = path;
			nextPath += "\\";
			nextPath += fileName;
			//递归
			SearchFile(option, nextPath);
		}
		else*/
		CountFile(option, wideCharToMultiByte(pFileData.cFileName));
	}
}

int main(int argc, char *argv[])
{
	//-c 返回字符数		-w 返回词的数目		-l 返回行数

	//-s 处理目录下所有符合要求的文件
	//-a 空行(空或只有 { ) /代码行(大于一个字符) /注释行(非代码行且含注释)
	//支持通配符(*,?)

	if (argc < 2)
	{
		cerr << "请输入参数!" << endl;
	}
	else if (argc == 2)
	{
		string option = argv[1];
		//打开gui
		if (option == "-x")
		{
			QApplication a(argc, argv);
			MainWindow w;
			w.show();
			cout << "GUI界面已打开" << endl;
			return a.exec();
		}
		else
			cerr << "请输入路径!" << endl;
	}
	else	//argc > 2
	{
		string option = argv[1];		//选项
		string path = argv[2];			//路径

		bool flag = false;				//标志有无 -s
		if (option == "-s" || path == "-s")
		{
			//参数不完整
			if (argc == 3)
			{
				cerr << "请输入完整的参数!(如: -s -a *.c)" << endl;
				system("pause");
				return 0;
			}
			//-s在前
			if (option == "-s")
				option = argv[2];

			path = argv[3];				//路径总是最后一个参数
			flag = true;				//有 -s
		}

		if (flag == false)
		{
			CountFile(option, path);
		}
		else	//有通配符
		{
			SearchFile(option, path);
		}
	}

	system("pause");
	return 0;
}
