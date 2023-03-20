#include"auditor.h"

//Ĭ�Ϲ���
Auditor::Auditor()
{

}
//�вι���
Auditor::Auditor(int audId, string name, string pwd)
{
    //��ʼ������
    this->m_AudId = audId;
    this->m_Name = name;
    this->m_Pwd = pwd;


}
//�˵�����
void Auditor::operMenu()
{
    cout << "��ӭ���Ա��" << this->m_Name << "��¼��" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.�鿴����ԤԼ          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.���ԤԼ              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.ע����¼              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

//�鿴����ԤԼ
void Auditor::showAllOrder()
{
    OrderFile of;
    of.showAllOrder();
}
//���ԤԼ
void Auditor::validOrder()
{
    OrderFile of;
    if (of.m_Size == 0)
    {
        cout << "��ԤԼ��¼" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����˵�ԤԼ��¼���£�" << endl;
    vector<int>v;
    int index = 0;
    for (int i = 0; i < of.m_Size; i++)
    {
        if (of.m_OrderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << ++index << "��";
            cout << " ԤԼ���ڣ���" << of.m_OrderData[i]["date"];
            cout << " ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����");
            cout << " �����˱�ţ�" << of.m_OrderData[i]["appId"];
            cout << " ������������" << of.m_OrderData[i]["appName"];
            cout << " ������ţ�" << of.m_OrderData[i]["roomId"];
            string status = "״̬�������";
            cout << status << endl;
        }
    }
    cout << "��������˵�ԤԼ��¼��0������" << endl;
    int select = 0;//�����û�ѡ���ԤԼ��¼
    int ret = 0;//����ԤԼ����ļ�¼
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
                cout << "��������˽����" << endl;
                cout << "1��ͨ��" << endl;
                cout << "2����ͨ��" << endl;
                cin >> ret;
                if (ret == 1)
                {
                    //ͨ�����
                    of.m_OrderData[v[select - 1]]["status"] = "2";
                }
                else
                {
                    //��ͨ�����
                    of.m_OrderData[v[select - 1]]["status"] = "-1";
                }
                //����ԤԼ��¼
                of.updateOrder();
                cout << "������" << endl;
                break;

            }
        }
        cout << "������������������" << endl;

    }
    system("pause");
    system("cls");

}
