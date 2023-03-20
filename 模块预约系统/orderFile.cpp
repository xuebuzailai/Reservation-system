#include"orderFile.h"

//���캯��
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;//����
	string interval;//ʱ���
	string appId;//�����˱��
	string appName;//����������
	string roomId;//�������
	string status;//ԤԼ״̬

	this->m_Size = 0;//��¼ԤԼ����
	while (ifs >> date && ifs >> interval && ifs >> appId && ifs >> appName && ifs >> roomId && ifs >> status)
	{
		
		map<string, string>m;

		getMap(date, m);
		getMap(interval, m);
		getMap(appId, m);
		getMap(appName, m);
		getMap(roomId, m);
		getMap(status, m);

	
		this->m_OrderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();

}
void OrderFile::getMap(string& word, map<string, string>& m)
{
	string key;
	string value;


	int pos = word.find(":");//����4
	if (pos != -1)
	{
		key = word.substr(0, pos);
		value = word.substr(pos + 1, word.size() - pos - 1);

		m.insert(make_pair(key, value));
	}
}

//����ԤԼ��¼
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;//ԤԼ��¼������ֱ��return
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_OrderData[i]["date"] << " ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "appId:" << this->m_OrderData[i]["appId"] << " ";
		ofs << "appName:" << this->m_OrderData[i]["appName"] << " ";
		ofs << "roomId:" << this->m_OrderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << endl;
	}
	ofs.close();

}

void OrderFile::showAllOrder()
{
	if (this->m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < this->m_Size; i++)
	{
		cout << i + 1 << "�� ";
		cout << "ԤԼ���ڣ���" << this->m_OrderData[i]["date"];
		cout << " ʱ��Σ�" << (this->m_OrderData[i]["interval"] == "1" ? "����" : "����");
		cout << " �����˱�ţ�" << this->m_OrderData[i]["appId"];
		cout << " ������" << this->m_OrderData[i]["appName"];
		cout << " ������ţ�" << this->m_OrderData[i]["roomId"];
		string status = "״̬��";
		//1������� 2����ԤԼ -1��ԤԼʧ�� 0��ȡ��ԤԼ
		if (this->m_OrderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (this->m_OrderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (this->m_OrderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else if (this->m_OrderData[i]["status"] == "0")
		{
			status += "ԤԼ�Ѿ�ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}
