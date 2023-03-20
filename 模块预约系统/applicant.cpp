#include"applicant.h"

//Ĭ�Ϲ���
Applicant::Applicant()
{

}
//�вι��� ������������ ���� ����
Applicant::Applicant(int id, string name, string pwd)
{
    //��ʼ������
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;

    //��ʼ��������Ϣ
    ifstream ifs;
    ifs.open(SPACE_FILE, ios::in);
    Space spa;
    while (ifs >> spa.m_SId && ifs >> spa.m_MaxNum)
    {
        //����ȡ����Ϣ���뵽������
        vSpa.push_back(spa);
    }
    ifs.close();
}
//�˵�����
void Applicant::operMenu()
{
    cout << "��ӭ�����ˣ�" << this->m_Name << "��¼��" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.����ԤԼ              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          3.�鿴����ԤԼ          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          4.ȡ��ԤԼ              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.ע����¼              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Applicant::applyOrder()
{
    cout << "�ռ俪��ʱ��Ϊ��һ������!" << endl;
    cout << "����������ԤԼʱ�䣺" << endl;
    cout << "1����һ" << endl;
    cout << "2���ܶ�" << endl;
    cout << "3������" << endl;
    cout << "4������" << endl;
    cout << "5������" << endl;
    int date = 0;//����
    int interval = 0;//ʱ���
    int room = 0;//�ռ���

    while (true)
    {
        cin >> date;
        if (date >= 1 && date <= 5)
        {
            break;
        }
        cout << "������������������" << endl;
    }
    cout << "����������ԤԼʱ��Σ�" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;
    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "������������������" << endl;

    }
    cout << "��ѡ��ռ䣺" << endl;
    for (int i = 0; i < vSpa.size(); i++)
    {
        cout << vSpa[i].m_SId << "�ſռ�����Ϊ��" << vSpa[i].m_MaxNum << endl;
    }
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "������������������" << endl;
    }
    cout << "ԤԼ�ɹ��������" << endl;
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
//�鿴����ԤԼ
void Applicant::showMyOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "û��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    for (int i = 0; i < of.m_Size; i++)
    {
       
        if (this->m_Id == atoi(of.m_OrderData[i]["appId"].c_str()))//�ҵ�����ԤԼ
        {
            cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
            cout << " ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
            cout << " ������ţ�" << of.m_OrderData[i]["roomId"] << " ";
            string status = "״̬��";
            //1 ����� 2��ԤԼ -1ԤԼʧ�� 0ȡ��ԤԼ
            if (of.m_OrderData[i]["status"] == "1")
            {
                status += "�����";
            }
            else if (of.m_OrderData[i]["status"] == "2")
            {
                status += "ԤԼ�ɹ�";
            }
            else if (of.m_OrderData[i]["status"] == "-1")
            {
                status += "ԤԼʧ�ܣ����δͨ��";
            }
            else
            {
                status += "ԤԼ��ȡ��";
            }
            cout << status << endl;
        }
    }
    cout << endl;
    system("pause");
    system("cls");

}
//�鿴����ԤԼ
void Applicant::showAllOrder()
{
    OrderFile of;
    of.showAllOrder();
}
//ȡ��ԤԼ
void Applicant::cancelOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
    vector<int>v;//�������������е��±���
    int index = 1;
    for (int i = 0; i < of.m_Size; i++)
    {
        //���ж���������
        if (this->m_Id == atoi(of.m_OrderData[i]["appId"].c_str()))
        {
            //��ɸѡ״̬ ����л�ԤԼ�ɹ�
            if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "��";
                cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
                cout << " ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
                cout << " ������ţ�" << of.m_OrderData[i]["roomId"];
                string status = " ״̬:";
                if (of.m_OrderData[i]["status"] == "1")
                {
                    status += "�����";
                }
                else if (of.m_OrderData[i]["status"] == "2")
                {
                    status += "ԤԼ�ɹ�";
                }
                cout << status << endl;
            }
        }
    }
    cout << "������ȡ���ļ�¼��0������" << endl;
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
                cout << "��ȡ��ԤԼ" << endl;
                break;

            }
        }
        cout << "������������������" << endl;
    }
    system("pause");
    system("cls");
}