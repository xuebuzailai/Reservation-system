#include"manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{

    //初始化管理员信息
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化容器 并且获取到所有文件中 申请人、审核员信息
    this->initVector();

     //初始化机房信息
    ifstream ifs;
    ifs.open(SPACE_FILE, ios::in);
    Space spa;
    while (ifs >> spa.m_SId && ifs >> spa.m_MaxNum)
    {
        this->vSpa.push_back(spa);

    }
    ifs.close();
    cout << "空间数量为：" << vSpa.size() << endl;

}


//菜单界面
void Manager::operMenu()
{
    cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.添加账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.查看账号            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.查看空间            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.清空预约            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.注销登录            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

//添加账号
void Manager::addPerson()
{
    cout << "请输入添加账号类型" << endl;
    cout << "1、添加申请人" << endl;
    cout << "2、添加审核员" << endl;

    string fileName;//操作文件名
    string tip;//提示id号
    ofstream ofs;//文件操作对象
    string errorTip;//重复错误提示

    int select = 0;
    cin >> select;//接受用户的选项

    if (select == 1)
    {
        //添加学生

        fileName = APPLICANT_FILE;
        tip = "请输入申请编号：";
        errorTip = "申请编号重复，请重新输入";

    }
    else if(select==2)
    {
        fileName = AUDITOR_FILE;
        tip = "请输入审核编号：";
        errorTip = "审核编号重复，请重新输入";

    }
    else
    {
        cout << "输入有误，请重新输入" << endl;
        system("pause");
        system("cls");
        return;
    }
    //利用追加的方式 写文件
    ofs.open(fileName, ios::out | ios::app);
    int id;//申请编号或者审核编号
    string name;//姓名
    string pwd;//密码

    cout << tip << endl;
    while (true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)//有重复
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }

    }

    cout << "请输入姓名：" << endl;
    cin >> name;
    cout << "请输入登录密码：" << endl;
    cin >> pwd;

       //向文件中添加数据
    ofs << id << " " << name << " " << pwd << endl;

    cout << "添加成功" << endl;
    system("pause");
    system("cls");
    ofs.close();


    //调用初始化容器接口，重新获取文件中的数据
    this->initVector();


}
void printApplicant(Applicant& a)
{
    cout<< "申请编号：" << a.m_Id << "姓名：" << a.m_Name << "密码：" << a.m_Pwd << endl;
}
void printAuditor(Auditor& Au)
{
    cout << "审核编号：" << Au.m_AudId << "姓名：" << Au.m_Name << "密码：" << Au.m_Pwd << endl;
}
//查看账号
void Manager::showPerson()
{

    cout << "请选择查看内容:" << endl;
    cout << "1、查看所有申请人" << endl;
    cout << "2、查看所有审核员" << endl;
    int select = 0;//接受用户选择
    cin >> select;
    if (select == 1)
    {
        //查看申请人
        if (vApp.size() == 0)
        {
            cout << "无申请人信息" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "所有申请人信息如下：" << endl;
            for_each(vApp.begin(), vApp.end(), printApplicant);
        }
    }
    else if(select==2)
    {
        //查看审核员
        if (vAud.size() == 0)
        {
            cout << "无审核员信息" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "所有审核员信息如下：" << endl;
            for_each(vAud.begin(), vAud.end(), printAuditor);
        }
    }
    else
    {
        cout << "输入有误，请重新输入" << endl;
        system("pause");
        system("cls");
        return;
    }
    system("pause");
    system("cls");
}
//查看空间信息
void Manager::showSpace()
{
    cout << "空间信息如下：" << endl;
    for (vector<Space>::iterator it = vSpa.begin(); it != vSpa.end(); it++)
    {
        cout << "空间编号：" << it->m_SId << " 空间最大容量:" << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}
//清空预约系统
void Manager::cleanFile()
{
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::trunc);
    ofs.close();
    cout << "清空成功！" << endl;
    system("pause");
    system("cls");
}


//初始化容器
void Manager::initVector()
{

    //确保容器清空状态
    vApp.clear();
    vAud.clear();
    //读取信息 申请人
    ifstream ifs;
    ifs.open(APPLICANT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    Applicant a;
    while (ifs >> a.m_Id && ifs >> a.m_Name && ifs >> a.m_Pwd)
    {
        vApp.push_back(a);
    }
    cout << "当前申请人数量为：" << vApp.size() << endl;
    ifs.close();

    //读取信息 审核员
    ifs.open(AUDITOR_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件读取失败" << endl;
        return;
    }
    Auditor AU;
    while (ifs >> AU.m_AudId && ifs >> AU.m_Name && ifs >> AU.m_Pwd)
    {
        vAud.push_back(AU);
    }
    cout << "当前审核员的数量：" << vAud.size() << endl;
    ifs.close();



}


//检测重复 参数一 检测申请人编号/审核员编号 参数二 检测类型
bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        //检测申请人
        for (vector<Applicant>::iterator it = vApp.begin(); it != vApp.end(); it++)
        {
            if (id == it->m_Id)

            {
                return true;
            }

        }
    }
    else
    {
        //检测审核员
        for (vector<Auditor>::iterator it = vAud.begin(); it != vAud.end(); it++)
        {
            if (id == it->m_AudId)
            {
                return true;
            }
        }
    }


    return false;
}
