#include<iostream>
#include<string>
#include"AccountFile.h"
#include"Adapt.h"

//���캯��
Adapt::Adapt(string id_account, string id_card, string name, string address, double balance)   //���캯�� �������
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(balance)
{

}
Adapt::Adapt(string id_account, string id_card, string name, string address)                   //���캯�� ���������
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(0.00)
{

}
Adapt::Adapt(string id_account)                                                                //���캯�� ֻ���˺�
	: id_account(id_account), id_card(""), name(""), address(""), balance(0.00)
{

}
Adapt::Adapt()                                                                                 //���캯�� Ĭ�������ַ���Ϊ"null"
	: id_account("null"), id_card("null"), name("null"), address("null"), balance(0.00)
{

}
//ת��������ʵ��
 string Adapt::All() {

	//ʵ�ֶ�����ÿ�����ݵ�ת��
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

}//Adapt����ɾ���˻�������ʵ��
bool Adapt::Delete(string id_account) {
	AccountFile* account0 = new AccountFile(id_account);
	account0->setId_account(id_account);
	bool success = account0->deleteObject();
	delete account0;
	if (success)
	{
		cout << "�˻��ѳɹ�ɾ����" << endl;
		return true;
	}
	else
	{
		cout << "�˻�ɾ��ʧ�ܣ�" << endl;
		return false;
	}
}
//һ��С���жϺ���
bool AccountFile::judge()
{
	AccountFile* account_file = new AccountFile();
	string* id_account;
	int nums = account_file->allObject(&id_account);
	for (int i = 0; i < nums; i++)
	{
		for (int j = i + 1; j < nums; j++)
		{
			if (id_account[i] == id_account[j]) return true;//����ͬ��
		}
	}
	delete account_file;
	return false;
}
//������ӹ���
bool Adapt::Add(string id_account, string id_card, string name, string address) {	
	BankAccount *newAccount1=new BankAccount(id_account, id_card, name,address);//ͨ��newAccount1��ʵ��acconut��AccountFile��ĸ�������
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//���ɸ���
	//account1->setId_account(id_account);
	if (account1.judge()) {
		account1.deleteObject();//ɾ��account1ָ����ļ��е��˻�
		cout << "�˻������ظ���ԭ���˻���ɾ��,������һ�����˻���" << endl;
		newAccount2.writeObject();//�ø���д���µ��˻�
		delete newAccount1; 
		//BankAccount newBankAccount=BankAccount(id_account, id_card, name, address);
		return true;
			}
	else {
		account1.writeObject();//ֱ��д���µ��˻�
	    //BankAccount newBankAccount =BankAccount(id_account, id_card, name, address);
		cout << "�����ɹ���������һ�����˻���" << endl;
		delete newAccount1;
		return true;
	}
}
bool Adapt::Add(string id_account, string id_card, string name, string address, double balance) {
	//��ͬ�Ĵ�������
	BankAccount* newAccount1 = new BankAccount(id_account, id_card, name, address,balance);//ͨ��newAccount1��ʵ��acconut��AccountFile��ĸ�������
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//���ɸ���
	if (account1.judge()) {
		cout << "�˻������ظ���ԭ���˻���ɾ��,������һ�����˻���" << endl;
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
		cout << "�����ɹ���������һ�����˻���" << endl;
		return true;
	}
}
bool Adapt::Add(string id_account) {
	//��ͬ��������
	BankAccount* newAccount1 = new BankAccount(id_account);//ͨ��newAccount1��ʵ��acconut��AccountFile��ĸ�������
	AccountFile account1(id_account, newAccount1);
	AccountFile newAccount2(id_account, newAccount1);//���ɸ���
	if (account1.judge()) {
		cout << "�˻������ظ���ԭ���˻���ɾ��,������һ�����˻���" << endl;
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
		cout << "�����ɹ���������һ�����˻���" << endl;
		return true;
	}
}
bool Adapt::Add() {
	cout << "���ʧ��" << endl;
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