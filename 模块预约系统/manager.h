#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<fstream>
#include"globalfile.h"
#include<vector>


#include<algorithm>
#include"Space.h"
#include"applicant.h"
#include"auditor.h"

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);


	//�˵�����
	void operMenu();

	//����˺�
	void addPerson();
	//�鿴�˺�
	void showPerson();
	//�鿴�ռ���Ϣ
	void showSpace();
	//���ԤԼϵͳ
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ� ����һ ��������˱��/���Ա��� ������ �������
	bool checkRepeat(int id, int type);

	//����������
	vector<Applicant>vApp;

	//���Ա����

	vector<Auditor>vAud;

	//�ռ���Ϣ����
	vector<Space>vSpa;


};