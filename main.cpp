/*
��Ҫ:·�����û�����ϵͳ
date:20190630
author:c.chou
*/

#include<iostream>
#include<string>
#include<Windows.h>
#include <stdio.h>
#include <conio.h>				//getchͷ�ļ�
#include "hacker.h"

using namespace std;

#define WIDTH 40
#define HEIGHT 15

void init(void);										//��ʼ��
void login(void);									//ʵ�ֵ�¼����
void printInMiddle(string);					//������ʾ
void menuShow(void);						//�˵���ʾ
int menuChoice(void);							//����ѡ��
void attack404(void);							//404����
void siteEdit(void);								//��վ�۸Ĺ���
void attackRecord(void);						//��վ������¼
void attackRepair(void);						//��վ�����޸�
void inputPwd(char pwd[] , int size);			//��������

int main(void) {
	init();
	login();							

	while (1) {
		menuShow();
		//���빦�ܱ��
		
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
			cout << "��Ч����,����������:" << endl;
			system("pause");
			break;
		}
	}

	system("pause");
	return 0;
}

void init(void){
	//�����ն˴��ڴ�С
	char cmd[128];
	sprintf_s(cmd, "mode con cols=%d lines=%d", WIDTH, HEIGHT);
	system(cmd);
}

void login(void){
	string name;
	//string pwd;
	char pwd[32];

	while (1) {
		cout << "�������û���" << endl;
		cin >> name;
		cout << "����������" << endl;
		//ʵ����������
		inputPwd(pwd , sizeof(pwd));

		if (name == "54hk" && !strcmp(pwd , "123456")) {
			break;
		}else{
			cout << "�û������������" << endl;
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
	cout << "1.��վ404����" << endl;
	cout << "2.��վ�۸Ĺ���" << endl;
	cout << "3.��վ������¼" << endl;
	cout << "4.�����޸�" << endl;
	cout << "5.�˳�" << endl;
	*/

	string menu[] = {
		"1.��վ404����",
		"2.��վ�۸Ĺ���",
		"3.��վ������¼",
		"4.�����޸�",
		"5.�˳�"
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

	printInMiddle("---�ڿ͹���ϵͳ---");			//��ӡ����

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
		cout << "�����빦�ܱ��:";
		cin >> n;
		if (cin.fail()) {
			cin.clear();
			cin.sync();
			cout << "�������,����������." << endl;
			system("pause");
		}else {
			break;
		}
	}

	return n;
}

void attack404(void){
	/*cout << "404����" << endl;*/
	//int hk_404(char *id, char *response);

	char id[64];								//��վID
	char response[MAXSIZE];		//������ӷ��������ؽ��

	system("cls");

	memset(response, 0, sizeof(response));			//��response��ʼ��Ϊ0

	printInMiddle("--��վ404����--");

	cout << "�����빥����վID";
	scanf_s("%s", id, sizeof(id));

	//���𹥻�
	cout << "���𹥻�" << endl;

	//ע������ʽutf-8��GBK
	hk_404(id, response);

	string retStr = UTF8ToGBK(response);				//���ת��ΪGBK����
	cout << retStr<<endl;

	system("pause");
}

void siteEdit(void) {
	system("cls");
	//cout << "��վ�۸Ĺ���" << endl;
	//��ҳ�۸Ĺ�����para��ʾ�������
	//int hk_tamper(char *id, char *para, char *response);
	char id[64];
	char response[MAXSIZE];
	string attackText;

	printInMiddle("--�۸Ĺ���--");
	cout<<"�������û�id:"<<endl;
	cin>>id;
	cout<<"������۸�����:"<<endl;
	cin>>attackText;

	GBKToUTF8(attackText);											//�������Ĺ������ݻ��������,�Ƚ��б���ת��
	cout<<"����ִ����վ�۸Ĺ���"<<endl;
	hk_tamper(id , (char*)attackText.c_str() , response);					//.c_str()

	string retStr = UTF8ToGBK(response);
	cout<<retStr<<endl;

	system("pause");
}

void attackRecord(void){
	//cout << "��վ������¼" << endl;
	//int hk_record(char *id, char *response);
	char id[64];
	char response[MAXSIZE];

	cout<<"�������ѯ��¼����վid"<<endl;
	scanf_s("%s" , id , sizeof(id));

	system("cls");

	printInMiddle("--��վ������¼--");
	cout<<"���ڲ�ѯ������¼";
	hk_record(id , response);
	
	string str = UTF8ToGBK(response);

	cout<<str<<endl;
	
	system("pause");
}

void attackRepair(void){
	/*system("cls");
	cout << "��վ�����޸�" << endl;*/
	//int hk_restore(char *id, char *response);
	char id[64];
	char response[MAXSIZE];

	cout<<"�������޸���վID:"<<endl;
	//cin>>id;
	scanf_s("%s" , id , sizeof(id));

	system("cls");

	printInMiddle("--��վ�޸�--");
	cout<<"���ڽ�����վ�޸�..."<<endl;
	hk_restore(id , response);

	string str = UTF8ToGBK(response);
	cout<<str<<endl;

	system("pause");
}

void inputPwd(char pwd[] , int size){
	char c;
	int i = 0;
	//����������
	//���浽pwd�� '1'  '2'  '3'  '4'  '5' '6'   �ټ�'\0',���ַ������Ϊ�ַ���������������
	while(1){
		c = getch();			//�������
		
		if(c == '\r' || i > size){				//��������س���,����'\r'
			pwd[i] = 0;
			break;
		}
		pwd[i++] = c;
		cout<<"*";
	}
	cout<<endl;
}