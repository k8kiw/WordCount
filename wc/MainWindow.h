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
	//�����еĿؼ�
	QPushButton *button;		//��ť������ѡ���ļ�
	QLabel *path;				//��ʾ·��
	QLabel *charactersResult;	//�ַ����
	QLabel *wordsResult;		//���ʽ��
	QLabel *blankLinesResult;	//�հ���
	QLabel *codeLinesResult;	//������
	QLabel *commentLinesResult;	//ע����
	QLabel *linesResult;		//����

	//����
	QVBoxLayout *layout;		//��ֱ����
	QWidget *centralWidget;		//������

private slots:
	void on_button_clicked();	//�����Ĳۺ���

public:
	void InitWidgets();			//��ʼ��
	void DesignLayout();		//��Ʋ���
	void OpenFile();			//���ļ�
};
