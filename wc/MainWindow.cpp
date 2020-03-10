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
	//��ʼ��
	InitWidgets();

	//���ñ���
	this->setWindowTitle("WordCount");
	this->resize(600, 400);

	//��Ʋ���
	DesignLayout();

	//Ӧ�ò���
	centralWidget->setLayout(layout);
	this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::InitWidgets()
{
	//��ʼ��ȫ���ؼ�
	button = new QPushButton(tr("ѡ���ļ�"));
	path = new QLabel(tr("�ļ�·��:"));

	charactersResult = new QLabel(tr("�ַ���:"));
	wordsResult = new QLabel(tr("������:"));

	blankLinesResult = new QLabel(tr("�հ���:"));
	codeLinesResult = new QLabel("������:");
	commentLinesResult = new QLabel("ע����:");
	linesResult = new QLabel("������:");

	layout = new QVBoxLayout;
	centralWidget = new QWidget;

	//������С��С
	button->setMinimumHeight(70);
	button->resize(70, 120);
	path->setMinimumHeight(30);

	charactersResult->setMinimumHeight(30);
	wordsResult->setMinimumHeight(30);

	blankLinesResult->setMinimumHeight(30);
	codeLinesResult->setMinimumHeight(30);
	commentLinesResult->setMinimumHeight(30);
	linesResult->setMinimumHeight(30);

	//����
	connect(button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));
}

void MainWindow::DesignLayout()
{
	//��Ӱ�ť
	layout->addWidget(button, 0, Qt::Alignment(4));

	//�������
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
	//����Դ����������ȡѡ���·��
	QString strPath = QFileDialog::getOpenFileName(this, 
						"ѡ���ļ�", ".", tr("Text(*.txt *.c *.cpp *.java)"));

	//���·��
	if (!strPath.isEmpty())
	{
		//��ʾ·��
		path->setText("�ļ�·��:" + strPath);

		//ʵ��������
		WordCount *wc = new WordCount(strPath.toStdString());
		
		//������
		charactersResult->setText("�ַ���:" + QString::number(wc->CountCharacters()));
		wordsResult->setText("������:" + QString::number(wc->CountWords()));

		//���
		linesResult->setText("������:" + QString::number(wc->CountDetails()));
		blankLinesResult->setText("�հ���:" + QString::number(wc->blankCount));
		codeLinesResult->setText("������:" + QString::number(wc->codeCount));
		commentLinesResult->setText("ע����:" + QString::number(wc->commentaryCount));

		delete wc;
	}
}

void MainWindow::on_button_clicked()
{
	OpenFile();
}
