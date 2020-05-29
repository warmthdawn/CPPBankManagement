#pragma once
#include<iostream>
#include<string>
#include"BankAccount.h"
#include"AccountFile.h"
//转换类
class Adapt {
public:
	//构造函数
	Adapt(string id_account, string id_card, string name, string address, double balance);      //构造函数 包括余额
	Adapt(string id_account, string id_card, string name, string address);                      //构造函数 不包括余额
	Adapt(string id_account);                                                                   //构造函数 只有账号
	Adapt();                                                                                    //构造函数 默认所有字符串为"null"
	//添加账号
	bool Add(string id_account, string id_card, string name, string address, double balance);   //添加账户 包括余额
	bool Add(string id_account, string id_card, string name, string address);                   //添加账户 不包括余额     
	bool Add(string id_account);                                                                //添加账户 只有账号
	bool Add();                                                                                 //添加账户 默认所有字符串为"null"
	//删除账户
	bool Delete(string id_account);
	//得到账户
	string getAll(string id_account);
	//得到所有账户
	string All();
private:
	string id_account;              //账号
	string id_card;                 //身份证号码
	string name;                    //姓名
	string address;                 //地址
	double balance;                 //余额
};