#pragma once
#include<iostream>
using namespace std;
#include"globalfile.h"
#include<fstream>
#include<map>

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();
	void getMap(string& word, map<string, string>& m);

	void showAllOrder();


	//��¼ԤԼ����
	int m_Size;

	//��¼����ԤԼ��Ϣ������ key��¼���� value�����¼��ֵ����Ϣ
	map<int, map<string, string>>m_OrderData;
};