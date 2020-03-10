#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	//布局中的控件
	QPushButton *button;		//按钮触发后选择文件
	QLabel *path;				//显示路径
	QLabel *charactersResult;	//字符结果
	QLabel *wordsResult;		//单词结果
	QLabel *blankLinesResult;	//空白行
	QLabel *codeLinesResult;	//代码行
	QLabel *commentLinesResult;	//注释行
	QLabel *linesResult;		//总行

	//布局
	QVBoxLayout *layout;		//竖直布局
	QWidget *centralWidget;		//主窗口

private slots:
	void on_button_clicked();	//按键的槽函数

public:
	void InitWidgets();			//初始化
	void DesignLayout();		//设计布局
	void OpenFile();			//打开文件
};
