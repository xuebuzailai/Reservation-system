#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"Space.h"
#include<fstream>
#include"globalfile.h"
#include"orderFile.h"

//��������
class Applicant :public Identity
{
public:
	//Ĭ�Ϲ���
	Applicant();
	//�вι��� ��������� ���� ����
	Applicant(int id, string name, string pwd);
	//�˵�����
	void operMenu();
	//����ԤԼ
	void applyOrder();
	//�鿴����ԤԼ
	void showMyOrder();
	//�鿴����ԤԼ
	void showAllOrder();
	//ȡ��ԤԼ
	void cancelOrder();
	//�����˱��
	int m_Id;
	//��������
	vector<Space>vSpa;

};