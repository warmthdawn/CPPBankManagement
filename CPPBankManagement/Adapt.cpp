#include <iostream>
#include <string>
#include "AccountFile.h"
#include "Adapt.h"

//���캯��
Adapt::Adapt() {

}

//Adapt����ɾ���˻�������ʵ��
bool Adapt::Delete(string id_account) {
	AccountFile* account0 = new AccountFile(id_account);
	account0->setId_account(id_account);
	bool success = account0->deleteObject();
	delete account0;
	return success ? true : false;
}

//��ӹ��� �������
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

//��ӹ��� ���������
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

//��ӹ��� ֻ���˺�
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

//��ӹ��� Ĭ�������ַ���Ϊ"null"
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

//�õ�ָ���˻���Ϣ
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

//�õ������˺�
string Adapt::All() {
	//ʵ�ֶ�����ÿ�����ݵ�ת��
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

//��������
Adapt::~Adapt() {

}