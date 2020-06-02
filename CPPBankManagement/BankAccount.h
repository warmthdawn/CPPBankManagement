#pragma once
#include <string>

using namespace std;

//�����˻���
class BankAccount
{
public:
	//���캯��
	BankAccount(string id_account, string id_card, string name, string address, double banlance);  //���캯�� �������
	BankAccount(string id_account, string id_card, string name, string address);                   //���캯�� ���������
	BankAccount(string id_account);                                                                //���캯�� ֻ���˺�
	BankAccount();                                                                                 //���캯�� Ĭ�������ַ���Ϊ"null"
	//�õ���Ϣ
	string getId_account() { return id_account; }                                  //�õ��˺�
	string getId_card() { return id_card; }                                        //�õ����֤����
	string getName() { return name; }                                              //�õ�����
	string getAddress() { return address; }                                        //�õ���ַ
	double getBalance() { return balance; }                                        //�õ����
	//�޸���Ϣ
	void setId_card(string id_card) { this->id_card = id_card; }                   //�޸����֤����
	void setName(string name) { this->name = name; }                               //�޸�����
	void setAddress(string address) { this->address = address; }                   //�޸ĵ�ַ
	void setBalance(double balance) { this->balance = balance; }                   //�޸����
	//��������
	~BankAccount();
private:
	string id_account;              //�˺�
	string id_card;                 //���֤����
	string name;                    //����
	string address;                 //��ַ
	double balance;                 //���
};