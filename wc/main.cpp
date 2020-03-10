#include "MainWindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <Windows.h>		//ʹ��FindFirstFile��֧��ͨ�������

#include "WordCount.h"

using namespace std;

//����ѡ����ļ�����
void CountFile(string option, string path)
{
	try
	{
		WordCount *wc = new WordCount(path.c_str());	//���ɶ���

		if (option == "-c")				//�����ַ�
		{
			cout << "�ļ�" + path + "���ַ���Ϊ:" << wc->CountCharacters() << endl << endl;
		}
		else if (option == "-w")		//���㵥��
		{
			cout << "�ļ�" + path + "�ĵ�����Ϊ:" << wc->CountWords() << endl << endl;
		}
		else if (option == "-l")		//��������
		{
			cout << "�ļ�" + path + "������Ϊ:" << wc->CountLines() << endl << endl;
		}
		else if (option == "-a")		//��ϸ����
		{
			int lines = wc->CountDetails();
			cout << "�ļ�" + path + "��������Ϊ:" << lines << endl << endl;
		}
		else
		{
			cout << "û��" + option + "ѡ��!������" << endl;
		}

		delete wc;
	}
	catch (int)		//�����쳣 ��û�гɹ����ļ����µĿ���
	{
		cerr << "���ļ�ʧ��" << endl;
	}

}

//wide char to string
char* wideCharToMultiByte(wchar_t* pWCStrKey)
{
	//��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	//�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
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

//ͨ��������ļ�
void SearchFile(string option, string path)
{
	WIN32_FIND_DATA pFileData;

	//������һ���ļ�
	HANDLE hFile = FindFirstFile(stringToLPCWSTR(path), &pFileData);
	if (hFile == INVALID_HANDLE_VALUE)
		cout << "����ʧ��" << endl;
	else
		CountFile(option, wideCharToMultiByte(pFileData.cFileName));

	//ʣ�µ��ļ�
	while (FindNextFile(hFile, &pFileData))
	{
		//����
		if (pFileData.cFileName[0] == '.' || pFileData.cFileName[0] == '..')
			continue;

		//�ݹ�ɨ����Ŀ¼
		/*if (pFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//�ļ���תstring
			string fileName = pFileData.cFileName;
			//ȡ����Ŀ¼·��
			string nextPath = path;
			nextPath += "\\";
			nextPath += fileName;
			//�ݹ�
			SearchFile(option, nextPath);
		}
		else*/
		CountFile(option, wideCharToMultiByte(pFileData.cFileName));
	}
}

int main(int argc, char *argv[])
{
	//-c �����ַ���		-w ���شʵ���Ŀ		-l ��������

	//-s ����Ŀ¼�����з���Ҫ����ļ�
	//-a ����(�ջ�ֻ�� { ) /������(����һ���ַ�) /ע����(�Ǵ������Һ�ע��)
	//֧��ͨ���(*,?)

	if (argc < 2)
	{
		cerr << "���������!" << endl;
	}
	else if (argc == 2)
	{
		string option = argv[1];
		//��gui
		if (option == "-x")
		{
			QApplication a(argc, argv);
			MainWindow w;
			w.show();
			cout << "GUI�����Ѵ�" << endl;
			return a.exec();
		}
		else
			cerr << "������·��!" << endl;
	}
	else	//argc > 2
	{
		string option = argv[1];		//ѡ��
		string path = argv[2];			//·��

		bool flag = false;				//��־���� -s
		if (option == "-s" || path == "-s")
		{
			//����������
			if (argc == 3)
			{
				cerr << "�����������Ĳ���!(��: -s -a *.c)" << endl;
				system("pause");
				return 0;
			}
			//-s��ǰ
			if (option == "-s")
				option = argv[2];

			path = argv[3];				//·���������һ������
			flag = true;				//�� -s
		}

		if (flag == false)
		{
			CountFile(option, path);
		}
		else	//��ͨ���
		{
			SearchFile(option, path);
		}
	}

	system("pause");
	return 0;
}
