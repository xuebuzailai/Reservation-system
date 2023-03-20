#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include"orderFile.h"
#include<vector>
//教师类设计
class Auditor : public Identity
{
public:
	//默认构造
	Auditor();
	//有参构造
	Auditor(int audId, string name, string pwd);
	//菜单界面
	void operMenu();

	//查看所有预约
	void showAllOrder();
	//审核预约
	void validOrder();
	//审核员编号
	int m_AudId;
};