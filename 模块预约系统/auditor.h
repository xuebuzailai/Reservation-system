#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include"orderFile.h"
#include<vector>
//��ʦ�����
class Auditor : public Identity
{
public:
	//Ĭ�Ϲ���
	Auditor();
	//�вι���
	Auditor(int audId, string name, string pwd);
	//�˵�����
	void operMenu();

	//�鿴����ԤԼ
	void showAllOrder();
	//���ԤԼ
	void validOrder();
	//���Ա���
	int m_AudId;
};