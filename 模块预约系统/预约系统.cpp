#include<iostream>
using namespace std;
#include"identity.h"
#include<fstream>
#include<string>
#include"globalfile.h"
#include"applicant.h"
#include"auditor.h"
#include"manager.h"

//进入管理员子菜单界面
void managerMenu(Identity*& manager)//identity*格式的 可引用改外值的 manager指针
{
    while (true)
    {
        //调用管理员子菜单
        manager->operMenu();
        //将父类指针转为子类指针，调用子类里其他接口
        Manager* man = (Manager*)manager;//初始化 

        int select = 0;
        //接受用户选项

        cin >> select;
        if (select == 1)//添加账号
        {
           
            man->addPerson();

        }
        else if (select == 2)//查看账号
        {
           
            man->showPerson();
        }
        else if (select == 3)//查看空间
        {
            
            man->showSpace();
        }

        else if (select == 4)//清空预约
        {
           
            man->cleanFile();
        }
        else
        {
            //注销
            delete manager;//销毁掉堆区对象
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//进入申请人子菜单界面
void applicantMenu(Identity*& applicant)
{
    while (true)
    {
        //调用申请人子菜单
        applicant->operMenu();
        Applicant* app = (Applicant*)applicant;//stu临时指针
        int select = 0;
        cin >> select;//接受用户选择
        if (select == 1)//申请预约
        {
            app->applyOrder();
        }
        else if (select == 2)//查看自身预约
        {
            app->showMyOrder();
        }
        else if (select == 3)//查看所有人预约
        {
            app->showAllOrder();
        }
        else if (select == 4)//取消预约
        {
            app->cancelOrder();
        }
        else
        {
            //注销登录
            delete applicant;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//进入审核员子菜单界面
void auditorMenu(Identity*& auditor)
{
    while (true)
    {
        //调用子菜单界面
        auditor->operMenu();
        Auditor* aud = (Auditor*)auditor;
        int select = 0;//接受用户选择
        cin >> select;
        if (select == 1)//查看所有预约
        {
            aud->showAllOrder();
        }
        else if (select == 2)//审核预约
        {
            aud->validOrder();
        }
        else
        {
            delete auditor;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}


//登录功能 参数一 操作文件名 参数二操作身份类型
void LoginIn(string fileName, int type)
{
    //父类指针，用于指向子类对象
    Identity* person = NULL;

    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);
    //判断文件是否存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        system("pause");
        system("cls");
        return;
    }
    //准备接受用户信息
    int id = 0;
    string name;
    string pwd;

    //判断身份
    if (type == 1)//申请人身份
    {
        cout << "请输入你的申请编号：" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "请输入您的审核编号:" << endl;
        cin >> id;
    }
    cout << "请输入用户名：" << endl;
    cin >> name;
    cout << "请输入密码：" << endl;
    cin >> pwd;
    if (type == 1)
    {
        //申请身份验证
        int fId;//从文件中读取的id号
        string fName;//从文件中获取的姓名
        string fPwd;//从文件中获取密码
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            //与用户输入的信息做对比
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "申请人验证登录成功！" << endl;
                system("pause");
                system("cls");
                person = new Applicant(id, name, pwd);
                //进入申请人身份的子菜单
                applicantMenu(person);
                return;
            }
        }

    }
    else if (type == 2)
    {
        //审核身份验证
        int fId;//从文件中获取的id号
        string fName;//从文件中获取的密码
        string fPwd;//从文件中获取密码
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "教师验证登录成功" << endl;
                system("pause");
                system("cls");
                person = new Auditor(id, name, pwd);
                //进入教师子菜单界面
                auditorMenu(person);
                return;
            }
        }

    }
    else if (type == 3)
    {
        //管理员身份验证
        string fName;//从文件中获取姓名
        string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (name == fName && pwd == fPwd)
            {
                cout << "管理员验证登录成功" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, pwd);
                //进入管理员子菜单界面
                managerMenu(person);
                return;
            }
        }
    }
    cout << "验证登录失败！" << endl;
    system("pause");
    system("cls");
    return;
}
//创建文件
void SetFile(string filename)
{
    ifstream ifs;
    ifs.open(filename, ios::in);
    ifs.close();

}
int main()
{
    int select = 0;//用于接受用户的选择



    while (true)
    {
        cout << "======================  预约系统  ====================="
            << endl;
        cout << endl << "请输入您的身份" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.申 请 人           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.审 核 人           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管 理 员           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退    出           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "输入您的选择: ";
        cin >> select;//接受用户选择

        switch (select)//根据用户选择 实现不同接口
        {
        case 1://申请applicant
            SetFile(APPLICANT_FILE);
            LoginIn(APPLICANT_FILE, 1);
            break;
        case 2://审核 auditor
            SetFile(AUDITOR_FILE);
            LoginIn(AUDITOR_FILE, 2);
            break;
        case 3://管理员身份
            SetFile(ADMIN_FILE);
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0://退出系统
            cout << "欢迎下一次使用" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入有误，请重新选择！" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}