#pragma once
#include<string>
#include<vector>
using namespace std;

enum Post {
	SALESMAN,
	SALESMANAGER,
	MANAGER
};
class Employee {
	int m_sId;//id��
	string m_sName;//����
	int m_nAge;//����
	Post m_pPost;//��λ
	bool state = true;//״̬ ��ְΪtrue 
public:
	Employee(int id, const string& name, int age, Post post);
	virtual ~Employee() = 0;
	int getId();
	string getName();
	int getAge();
	Post getPost();
	bool getState() const;
	void setId(const int& id);
	void setName(const string& name);
	void setAge(const int& age);
	void setPost(const Post& post);
	void setState(bool status);

	
};
class Salesman : public Employee {
	int m_nSales;
public:
	
	Salesman(int id, const string& name, int age, Post post, int sales);
	int getSales();
	void setSales(const int& sales);

};

class SalesManager : public Employee {
	int m_nSales;
public:
	SalesManager(int id, const string& name, int age, Post post, int sales);
	int getSales();
	void setSales(const int& sales);
};
class Manager : public Employee {
	
public:
	Manager(int id, const string& name, int age, Post post);
};
class System {
	vector<Employee*> m_vEmployees;
	string dataFile = "employee.txt";
public:
	~System();

	void addEmployee();//���Ա��
	void updateEmployee(int id);//����id����Ա��
	void deleteEmployee(int id);//���Ա��
	void findEmployeeId(int id) const;//����id��ѯԱ��
	void findEmployeeName(const string& name) const;//����������ѯԱ��
	void listAll() const;//��ѯ����Ա��
	void findEmployeeCount() const;//��ѯԱ������

	//�ļ��еĲ���
	void saveToFile();//�����ļ�
	void loadFromFile();//��ȡ�ļ�

	//��������
	bool idExists(int id) const;//����id��ѯ�Ƿ����
	Post selectPosition() const;//ѡ���λ
};

