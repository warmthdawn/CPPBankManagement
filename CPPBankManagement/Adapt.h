#pragma once
#include <iostream>
#include <string>
#include "BankAccount.h"
#include "AccountFile.h"

//ת����
class Adapt {
public:
	//���캯��
	Adapt();                                                                                    //���캯��
	//����˺�
	bool Add(string id_account, string id_card, string name, string address, double balance);   //����˻� �������
	bool Add(string id_account, string id_card, string name, string address);                   //����˻� ���������     
	bool Add(string id_account);                                                                //����˻� ֻ���˺�
	bool Add();                                                                                 //����˻� Ĭ�������ַ���Ϊ"null"
	//ɾ���˻�
	bool Delete(string id_account);                                                             //ɾ���˻�
	//�õ�ָ���˻���Ϣ
	string getAll(string id_account);                                                           //�õ�ָ���˻���Ϣ
	//�õ������˺�
	string All();                                                                               //�õ������˺�
	//��������
	~Adapt();                                                                                   //��������
};