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
	int m_sId;//id号
	string m_sName;//姓名
	int m_nAge;//年龄
	Post m_pPost;//岗位
	bool state = true;//状态 在职为true 
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

	void addEmployee();//添加员工
	void updateEmployee(int id);//根据id更新员工
	void deleteEmployee(int id);//解雇员工
	void findEmployeeId(int id) const;//根据id查询员工
	void findEmployeeName(const string& name) const;//根据姓名查询员工
	void listAll() const;//查询所有员工
	void findEmployeeCount() const;//查询员工人数

	//文件中的操作
	void saveToFile();//保存文件
	void loadFromFile();//读取文件

	//辅助方法
	bool idExists(int id) const;//利用id查询是否存在
	Post selectPosition() const;//选择岗位
};

