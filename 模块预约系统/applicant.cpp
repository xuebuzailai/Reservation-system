#include"applicant.h"

//默认构造
Applicant::Applicant()
{

}
//有参构造 参数：申请编号 姓名 密码
Applicant::Applicant(int id, string name, string pwd)
{
    //初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //初始化机房信息
    ifstream ifs;
    ifs.open(SPACE_FILE, ios::in);
    Space spa;
    while (ifs >> spa.m_SId && ifs >> spa.m_MaxNum)
    {
        //将读取的信息放入到容器中
        vSpa.push_back(spa);
    }
    ifs.close();
}
//菜单界面
void Applicant::operMenu()
{
    cout << "欢迎申请人：" << this->m_Name << "登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.申请预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.查看我的预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          3.查看所有预约          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          4.取消预约              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.注销登录              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作： " << endl;
}

//申请预约
void Applicant::applyOrder()
{
    cout << "空间开放时间为周一至周五!" << endl;
    cout << "请输入申请预约时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    int date = 0;//日期
    int interval = 0;//时间段
    int room = 0;//空间编号

    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "请输入申请预约时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;

    }
    cout << "请选择空间：" << endl;
    for (int i = 0; i < vSpa.size(); i++)
    {
        cout << vSpa[i].m_SId << "号空间容量为：" << vSpa[i].m_MaxNum << endl;
    }
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "预约成功！审核中" << endl;
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "appId:" << this->m_Id << " ";
    ofs << "appName:" << this->m_Name << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << endl;
    ofs.close();
    system("pause");
    system("cls");
}
//查看自身预约
void Applicant::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "没有预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
       
        if (this->m_Id == atoi(of.m_OrderData[i]["appId"].c_str()))//找到自身预约
        {
            cout << "预约日期：周" << of.m_OrderData[i]["date"];
            cout << " 时间段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 机房编号：" << of.m_OrderData[i]["roomId"] << " ";
            string status = "状态：";
            //1 审核中 2已预约 -1预约失败 0取消预约
            if (of.m_OrderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if (of.m_OrderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_OrderData[i]["status"] == "-1")
            {
                status += "预约失败，审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
    }
    cout << endl;
    system("pause");
    system("cls");

}
//查看所有预约
void Applicant::showAllOrder()
{
    OrderFile of;
    of.showAllOrder();
}
//取消预约
void Applicant::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
    vector<int>v;//存放在最大容器中的下标编号
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        //先判断是自身编号
        if (this->m_Id == atoi(of.m_OrderData[i]["appId"].c_str()))
        {
            //再筛选状态 审核中或预约成功
            if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "、";
                cout << "预约日期：周" << of.m_OrderData[i]["date"];
                cout << " 时间段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << " 机房编号：" << of.m_OrderData[i]["roomId"];
                string status = " 状态:";
                if (of.m_OrderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if (of.m_OrderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    cout << "请输入取消的记录，0代表返回" << endl;
    int select = 0;
    while (true)
    {
        cin >> select;
        if (select >= 0 && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_OrderData[v[select - 1]]["status"] = "0";
                of.updateOrder();
                cout << "已取消预约" << endl;
                break;

            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
    system("pause");
    system("cls");
}