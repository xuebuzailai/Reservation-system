#include"manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{

    //��ʼ������Ա��Ϣ
    this->m_Name = name;
    this->m_Pwd = pwd;

    //��ʼ������ ���һ�ȡ�������ļ��� �����ˡ����Ա��Ϣ
    this->initVector();

     //��ʼ��������Ϣ
    ifstream ifs;
    ifs.open(SPACE_FILE, ios::in);
    Space spa;
    while (ifs >> spa.m_SId && ifs >> spa.m_MaxNum)
    {
        this->vSpa.push_back(spa);

    }
    ifs.close();
    cout << "�ռ�����Ϊ��" << vSpa.size() << endl;

}


//�˵�����
void Manager::operMenu()
{
    cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.����˺�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.�鿴�˺�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.�鿴�ռ�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.���ԤԼ            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.ע����¼            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

//����˺�
void Manager::addPerson()
{
    cout << "����������˺�����" << endl;
    cout << "1�����������" << endl;
    cout << "2��������Ա" << endl;

    string fileName;//�����ļ���
    string tip;//��ʾid��
    ofstream ofs;//�ļ���������
    string errorTip;//�ظ�������ʾ

    int select = 0;
    cin >> select;//�����û���ѡ��

    if (select == 1)
    {
        //���ѧ��

        fileName = APPLICANT_FILE;
        tip = "�����������ţ�";
        errorTip = "�������ظ�������������";

    }
    else if(select==2)
    {
        fileName = AUDITOR_FILE;
        tip = "��������˱�ţ�";
        errorTip = "��˱���ظ�������������";

    }
    else
    {
        cout << "������������������" << endl;
        system("pause");
        system("cls");
        return;
    }
    //����׷�ӵķ�ʽ д�ļ�
    ofs.open(fileName, ios::out | ios::app);
    int id;//�����Ż�����˱��
    string name;//����
    string pwd;//����

    cout << tip << endl;
    while (true)
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)//���ظ�
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }

    }

    cout << "������������" << endl;
    cin >> name;
    cout << "�������¼���룺" << endl;
    cin >> pwd;

       //���ļ����������
    ofs << id << " " << name << " " << pwd << endl;

    cout << "��ӳɹ�" << endl;
    system("pause");
    system("cls");
    ofs.close();


    //���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
    this->initVector();


}
void printApplicant(Applicant& a)
{
    cout<< "�����ţ�" << a.m_Id << "������" << a.m_Name << "���룺" << a.m_Pwd << endl;
}
void printAuditor(Auditor& Au)
{
    cout << "��˱�ţ�" << Au.m_AudId << "������" << Au.m_Name << "���룺" << Au.m_Pwd << endl;
}
//�鿴�˺�
void Manager::showPerson()
{

    cout << "��ѡ��鿴����:" << endl;
    cout << "1���鿴����������" << endl;
    cout << "2���鿴�������Ա" << endl;
    int select = 0;//�����û�ѡ��
    cin >> select;
    if (select == 1)
    {
        //�鿴������
        if (vApp.size() == 0)
        {
            cout << "����������Ϣ" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "������������Ϣ���£�" << endl;
            for_each(vApp.begin(), vApp.end(), printApplicant);
        }
    }
    else if(select==2)
    {
        //�鿴���Ա
        if (vAud.size() == 0)
        {
            cout << "�����Ա��Ϣ" << endl;
            system("pause");
            system("cls");
            return;
        }
        else
        {
            cout << "�������Ա��Ϣ���£�" << endl;
            for_each(vAud.begin(), vAud.end(), printAuditor);
        }
    }
    else
    {
        cout << "������������������" << endl;
        system("pause");
        system("cls");
        return;
    }
    system("pause");
    system("cls");
}
//�鿴�ռ���Ϣ
void Manager::showSpace()
{
    cout << "�ռ���Ϣ���£�" << endl;
    for (vector<Space>::iterator it = vSpa.begin(); it != vSpa.end(); it++)
    {
        cout << "�ռ��ţ�" << it->m_SId << " �ռ��������:" << it->m_MaxNum << endl;
    }
    system("pause");
    system("cls");
}
//���ԤԼϵͳ
void Manager::cleanFile()
{
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::trunc);
    ofs.close();
    cout << "��ճɹ���" << endl;
    system("pause");
    system("cls");
}


//��ʼ������
void Manager::initVector()
{

    //ȷ���������״̬
    vApp.clear();
    vAud.clear();
    //��ȡ��Ϣ ������
    ifstream ifs;
    ifs.open(APPLICANT_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "�ļ���ȡʧ��" << endl;
        return;
    }
    Applicant a;
    while (ifs >> a.m_Id && ifs >> a.m_Name && ifs >> a.m_Pwd)
    {
        vApp.push_back(a);
    }
    cout << "��ǰ����������Ϊ��" << vApp.size() << endl;
    ifs.close();

    //��ȡ��Ϣ ���Ա
    ifs.open(AUDITOR_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "�ļ���ȡʧ��" << endl;
        return;
    }
    Auditor AU;
    while (ifs >> AU.m_AudId && ifs >> AU.m_Name && ifs >> AU.m_Pwd)
    {
        vAud.push_back(AU);
    }
    cout << "��ǰ���Ա��������" << vAud.size() << endl;
    ifs.close();



}


//����ظ� ����һ ��������˱��/���Ա��� ������ �������
bool Manager::checkRepeat(int id, int type)
{
    if (type == 1)
    {
        //���������
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
        //������Ա
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
