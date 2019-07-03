/*
需要:路由器用户管理系统
date:20190630
author:c.chou
*/

#include<iostream>
#include<string>
#include<Windows.h>
#include <stdio.h>
#include <conio.h>				//getch头文件
#include "hacker.h"

using namespace std;

#define WIDTH 40
#define HEIGHT 15

void init(void);										//初始化
void login(void);									//实现登录功能
void printInMiddle(string);					//居中显示
void menuShow(void);						//菜单显示
int menuChoice(void);							//功能选择
void attack404(void);							//404攻击
void siteEdit(void);								//网站篡改攻击
void attackRecord(void);						//网站攻击记录
void attackRepair(void);						//网站攻击修复
void inputPwd(char pwd[] , int size);			//密码输入

int main(void) {
	init();
	login();							

	while (1) {
		menuShow();
		//输入功能编号
		
		int n = menuChoice();

		switch (n){
		case 1:
			attack404();
			break;
		case 2:
			siteEdit();
			break;
		case 3:
			attackRecord();
			break;
		case 4:
			attackRepair();
			break;
		case 5:
			return 0;
		default:
			cout << "无效输入,请重新输入:" << endl;
			system("pause");
			break;
		}
	}

	system("pause");
	return 0;
}

void init(void){
	//设置终端窗口大小
	char cmd[128];
	sprintf_s(cmd, "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(cmd);
}

void login(void){
	string name;
	//string pwd;
	char pwd[32];

	while (1) {
		cout << "请输入用户名" << endl;
		cin >> name;
		cout << "请输入密码" << endl;
		//实现密码输入
		inputPwd(pwd , sizeof(pwd));

		if (name == "54hk" && !strcmp(pwd , "123456")) {
			break;
		}else{
			cout << "用户名或密码错误" << endl;
			//system("pause");
			Sleep(1000);
			system("cls");
		}
	}
}

void printInMiddle(string msg){
	int leftspace = (WIDTH - msg.length())/2;
	for (int i = 0; i < leftspace; i++) {
		cout << " ";
	}
	cout << msg << endl;
}

void menuShow(void){
	/*
	system("cls");
	cout << "1.网站404攻击" << endl;
	cout << "2.网站篡改攻击" << endl;
	cout << "3.网站攻击记录" << endl;
	cout << "4.攻击修复" << endl;
	cout << "5.退出" << endl;
	*/

	string menu[] = {
		"1.网站404攻击",
		"2.网站篡改攻击",
		"3.网站攻击记录",
		"4.攻击修复",
		"5.退出"
	};

	int max = 0;
	int menuCount = sizeof(menu) / sizeof(menu[0]);
	for ( int i = 0; i < menuCount; i++) {
		if (menu[i].length() > max) {
			max = menu[i].length();
		}
	}

	int leftSpace = (WIDTH - max) / 2;
	int linespace = (HEIGHT - menuCount -1) / 2;
	
	system("cls");

	for (int i = 0; i < linespace; i++) {
		cout << endl;
	}

	printInMiddle("---黑客攻击系统---");			//打印标题

	for (int i = 0; i < menuCount; i++) {
		for (int i = 0; i < leftSpace; i++) {
			cout << " ";
		}
		cout << menu[i] << endl;
	}
}

int menuChoice(void){
	int n = 0;

	while (1) {
		cout << "请输入功能编号:";
		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cout << "输入错误,请重新输入." << endl;
			system("pause");
		}else {
			break;
		}
	}

	return n;
}

void attack404(void){
	/*cout << "404攻击" << endl;*/
	//int hk_404(char *id, char *response);

	char id[64];								//网站ID
	char response[MAXSIZE];		//攻击后从服务器返回结果

	system("cls");

	memset(response, 0, sizeof(response));			//将response初始化为0

	printInMiddle("--网站404攻击--");

	cout << "请输入攻击网站ID";
	scanf_s("%s", id, sizeof(id));

	//发起攻击
	cout << "发起攻击" << endl;

	//注意编码格式utf-8与GBK
	hk_404(id, response);

	string retStr = UTF8ToGBK(response);				//结果转换为GBK编码
	cout << retStr<<endl;

	system("pause");
}

void siteEdit(void) {
	system("cls");
	//cout << "网站篡改攻击" << endl;
	//网页篡改攻击，para表示填充内容
	//int hk_tamper(char *id, char *para, char *response);
	char id[64];
	char response[MAXSIZE];
	string attackText;

	printInMiddle("--篡改攻击--");
	cout<<"请输入用户id:"<<endl;
	cin>>id;
	cout<<"请输入篡改内容:"<<endl;
	cin>>attackText;

	GBKToUTF8(attackText);											//输入中文攻击内容会出现乱码,先进行编码转化
	cout<<"正在执行网站篡改攻击"<<endl;
	hk_tamper(id , (char*)attackText.c_str() , response);					//.c_str()

	string retStr = UTF8ToGBK(response);
	cout<<retStr<<endl;

	system("pause");
}

void attackRecord(void){
	//cout << "网站攻击记录" << endl;
	//int hk_record(char *id, char *response);
	char id[64];
	char response[MAXSIZE];

	cout<<"请输入查询记录的网站id"<<endl;
	scanf_s("%s" , id , sizeof(id));

	system("cls");

	printInMiddle("--网站攻击记录--");
	cout<<"正在查询攻击记录";
	hk_record(id , response);
	
	string str = UTF8ToGBK(response);

	cout<<str<<endl;
	
	system("pause");
}

void attackRepair(void){
	/*system("cls");
	cout << "网站攻击修复" << endl;*/
	//int hk_restore(char *id, char *response);
	char id[64];
	char response[MAXSIZE];

	cout<<"请输入修复网站ID:"<<endl;
	//cin>>id;
	scanf_s("%s" , id , sizeof(id));

	system("cls");

	printInMiddle("--网站修复--");
	cout<<"正在进行网站修复..."<<endl;
	hk_restore(id , response);

	string str = UTF8ToGBK(response);
	cout<<str<<endl;

	system("pause");
}

void inputPwd(char pwd[] , int size){
	char c;
	int i = 0;
	//请输入密码
	//保存到pwd中 '1'  '2'  '3'  '4'  '5' '6'   再加'\0',由字符数组变为字符串用起来更方便
	while(1){
		c = getch();			//不会回显
		
		if(c == '\r' || i > size){				//如果读到回车符,返回'\r'
			pwd[i] = 0;
			break;
		}
		pwd[i++] = c;
		cout<<"*";
	}
	cout<<endl;
}