#include"employee.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>



Employee::Employee(int id, const string& name, int age, Post post)
	:m_sId(id),m_sName(name),m_nAge(age),m_pPost(post) {}
int Employee::getId() { return m_sId; }
string Employee::getName() { return m_sName; }
int Employee::getAge() { return m_nAge; }
Post Employee::getPost() { return m_pPost; }
bool Employee::getState() const { return state; }

void Employee::setId(const int& id) { m_sId = id;}
void Employee::setName(const string& name) { m_sName = name;}
void Employee::setAge(const int& age) { m_nAge = age;}
void Employee::setPost(const Post& post) { m_pPost = post;}
void Employee::setState(bool status) { state = status; }

Salesman::Salesman(int id, const string& name, int age, Post post, int sales)
	:Employee(id,name,age,post),m_nSales(sales){}
int Salesman::getSales() { return m_nSales; }
void Salesman::setSales(const int& sales) { m_nSales = sales; }


SalesManager::SalesManager(int id, const string& name, int age, Post post, int sales)
	:Employee(id, name, age, post), m_nSales(sales) {}
int SalesManager::getSales() { return m_nSales; }
void SalesManager::setSales(const int& sales) { m_nSales = sales; }

Manager::Manager(int id, const string& name, int age, Post post)
	:Employee(id, name, age, post){}

System::~System()
{
	for (auto e:m_vEmployees)
	{
		delete e;
	}
}

//����id��ѯ�Ƿ����
bool System::idExists(int id) const
{
	for (auto e:m_vEmployees)
	{
		if (e->getId() == id)
		{
			return true;
		}
	}
	return false;
}

//ѡ���λ
Post System::selectPosition()const
{
	int num;
	cout << "��0������Ա"<<"��1�����۾���"<<"��2���ܾ���" << endl;
	cin >> num;
	switch (num)
	{
	case 0:return SALESMAN;
	case 1:return SALESMANAGER;
	case 2:return MANAGER;
	default:"������ȷ����";
		break;
	}
}

//���Ա��
void System::addEmployee()
{
	int id, age, sales = 0;
	string name;
	Post post;

	cout << "�����û�ID��";
	cin >> id;
	if (idExists(id))
	{
		cout << "�û��Ѵ���" << endl;
		return;
	}

	cout << "�������֣�";
	cin >> name;
	cout << "�������䣺";
	cin >> age;

	post = selectPosition();
	if (post == SALESMAN||post == SALESMANAGER)
	{
		cout << "�������۶";
		cin >> sales;
	}

	Employee* e = NULL;
	if (post == SALESMAN)
	{
		e = new Salesman(id, name, age, post ,sales);
	}
	else if (post == SALESMANAGER)
	{
		e = new SalesManager(id, name, age, post, sales);
	}
	else
	{
		e = new Manager(id, name, age, post);
	}

	m_vEmployees.push_back(e);
	cout << "���Ա���ɹ�" << endl;
}

//����id����Ա��
void System::updateEmployee(int id)
{
	for (auto e:m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			string name;
			int age,sales = 0;

			cout << "������Ϊ��";
			cin >> name;
			e->setName(name);

			cout << "������Ϊ��";
			cin >> age;
			e->setAge(age);

			if (e->getPost() == SALESMAN || e->getPost() == SALESMANAGER)
			{
				cout << "�µ����۶�Ϊ��";
				cin >> sales;
			}
			cout << "���³ɹ�" << endl;
			return;
			
		}
	}
	cout << "�޴�Ա��" << endl;
}

//���Ա��
void System::deleteEmployee(int id)
{
	for (auto e:m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			e->setState(false);
			cout << "��Ա���Ա�Ǵ���ְ" << endl;
			return;
		}
	}
}

//����id��ѯԱ��
void System::findEmployeeId(int id) const
{
	bool num = true;
	for (auto e: m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			cout << "Ա��ID��" << e->getId() << endl;
			cout << "����Ϊ��" << e->getName() << endl;
			cout << "Ա������Ϊ��" << e->getAge() << endl;
			switch (e->getPost())
			{
			case SALESMAN:cout << "����Ա" << endl; break;
			case SALESMANAGER:cout << "���۾���" << endl; break;
			case MANAGER:cout << "����" << endl; break;
			default:cout << "���޴���" << endl;
				break;
			}
			if (e->getState() == SALESMAN || e->getState() == SALESMANAGER)
			{
				cout << "���۶�:" << static_cast<Salesman*>(e)->getSales() << endl;
			}
			cout << "״̬: ��ְ" << endl;
			num = true;
		}
	}
	if (!num)
	{
		cout << "���޴���" << endl;
	}
}

//����������ѯԱ��
void System::findEmployeeName(const string& name)const
{
	for (auto e : m_vEmployees)
	{
		if (e->getName() == name && e->getState())
		{
			name; cout << "Ա��ID��" << e->getId() << endl;
			cout << "����Ϊ��" << e->getName() << endl;
			cout << "Ա������Ϊ��" << e->getAge() << endl;
			return;


			switch (e->getPost())
			{
			case SALESMAN:
				cout << "ְλ������Ա" << endl;
				if (auto s = static_cast<Salesman*>(e))
				{
					cout << "���۶�Ϊ��" << s->getSales() << endl;
				}
				break;
			case SALESMANAGER:
				cout << "ְλ�����۾���" << endl;
				if (auto s = static_cast<Salesman*>(e))
				{
					cout << "���۶�Ϊ��" << s->getSales() << endl;
				}
				break;
			case MANAGER:
				cout << "ְλ�Ǿ���" << endl;
				break;
			default:cout << "���޴���" << endl;
				break;
			}
		}
	}
	cout << "�޴�Ա��" << endl;
}


//��ѯ����Ա��
void System::listAll() const
{
	if (m_vEmployees.empty())
	{
		cout << "���޳�Ա��Ϣ" << endl;
		return;
	}

	for (auto e:m_vEmployees)
	{
		if (!e->getState())
		{

			continue;
		}
		cout << "Ա��ID��" << e->getId();
		cout << "Ա��������" << e->getName();
		cout << "Ա�����䣺" << e->getAge();


		switch (e->getPost())
		{
		case SALESMAN:
			cout << "ְλ������Ա" << endl;
			if (auto s = static_cast<Salesman*>(e))
			{
				cout << "���۶�Ϊ��" << s->getSales() << endl;
			}
			break;
		case SALESMANAGER:
			cout << "ְλ�����۾���" << endl;
			if (auto s = static_cast<Salesman*>(e))
			{
				cout << "���۶�Ϊ��" << s->getSales() << endl;
			}
			break;
		case MANAGER:
			cout << "ְλ�Ǿ���" << endl;
			break;
		default:cout << "���޴���" << endl;
			break;
		}

	}

}

//��ѯԱ������
void System::findEmployeeCount() const
{
	int count = 0;
	for (auto e:m_vEmployees)
	{
		if (e->getState())
		{
			count++;
		}

	}
	cout << "��ǰ��ְԱ������: " << count << "��";
}

//�����ļ�
void System::saveToFile() {
	ofstream ofs(dataFile);
	if (!ofs.is_open())
	{
		cout << "·�������⣬�޷���" << endl;
		return;

	}
	for (auto e:m_vEmployees)
	{
		if (e)
		{
			ofs << e->getId() << "	" 
				<< e->getName() << "	" 
				<< e->getAge() << "		" 
				<< e->getPost() << endl;
			if (e->getPost() == SALESMAN || e->getPost() == SALESMANAGER)
			{
				ofs << static_cast<Salesman*>(e)->getSales() << endl;
			}
			else {
				ofs << "  " << endl;
			}
			ofs << e->getState() << endl;
		}
	}
	ofs.close();	
	cout << "����ɹ�" << endl;
}



//��ȡ�ļ�

void System::loadFromFile() {
	ifstream ifs(dataFile);
	if (!ifs.is_open()) {
		cout << "δ�ҵ�Ա����Ϣ�ļ������ļ���ʧ�ܡ�" << endl;
		return;
	}

	// ���ԭ������
	for (auto e : m_vEmployees) {
		delete e;
	}
	m_vEmployees.clear();

	int post, id, age, sales;
	string name;
	bool state;

	while (ifs >> post >> id >> name >> age >> sales >> state) {
		Employee* e = nullptr;
		switch (post) {
		case SALESMAN:
			e = new Salesman(id, name, age, static_cast<Post>(post), sales);
			break;
		case SALESMANAGER:
			e = new SalesManager(id, name, age, static_cast<Post>(post), sales);
			break;
		case MANAGER:
			e = new Manager(id, name, age, static_cast<Post>(post));
			break;
		default:
			cout << "��Ч��λ���ݣ�����������¼��" << endl;
			continue;
		}
		e->setState(state);
		m_vEmployees.push_back(e);
	}

	ifs.close();
	cout << "Ա����Ϣ������ɡ�" << endl;
}


