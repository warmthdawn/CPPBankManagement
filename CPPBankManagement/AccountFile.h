#pragma once
#include "BankAccount.h"
#include <string>
#define FILE_NAME "file_bankaccount.txt"   //�ļ���
using namespace std;
//�˻��ļ���
class AccountFile
{
public:
	//���캯��
	AccountFile(string id_account, BankAccount* object_account);       //���캯�� ���˺��ж���
	AccountFile(BankAccount* object_account);                          //���캯�� ���˺��ж���
	AccountFile(string id_account);                                    //���캯�� ���˺��޶���
	AccountFile();                                                     //���캯�� ���˺��޶���
	//��д����
	bool writeObject();                                                //д�����
	string readObject();                                          //��ȡ����
	bool deleteObject();                                               //ɾ������
	BankAccount findAccount(string id_account);
	int allObject(string** result);								       //�����˺�
	//�޸ĳ�Ա
	void setBankAccount(BankAccount* object_account)                   //�޸Ĵ����Ա���˻���Ա�������޸������˻�
	{
		this->object_account = object_account;
	}
	void setId_account(string id_account)                              //�޸Ĵ����Ա���˺ų�Ա�������޸������˺�
	{
		this->id_account = id_account;
	}
	~AccountFile();                                                    //��������
	bool judge();                                                      //һ���ж��Ƿ����ظ��˻��ĺ���
private:
	string file_name;                      //�ļ���
	string id_account;                     //�˺�
	BankAccount* object_account;           //�˻�����
};
