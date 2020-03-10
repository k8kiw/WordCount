#include "WordCount.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

WordCount::WordCount(std::string path) 
	: m_Path(path), blankCount(0), codeCount(0), commentaryCount(0)
{
	//����·�����ļ�
	m_File.open(m_Path, ios::in);

	//��֤��
	if (m_File.is_open())
	{
		cout << "�Ѵ��ļ�" << m_Path << endl << endl;
	}
	else
	{
		//cerr << "���ļ�ʧ��" << endl << endl;
		//������Ҫ�׳��쳣����Ῠ��
		throw 1;
	}

}

WordCount::~WordCount()
{
	//��������ʱ�ر��ļ�
	m_File.close();
}

int WordCount::CountCharacters()
{
	int count = 0;

	char c;
	while (!m_File.eof())	//����
	{
		//ÿ��ȡһ���ַ��ͼ���һ��
		m_File >> c;
		count++;
	}

	//�ص��ļ�ͷ����ֹ��һ�ε��õ�ʱ���޷���ȡ���ļ�
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountWords()
{
	int count = 0;

	string str;
	while (!m_File.eof())	//����
	{
		//ÿ��ȡһ�����ʾͼ���һ��
		m_File >> str;		//iostream�������Ĭ�Ϻ��Կո�
		count++;
	}

	//�ص��ļ�ͷ����ֹ��һ�ε��õ�ʱ���޷���ȡ���ļ�
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountLines()
{
	int count = 0;

	string str;
	while (!m_File.eof())	//����
	{
		//ÿ��ȡһ�оͼ���һ��
		getline(m_File, str);
		count++;
	}

	//�ص��ļ�ͷ����ֹ��һ�ε��õ�ʱ���޷���ȡ���ļ�
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountDetails()
{
	string str;				//���ڱ�����ȡ������

	int count = 0;			//������

	while (!m_File.eof())	//�����ļ�
	{
		//��ȡһ�н��з���
		getline(m_File, str);
		count++;

		//����string
		string::iterator ite;
		int flag = 0;			//���
		for (ite = str.begin(); ite != str.end(); ite++)
		{
			//�հ��ַ� or ������һ���ַ� --> ����
			//flag = 0	  flag = 1
			//����Ϊ�ַ��� ��Ϊ//..... --> ע����
			//			   ����Ϊ������
			if (flag == 0 && isspace(*ite))			//һֱ���ǿհ�
			{
				flag = 0;
			}
			else if (flag == 0 && isgraph(*ite))	//������һ���ַ�
			{
				flag = 1;
			}
			else if (flag == 1 && isspace(*ite))	//���ַ���Ϊ�հ�
			{
				flag = 1;
			}
			else if (flag == 1 && isgraph(*ite))	//�ڶ����ַ�
			{
				if (*ite == '/')
					flag = 3;
				else
					flag = 2;
			}

		}	//for

		//����flag��������м���
		if (flag == 0 || flag == 1)
			blankCount++;
		else if (flag == 2)
			codeCount++;
		else
			commentaryCount++;
	}	//while

	//����������
	cout << "�ļ�" << m_Path << "�Ŀհ�����:" << blankCount << endl;
	cout << "�ļ�" << m_Path << "�Ĵ�������:" << codeCount << endl;
	cout << "�ļ�" << m_Path << "��ע������:" << commentaryCount << endl;

	//�ص��ļ�ͷ����ֹ��һ�ε��õ�ʱ���޷���ȡ���ļ�
	m_File.clear();
	m_File.seekg(0);
	return count;
}
