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
	std::string m_Path;		//文件路径
	std::fstream m_File;	//读文件流

public:
	int CountCharacters();	//计算字符
	int CountWords();		//计算词数
	int CountLines();		//计算行数
	int CountDetails();		//计算细节

public:
	//保存CountDetails内的数据，外部直接引用
	int blankCount;		//空白行
	int codeCount;		//代码行
	int commentaryCount;//注释行
};