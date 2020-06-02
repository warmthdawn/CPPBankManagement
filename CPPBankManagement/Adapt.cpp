#include <iostream>
#include <string>
#include "AccountFile.h"
#include "Adapt.h"

//构造函数
Adapt::Adapt() {

}

//Adapt类中删除账户函数的实现
bool Adapt::Delete(string id_account) {
	AccountFile* account0 = new AccountFile(id_account);
	account0->setId_account(id_account);
	bool success = account0->deleteObject();
	delete account0;
	return success ? true : false;
}

//添加构造 包括余额
bool Adapt::Add(string id_account, string id_card, string name, string address, double balance) {
	BankAccount* account = new BankAccount(id_account, id_card, name, address, balance);
	AccountFile* fileAccount = new AccountFile(id_account, account);
	if (fileAccount->judge()) {
		fileAccount->deleteObject();
	}
	fileAccount->writeObject();
	delete account;
	delete fileAccount;
	return true;
}

//添加构造 不包括余额
bool Adapt::Add(string id_account, string id_card, string name, string address) {
	BankAccount* account = new BankAccount(id_account, id_card, name, address);
	AccountFile* fileAccount = new AccountFile(id_account, account);
	if (fileAccount->judge()) {
		fileAccount->deleteObject();
	}
	fileAccount->writeObject();
	delete account;
	delete fileAccount;
	return true;
}

//添加构造 只有账号
bool Adapt::Add(string id_account) {
	BankAccount* account = new BankAccount(id_account);
	AccountFile* fileAccount = new AccountFile(id_account, account);
	if (fileAccount->judge()) {
		fileAccount->deleteObject();
	}
	fileAccount->writeObject();
	delete account;
	delete fileAccount;
	return true;
}

//添加构造 默认所有字符串为"null"
bool Adapt::Add() {
	BankAccount* account = new BankAccount();
	AccountFile* fileAccount = new AccountFile("null", account);
	if (fileAccount->judge()) {
		fileAccount->deleteObject();
	}
	fileAccount->writeObject();
	delete account;
	delete fileAccount;
	return true;
}

//得到指定账户信息
string Adapt::getAll(string id_account) {
	AccountFile* fileAccount = new AccountFile(id_account);
	BankAccount account = fileAccount->findAccount(id_account);
	string str("{\"id_account\":\"" + account.getId_account()
		+ "\"," + "\"id_card\":\"" + account.getId_card()
		+ "\"," + "\"name\":\"" + account.getName()
		+ "\"," + "\"address\":\"" + account.getAddress()
		+ "\"," + "\"balance\":\" " + (to_string(account.getBalance())).substr(0, (to_string(account.getBalance()).size() - (6 - PRECISION)))
		+ "\"}");
	return str;
}

//得到所有账号
string Adapt::All() {
	//实现对象中每种数据的转换
	string* all = NULL;
	AccountFile* account = new AccountFile;
	int n = account->allObject(&all);
	delete account;
	string s = "[\"";
	for (int i = 0; i < n; i++)
	{
		s.append(all[i]);
		if (i < n - 1) {
			s.append("\",\"");
		}
	}
	s.append("\"]");
	return s;
}

//析构函数
Adapt::~Adapt() {

}