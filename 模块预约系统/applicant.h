#pragma once
#include<iostream>
using namespace std;
#include"identity.h"
#include<vector>
#include"Space.h"
#include<fstream>
#include"globalfile.h"
#include"orderFile.h"

//申请人类
class Applicant :public Identity
{
public:
	//默认构造
	Applicant();
	//有参构造 参数：编号 姓名 密码
	Applicant(int id, string name, string pwd);
	//菜单界面
	void operMenu();
	//申请预约
	void applyOrder();
	//查看自身预约
	void showMyOrder();
	//查看所有预约
	void showAllOrder();
	//取消预约
	void cancelOrder();
	//申请人编号
	int m_Id;
	//机房容器
	vector<Space>vSpa;

};