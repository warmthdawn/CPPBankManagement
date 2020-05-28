#include<iostream>
#include<string>
#include"AccountFile.h"
#include"Adapt.h"

//构造函数
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
//转换函数的实现
 string Adapt::All() {

	//实现对象中每种数据的转换
	string* all;
	AccountFile* account = new AccountFile;
	int n = account->allObject(&all);

	string s = "[\"";

	for (int i = 0; i < n; i++)
	{
		s.append(all[i]);
		if (i < n - 1) {
			s.append("\",\"");
		}
	}
	s.append("\"]");
	cout << s;
	delete account;
	return s;

}//Adapt类中删除账户函数的实现
bool Adapt::Delete(string id_account) {
	AccountFile* account0 = new AccountFile(id_account);
	account0->setId_account(id_account);
	bool success = account0->deleteObject();
	delete account0;
	if (success)
	{
		cout << "账户已成功删除！" << endl;
		return true;
	}
	else
	{
		cout << "账户删除失败！" << endl;
		return false;
	}
}
//一个小的判断函数
bool AccountFile::judge()
{
	AccountFile* account_file = new AccountFile();
	string* id_account;
	int nums = account_file->allObject(&id_account);
	for (int i = 0; i < nums; i++)
	{
		for (int j = i + 1; j < nums; j++)
		{
			if (id_account[i] == id_account[j]) return true;//有相同的
		}
	}
	delete account_file;
	return false;
}
//四种添加构造
bool Adapt::Add(string id_account, string id_card, string name, string address) {	
	BankAccount *newAccount1=new BankAccount(id_account, id_card, name,address);//通过newAccount1来实现acconut的AccountFile类的副本构造
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//生成副本
	//account1->setId_account(id_account);
	if (account1.judge()) {
		account1.deleteObject();//删除account1指向的文件中的账户
		cout << "账户出现重复，原有账户已删除,并生成一个新账户。" << endl;
		newAccount2.writeObject();//用副本写入新的账户
		delete newAccount1; 
		//BankAccount newBankAccount=BankAccount(id_account, id_card, name, address);
		return true;
			}
	else {
		account1.writeObject();//直接写入新的账户
	    //BankAccount newBankAccount =BankAccount(id_account, id_card, name, address);
		cout << "操作成功，已生成一个新账户。" << endl;
		delete newAccount1;
		return true;
	}
}
bool Adapt::Add(string id_account, string id_card, string name, string address, double balance) {
	//相同的代码重用
	BankAccount* newAccount1 = new BankAccount(id_account, id_card, name, address,balance);//通过newAccount1来实现acconut的AccountFile类的副本构造
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//生成副本
	if (account1.judge()) {
		cout << "账户出现重复，原有账户已删除,并生成一个新账户。" << endl;
		account1.deleteObject();
		newAccount2.writeObject();
		delete newAccount1;
		//BankAccount newBankAccount =BankAccount(id_account, id_card, name, address, balance);
		return true;
	}
	else {
		account1.writeObject();
		delete  newAccount1;
		//BankAccount newBankAccount =BankAccount(id_account, id_card, name, address, balance);
		cout << "操作成功，已生成一个新账户。" << endl;
		return true;
	}
}
bool Adapt::Add(string id_account) {
	//相同代码重用
	BankAccount* newAccount1 = new BankAccount(id_account);//通过newAccount1来实现acconut的AccountFile类的副本构造
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//生成副本
	if (account1.judge()) {
		cout << "账户出现重复，原有账户已删除,并生成一个新账户。" << endl;
		account1.deleteObject();
		newAccount2.writeObject();
		delete newAccount1;
		//AccountFile newBankAccount = AccountFile(id_account);
		//newBankAccount.writeObject();
		return true;
	}
	else {
		account1.writeObject();
		delete newAccount1;
		//AccountFile newBankAccount = AccountFile(id_account);
		//newBankAccount.writeObject();
		cout << "操作成功，已生成一个新账户。" << endl;
		return true;
	}
}
bool Adapt::Add() {
	cout << "添加失败" << endl;
	return true;
}
string Adapt::getAll(string id_account) {
	AccountFile* t_account1 = new AccountFile(id_account);
	BankAccount t_account = t_account1->findAccount(id_account);
	BankAccount* account = &t_account;
	string accountString("{\"id_account\":\"" + account->getId_account() + "\"," + "\"id_card\":\"" + account->getId_card() + "\","
		+ "\"name\":\"" + account->getName() + "\"," + "\"address\":\"" + account->getAddress() + "\"," + "\"balance\":\" " + to_string(account->getBalance()) + "\"}");
	delete t_account1;
	return accountString;
}