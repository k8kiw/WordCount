#pragma once

#include <fstream>

class WordCount
{
public:
	WordCount(const char *path);
	~WordCount();

private:
	const char * m_Path;	//�ļ�·��
	std::fstream m_File;	//���ļ���

public:
	int CountCharacters();	//�����ַ�
	int CountWords();		//�������
	int CountLines();		//��������
	int CountDetails();		//����ϸ��
};