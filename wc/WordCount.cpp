#include "WordCount.h"

#include <iostream>
#include <string>
#include <cctype>
#include <regex>

using namespace std;

WordCount::WordCount(std::string path) 
	: m_Path(path), blankCount(0), codeCount(0), commentaryCount(0)
{
	//根据路径打开文件
	m_File.open(m_Path, ios::in);

	//验证打开
	if (m_File.is_open())
	{
		std::cout << "已打开文件" << m_Path << endl << endl;
	}
	else
	{
		//cerr << "打开文件失败" << endl << endl;
		//这里需要抛出异常否则会卡死
		throw 1;
	}

}

WordCount::~WordCount()
{
	//对象销毁时关闭文件
	m_File.close();
}

int WordCount::CountCharacters()
{
	int count = 0;

	char c;
	while (!m_File.eof())	//遍历
	{
		//每读取一个字符就计数一次
		m_File >> c;
		if (isgraph(c))
		{
			count++;
			c = '\0';
		}
	}

	//回到文件头，准备下一次使用
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountWords()
{
	int count = 0;

	string str;
	while (!m_File.eof())	//遍历
	{
		//每读取一个单词就计数一次
		m_File >> str;		//iostream的运算符默认忽略空格
		if (regex_search(str, regex("[a-zA-Z]+\\b")))		//正则表达式匹配
		{
			count++;
		}
	}

	//回到文件头，防止下一次调用的时候无法读取该文件
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountLines()
{
	int count = 0;

	string str;
	while (!m_File.eof())	//遍历
	{
		//每读取一行就计数一次
		getline(m_File, str);
		count++;
	}

	//回到文件头，防止下一次调用的时候无法读取该文件
	m_File.clear();
	m_File.seekg(0);
	return count;
}

int WordCount::CountDetails()
{
	string str;				//用于保存提取出的行

	int count = 0;			//总行数

	while (!m_File.eof())	//遍历文件
	{
		//读取一行进行分析
		getline(m_File, str);
		count++;

		//遍历string
		string::iterator ite;
		int flag = 0;			//标记
		for (ite = str.begin(); ite != str.end(); ite++)
		{
			//空白字符 or 仅含有{  --> 空行
			//flag = 0	  flag = 1
			//否则为字符行 若为//..... --> 注释行
			//			   否则为代码行
			if (flag == 0 && isspace(*ite))			//一直都是空白
			{
				flag = 0;
			}
			else if (flag == 0 && isgraph(*ite))	//遇到第一个字符
			{
				if ((*ite) == '{' || (*ite) == '}')	//大括号标记为1否则为代码行
					flag = 1;
				else if ((*ite) == '/')
					flag = 3;
				else
					flag = 2;
			}
			else if (flag == 1 && isspace(*ite))	//该字符后都为空白
			{
				flag = 1;
			}
			else if (flag == 1 && isgraph(*ite))	//第二个字符
			{
				//如果是注释行 无论有没有大括号 第二个字符都为/
				if (*ite == '/')
					flag = 3;
				else
					flag = 2;
			}
			
		}	//for

		//根据flag的情况进行计数
		if (flag == 0 || flag == 1)
			blankCount++;
		else if (flag == 2)
			codeCount++;
		else
			commentaryCount++;
	}	//while

	//计数完毕输出
	std::cout << "文件" << m_Path << "的空白行数:" << blankCount << endl;
	std::cout << "文件" << m_Path << "的代码行数:" << codeCount << endl;
	std::cout << "文件" << m_Path << "的注释行数:" << commentaryCount << endl;

	//回到文件头，防止下一次调用的时候无法读取该文件
	m_File.clear();
	m_File.seekg(0);
	return count;
}
