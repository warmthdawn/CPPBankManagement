#pragma once
#include<iostream>
#include<string>
#include"BankAccount.h"
#include"AccountFile.h"
//xglҪ���ת����
class Adapt {
public:
	Adapt();
	string All();
	bool Delete(string id_account);
    Adapt(string id_account, string id_card, string name, string address, double balance);  //���캯�� �������
	Adapt(string id_account, string id_card, string name, string address);                   //���캯�� ���������
	Adapt(string id_account);                                                                //���캯�� ֻ���˺�	
	bool Add(string id_account, string id_card, string name, string address, double balance);  
	bool Add(string id_account, string id_card, string name, string address);                  
	bool Add(string id_account);                                                                
	bool Add();
	string getAll(string id_account);
private:
	string id_account;              //�˺�
	string id_card;                 //���֤����
	string name;                    //����
	string address;                 //��ַ
	double balance;                 //���

};