#include<iostream>
#include<string>
#include"AccountFile.h"
#include"Adapt.h"
Adapt::Adapt(string id_account, string id_card, string name, string address, double balance)   //构造函数 包括余额
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(balance)
{

}
Adapt::Adapt(string id_account, string id_card, string name, string address)                   //构造函数 不包括余额
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(0.00)
{

}
Adapt::Adapt(string id_account)                                                                //构造函数 只有账号
	: id_account(id_account), id_card(""), name(""), address(""), balance(0.00)
{

}
Adapt::Adapt()                                                                                 //构造函数 默认所有字符串为"null"
	: id_account("null"), id_card("null"), name("null"), address("null"), balance(0.00)
{

}
//Adapt类中删除账户函数的实现
bool Adapt::Delete(string id_account) {
	AccountFile* account0 = new AccountFile(id_account);
	account0->setId_account(id_account);
	bool success = account0->deleteObject();
	delete account0;
	return success ? true : false;
}
//四种添加构造
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
bool Adapt::Add() {
	BankAccount* account = new BankAccount();
	AccountFile* fileAccount = new AccountFile(id_account, account);
	if (fileAccount->judge()) {
		fileAccount->deleteObject();
	}
	fileAccount->writeObject();
	delete account;
	delete fileAccount;
	return true;
}
string Adapt::getAll(string id_account) {
	AccountFile* fileAccount = new AccountFile(id_account);
	BankAccount account = fileAccount->findAccount(id_account);
	string str("{\"id_account\":\"" + account.getId_account()
		+ "\"," + "\"id_card\":\"" + account.getId_card()
		+ "\"," + "\"name\":\"" + account.getName()
		+ "\"," + "\"address\":\"" + account.getAddress()
		+ "\"," + "\"balance\":\" " + to_string(account.getBalance())
		+ "\"}");
	return str;
}
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