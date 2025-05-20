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

//利用id查询是否存在
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

//选择岗位
Post System::selectPosition()const
{
	int num;
	cout << "【0】销售员"<<"【1】销售经理"<<"【2】总经理" << endl;
	cin >> num;
	switch (num)
	{
	case 0:return SALESMAN;
	case 1:return SALESMANAGER;
	case 2:return MANAGER;
	default:"输入正确数字";
		break;
	}
}

//添加员工
void System::addEmployee()
{
	int id, age, sales = 0;
	string name;
	Post post;

	cout << "输入用户ID：";
	cin >> id;
	if (idExists(id))
	{
		cout << "用户已存在" << endl;
		return;
	}

	cout << "输入名字：";
	cin >> name;
	cout << "输入年龄：";
	cin >> age;

	post = selectPosition();
	if (post == SALESMAN||post == SALESMANAGER)
	{
		cout << "输入销售额：";
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
	cout << "添加员工成功" << endl;
}

//根据id更新员工
void System::updateEmployee(int id)
{
	for (auto e:m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			string name;
			int age,sales = 0;

			cout << "新姓名为：";
			cin >> name;
			e->setName(name);

			cout << "新年龄为：";
			cin >> age;
			e->setAge(age);

			if (e->getPost() == SALESMAN || e->getPost() == SALESMANAGER)
			{
				cout << "新的销售额为：";
				cin >> sales;
			}
			cout << "更新成功" << endl;
			return;
			
		}
	}
	cout << "无此员工" << endl;
}

//解雇员工
void System::deleteEmployee(int id)
{
	for (auto e:m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			e->setState(false);
			cout << "该员工以标记待离职" << endl;
			return;
		}
	}
}

//根据id查询员工
void System::findEmployeeId(int id) const
{
	bool num = true;
	for (auto e: m_vEmployees)
	{
		if (e->getId() == id && e->getState())
		{
			cout << "员工ID：" << e->getId() << endl;
			cout << "姓名为：" << e->getName() << endl;
			cout << "员工年龄为：" << e->getAge() << endl;
			switch (e->getPost())
			{
			case SALESMAN:cout << "销售员" << endl; break;
			case SALESMANAGER:cout << "销售经理" << endl; break;
			case MANAGER:cout << "经理" << endl; break;
			default:cout << "查无此人" << endl;
				break;
			}
			if (e->getState() == SALESMAN || e->getState() == SALESMANAGER)
			{
				cout << "销售额:" << static_cast<Salesman*>(e)->getSales() << endl;
			}
			cout << "状态: 在职" << endl;
			num = true;
		}
	}
	if (!num)
	{
		cout << "查无此人" << endl;
	}
}

//根据姓名查询员工
void System::findEmployeeName(const string& name)const
{
	for (auto e : m_vEmployees)
	{
		if (e->getName() == name && e->getState())
		{
			name; cout << "员工ID：" << e->getId() << endl;
			cout << "姓名为：" << e->getName() << endl;
			cout << "员工年龄为：" << e->getAge() << endl;
			return;


			switch (e->getPost())
			{
			case SALESMAN:
				cout << "职位是销售员" << endl;
				if (auto s = static_cast<Salesman*>(e))
				{
					cout << "销售额为：" << s->getSales() << endl;
				}
				break;
			case SALESMANAGER:
				cout << "职位是销售经理" << endl;
				if (auto s = static_cast<Salesman*>(e))
				{
					cout << "销售额为：" << s->getSales() << endl;
				}
				break;
			case MANAGER:
				cout << "职位是经理" << endl;
				break;
			default:cout << "查无此人" << endl;
				break;
			}
		}
	}
	cout << "无此员工" << endl;
}


//查询所有员工
void System::listAll() const
{
	if (m_vEmployees.empty())
	{
		cout << "暂无成员信息" << endl;
		return;
	}

	for (auto e:m_vEmployees)
	{
		if (!e->getState())
		{

			continue;
		}
		cout << "员工ID：" << e->getId();
		cout << "员工姓名：" << e->getName();
		cout << "员工年龄：" << e->getAge();


		switch (e->getPost())
		{
		case SALESMAN:
			cout << "职位是销售员" << endl;
			if (auto s = static_cast<Salesman*>(e))
			{
				cout << "销售额为：" << s->getSales() << endl;
			}
			break;
		case SALESMANAGER:
			cout << "职位是销售经理" << endl;
			if (auto s = static_cast<Salesman*>(e))
			{
				cout << "销售额为：" << s->getSales() << endl;
			}
			break;
		case MANAGER:
			cout << "职位是经理" << endl;
			break;
		default:cout << "查无此人" << endl;
			break;
		}

	}

}

//查询员工人数
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
	cout << "当前在职员工数量: " << count << "人";
}

//保存文件
void System::saveToFile() {
	ofstream ofs(dataFile);
	if (!ofs.is_open())
	{
		cout << "路径有问题，无法打开" << endl;
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
	cout << "保存成功" << endl;
}



//读取文件

void System::loadFromFile() {
	ifstream ifs(dataFile);
	if (!ifs.is_open()) {
		cout << "未找到员工信息文件，或文件打开失败。" << endl;
		return;
	}

	// 清空原有数据
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
			cout << "无效岗位数据，跳过该条记录。" << endl;
			continue;
		}
		e->setState(state);
		m_vEmployees.push_back(e);
	}

	ifs.close();
	cout << "员工信息加载完成。" << endl;
}


