#pragma once
#include<iostream>
#include<string>
#include"BankAccount.h"
#include"AccountFile.h"
//xgl要求的转换类
class Adapt {
public:
	Adapt();
	string All();
	bool Delete(string id_account);
    Adapt(string id_account, string id_card, string name, string address, double balance);  //构造函数 包括余额
	Adapt(string id_account, string id_card, string name, string address);                   //构造函数 不包括余额
	Adapt(string id_account);                                                                //构造函数 只有账号	
	bool Add(string id_account, string id_card, string name, string address, double balance);  
	bool Add(string id_account, string id_card, string name, string address);                  
	bool Add(string id_account);                                                                
	bool Add();
	string getAll(string id_account);
private:
	string id_account;              //账号
	string id_card;                 //身份证号码
	string name;                    //姓名
	string address;                 //地址
	double balance;                 //余额

};