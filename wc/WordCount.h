#pragma once

#include <fstream>
#include <string>

using namespace std;

class WordCount
{
public:
	WordCount(std::string path);
	~WordCount();

private:
	std::string m_Path;		//�ļ�·��
	std::fstream m_File;	//���ļ���

public:
	int CountCharacters();	//�����ַ�
	int CountWords();		//�������
	int CountLines();		//��������
	int CountDetails();		//����ϸ��

public:
	//����CountDetails�ڵ����ݣ��ⲿֱ������
	int blankCount;		//�հ���
	int codeCount;		//������
	int commentaryCount;//ע����
};