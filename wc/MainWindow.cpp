#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include "WordCount.h"

#include <QSize>
#include <QTextCodec>
#include <QFileDialog>
#include <clocale>
#include <string>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	//初始化
	InitWidgets();

	//设置标题
	this->setWindowTitle("WordCount");
	this->resize(600, 400);

	//设计布局
	DesignLayout();

	//应用布局
	centralWidget->setLayout(layout);
	this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitWidgets()
{
	//初始化全部控件
	button = new QPushButton(tr("选择文件"));
	path = new QLabel(tr("文件路径:"));

	charactersResult = new QLabel(tr("字符数:"));
	wordsResult = new QLabel(tr("单词数:"));

	blankLinesResult = new QLabel(tr("空白行:"));
	codeLinesResult = new QLabel("代码行:");
	commentLinesResult = new QLabel("注释行:");
	linesResult = new QLabel("总行数:");

	layout = new QVBoxLayout;
	centralWidget = new QWidget;

	//设置最小大小
	button->setMinimumHeight(70);
	button->resize(70, 120);
	path->setMinimumHeight(30);

	charactersResult->setMinimumHeight(30);
	wordsResult->setMinimumHeight(30);

	blankLinesResult->setMinimumHeight(30);
	codeLinesResult->setMinimumHeight(30);
	commentLinesResult->setMinimumHeight(30);
	linesResult->setMinimumHeight(30);

	//连接
	connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void MainWindow::DesignLayout()
{
	//添加按钮
	layout->addWidget(button, 0, Qt::Alignment(4));

	//添加文字
	layout->addWidget(path, 0, Qt::Alignment(4));
	layout->addWidget(charactersResult, 0, Qt::Alignment(4));
	layout->addWidget(wordsResult, 0, Qt::Alignment(4));

	layout->addWidget(blankLinesResult, 0, Qt::Alignment(4));
	layout->addWidget(codeLinesResult, 0, Qt::Alignment(4));
	layout->addWidget(commentLinesResult, 0, Qt::Alignment(4));
	layout->addWidget(linesResult, 0, Qt::Alignment(4));
}

void MainWindow::OpenFile()
{
	//打开资源管理器并获取选择的路径
	QString strPath = QFileDialog::getOpenFileName(this, 
						"选择文件", ".", tr("Text(*.txt *.c *.cpp *.java)"));

	//检查路径
	if (!strPath.isEmpty())
	{
		//显示路径
		path->setText("文件路径:" + strPath);

		//实例化对象
		WordCount *wc = new WordCount(strPath.toStdString());
		
		//输出结果
		charactersResult->setText("字符数:" + QString::number(wc->CountCharacters()));
		wordsResult->setText("单词数:" + QString::number(wc->CountWords()));

		//输出
		linesResult->setText("总行数:" + QString::number(wc->CountDetails()));
		blankLinesResult->setText("空白行:" + QString::number(wc->blankCount));
		codeLinesResult->setText("代码行:" + QString::number(wc->codeCount));
		commentLinesResult->setText("注释行:" + QString::number(wc->commentaryCount));

		delete wc;
	}
}

void MainWindow::on_button_clicked()
{
	OpenFile();
}
