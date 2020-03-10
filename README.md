## WordCount

​		基于命令行参数对选择的文件进行计数。



## 使用方式

​		命令行参数调用。程序处理用户需求的模式为：

​		wc.exe [parameter] [file_name]

 

​		wc.exe -c file.c  	//返回文件 file.c 的字符数

​		wc.exe -w file.c 	//返回文件 file.c 的词的数目  

​		wc.exe -l file.c   	//返回文件 file.c 的行数

​		wc.exe -a file.c  	//返回文件 file.c 的空白行、代码行、注释行

​		wc.exe -s -a *.c 	//可使用通配符

​		wc.exe -x		  //呼出GUI界面

 