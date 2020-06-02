#pragma once
#include <iostream>
#include <string>
#include "BankAccount.h"
#include "AccountFile.h"

//转换类
class Adapt {
public:
	//构造函数
	Adapt();                                                                                    //构造函数
	//添加账号
	bool Add(string id_account, string id_card, string name, string address, double balance);   //添加账户 包括余额
	bool Add(string id_account, string id_card, string name, string address);                   //添加账户 不包括余额     
	bool Add(string id_account);                                                                //添加账户 只有账号
	bool Add();                                                                                 //添加账户 默认所有字符串为"null"
	//删除账户
	bool Delete(string id_account);                                                             //删除账户
	//得到指定账户信息
	string getAll(string id_account);                                                           //得到指定账户信息
	//得到所有账号
	string All();                                                                               //得到所有账号
	//析构函数
	~Adapt();                                                                                   //析构函数
};