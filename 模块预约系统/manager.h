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
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);


	//菜单界面
	void operMenu();

	//添加账号
	void addPerson();
	//查看账号
	void showPerson();
	//查看空间信息
	void showSpace();
	//清空预约系统
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复 参数一 检测申请人编号/审核员编号 参数二 检测类型
	bool checkRepeat(int id, int type);

	//申请人容器
	vector<Applicant>vApp;

	//审核员容器

	vector<Auditor>vAud;

	//空间信息容器
	vector<Space>vSpa;


};