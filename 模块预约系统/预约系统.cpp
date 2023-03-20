#include<iostream>
using namespace std;
#include"identity.h"
#include<fstream>
#include<string>
#include"globalfile.h"
#include"applicant.h"
#include"auditor.h"
#include"manager.h"

//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager)//identity*��ʽ�� �����ø���ֵ�� managerָ��
{
    while (true)
    {
        //���ù���Ա�Ӳ˵�
        manager->operMenu();
        //������ָ��תΪ����ָ�룬���������������ӿ�
        Manager* man = (Manager*)manager;//��ʼ�� 

        int select = 0;
        //�����û�ѡ��

        cin >> select;
        if (select == 1)//����˺�
        {
           
            man->addPerson();

        }
        else if (select == 2)//�鿴�˺�
        {
           
            man->showPerson();
        }
        else if (select == 3)//�鿴�ռ�
        {
            
            man->showSpace();
        }

        else if (select == 4)//���ԤԼ
        {
           
            man->cleanFile();
        }
        else
        {
            //ע��
            delete manager;//���ٵ���������
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}

//�����������Ӳ˵�����
void applicantMenu(Identity*& applicant)
{
    while (true)
    {
        //�����������Ӳ˵�
        applicant->operMenu();
        Applicant* app = (Applicant*)applicant;//stu��ʱָ��
        int select = 0;
        cin >> select;//�����û�ѡ��
        if (select == 1)//����ԤԼ
        {
            app->applyOrder();
        }
        else if (select == 2)//�鿴����ԤԼ
        {
            app->showMyOrder();
        }
        else if (select == 3)//�鿴������ԤԼ
        {
            app->showAllOrder();
        }
        else if (select == 4)//ȡ��ԤԼ
        {
            app->cancelOrder();
        }
        else
        {
            //ע����¼
            delete applicant;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
//�������Ա�Ӳ˵�����
void auditorMenu(Identity*& auditor)
{
    while (true)
    {
        //�����Ӳ˵�����
        auditor->operMenu();
        Auditor* aud = (Auditor*)auditor;
        int select = 0;//�����û�ѡ��
        cin >> select;
        if (select == 1)//�鿴����ԤԼ
        {
            aud->showAllOrder();
        }
        else if (select == 2)//���ԤԼ
        {
            aud->validOrder();
        }
        else
        {
            delete auditor;
            cout << "ע���ɹ�" << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}


//��¼���� ����һ �����ļ��� �����������������
void LoginIn(string fileName, int type)
{
    //����ָ�룬����ָ���������
    Identity* person = NULL;

    //���ļ�
    ifstream ifs;
    ifs.open(fileName, ios::in);
    //�ж��ļ��Ƿ����
    if (!ifs.is_open())
    {
        cout << "�ļ�������" << endl;
        ifs.close();
        system("pause");
        system("cls");
        return;
    }
    //׼�������û���Ϣ
    int id = 0;
    string name;
    string pwd;

    //�ж����
    if (type == 1)//���������
    {
        cout << "��������������ţ�" << endl;
        cin >> id;
    }
    else if (type == 2)
    {
        cout << "������������˱��:" << endl;
        cin >> id;
    }
    cout << "�������û�����" << endl;
    cin >> name;
    cout << "���������룺" << endl;
    cin >> pwd;
    if (type == 1)
    {
        //���������֤
        int fId;//���ļ��ж�ȡ��id��
        string fName;//���ļ��л�ȡ������
        string fPwd;//���ļ��л�ȡ����
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            //���û��������Ϣ���Ա�
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "��������֤��¼�ɹ���" << endl;
                system("pause");
                system("cls");
                person = new Applicant(id, name, pwd);
                //������������ݵ��Ӳ˵�
                applicantMenu(person);
                return;
            }
        }

    }
    else if (type == 2)
    {
        //��������֤
        int fId;//���ļ��л�ȡ��id��
        string fName;//���ļ��л�ȡ������
        string fPwd;//���ļ��л�ȡ����
        while (ifs >> fId && ifs >> fName && ifs >> fPwd)
        {
            if (fId == id && fName == name && fPwd == pwd)
            {
                cout << "��ʦ��֤��¼�ɹ�" << endl;
                system("pause");
                system("cls");
                person = new Auditor(id, name, pwd);
                //�����ʦ�Ӳ˵�����
                auditorMenu(person);
                return;
            }
        }

    }
    else if (type == 3)
    {
        //����Ա�����֤
        string fName;//���ļ��л�ȡ����
        string fPwd;
        while (ifs >> fName && ifs >> fPwd)
        {
            if (name == fName && pwd == fPwd)
            {
                cout << "����Ա��֤��¼�ɹ�" << endl;
                system("pause");
                system("cls");
                person = new Manager(name, pwd);
                //�������Ա�Ӳ˵�����
                managerMenu(person);
                return;
            }
        }
    }
    cout << "��֤��¼ʧ�ܣ�" << endl;
    system("pause");
    system("cls");
    return;
}
//�����ļ�
void SetFile(string filename)
{
    ifstream ifs;
    ifs.open(filename, ios::in);
    ifs.close();

}
int main()
{
    int select = 0;//���ڽ����û���ѡ��



    while (true)
    {
        cout << "======================  ԤԼϵͳ  ====================="
            << endl;
        cout << endl << "�������������" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.�� �� ��           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.�� �� ��           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.�� �� Ա           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.��    ��           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "��������ѡ��: ";
        cin >> select;//�����û�ѡ��

        switch (select)//�����û�ѡ�� ʵ�ֲ�ͬ�ӿ�
        {
        case 1://����applicant
            SetFile(APPLICANT_FILE);
            LoginIn(APPLICANT_FILE, 1);
            break;
        case 2://��� auditor
            SetFile(AUDITOR_FILE);
            LoginIn(AUDITOR_FILE, 2);
            break;
        case 3://����Ա���
            SetFile(ADMIN_FILE);
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0://�˳�ϵͳ
            cout << "��ӭ��һ��ʹ��" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "��������������ѡ��" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}