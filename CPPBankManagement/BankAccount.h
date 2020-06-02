#pragma once
#include <string>

using namespace std;

//银行账户类
class BankAccount
{
public:
	//构造函数
	BankAccount(string id_account, string id_card, string name, string address, double banlance);  //构造函数 包括余额
	BankAccount(string id_account, string id_card, string name, string address);                   //构造函数 不包括余额
	BankAccount(string id_account);                                                                //构造函数 只有账号
	BankAccount();                                                                                 //构造函数 默认所有字符串为"null"
	//得到信息
	string getId_account() { return id_account; }                                  //得到账号
	string getId_card() { return id_card; }                                        //得到身份证号码
	string getName() { return name; }                                              //得到姓名
	string getAddress() { return address; }                                        //得到地址
	double getBalance() { return balance; }                                        //得到余额
	//修改信息
	void setId_card(string id_card) { this->id_card = id_card; }                   //修改身份证号码
	void setName(string name) { this->name = name; }                               //修改姓名
	void setAddress(string address) { this->address = address; }                   //修改地址
	void setBalance(double balance) { this->balance = balance; }                   //修改余额
	//析构函数
	~BankAccount();
private:
	string id_account;              //账号
	string id_card;                 //身份证号码
	string name;                    //姓名
	string address;                 //地址
	double balance;                 //余额
};