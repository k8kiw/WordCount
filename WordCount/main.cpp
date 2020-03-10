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

//ͨ��������ļ�
void SearchFile(string option, string path)
{
	WIN32_FIND_DATA pFileData;

	//������һ���ļ�
	HANDLE hFile = FindFirstFile(path.c_str(), &pFileData);
	if (hFile == INVALID_HANDLE_VALUE)
		cout << "����ʧ��" << endl;
	else
		CountFile(option, pFileData.cFileName);

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
			CountFile(option, pFileData.cFileName);
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
