#pragma once

#include <fstream>

class WordCount
{
public:
	WordCount(const char *path);
	~WordCount();

private:
	const char * m_Path;	//文件路径
	std::fstream m_File;	//读文件流

public:
	int CountCharacters();	//计算字符
	int CountWords();		//计算词数
	int CountLines();		//计算行数
	int CountDetails();		//计算细节
};