#include "AccountFile.h"
#include "Adapt.h"
#include "Text_Binary.h"
#include <fstream>
#include <iostream>
AccountFile::AccountFile(string id_account, BankAccount* object_account)               //���캯�� ���˺��ж���
	: id_account(id_account), object_account(object_account), file_name(FILE_NAME)
{

}
AccountFile::AccountFile(BankAccount* object_account)                                  //���캯�� ���˺��ж���
	: id_account("null"), object_account(object_account), file_name(FILE_NAME)
{

}
AccountFile::AccountFile(string id_account)                                            //���캯�� ���˺��޶���
	: id_account(id_account), object_account(0), file_name(FILE_NAME)
{

}
AccountFile::AccountFile()                                                             //���캯�� ���˺��޶���
	: id_account("null"), object_account(0), file_name(FILE_NAME)
{

}
bool AccountFile::writeObject()                                //д�����
{
	//���������ļ�ת��Ϊ�ı��ļ�
	BinaryToTxt(FILE_NAME);
	ofstream fileout(FILE_NAME, ios::app | ios::binary); //���ļ�
	if (!fileout) //��ȡʧ��
	{
		fileout.close();
		return false;
	}
	//д���������ݳ�Ա
	fileout << object_account->getId_account() << " "
		<< object_account->getId_card() << " "
		<< object_account->getName() << " "
		<< object_account->getAddress() << " "
		<< to_string(object_account->getBalance()) << endl;
	fileout.close();
	//���ı��ļ�ת��Ϊ�������ļ�
	TxtToBinary(FILE_NAME);
	return true;
}
string AccountFile::readObject()                               //��ȡ����
{
	//���������ļ�ת��Ϊ�ı��ļ�
	BinaryToTxt(FILE_NAME);
	//���ļ�
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //��ʧ��
	{
		filein.close();
		BankAccount account;
		return "null"; //Ĭ�϶��� �ַ�����Ա��Ϊnull
	}
	//��ȡ��������
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //��¼��������
	while (filein >> get_id_account && filein >> get_id_card && filein >> get_name && filein >> get_address && filein >> get_balance)
	{
		i++;
	}
	filein.close();
	//��ȡ���ж���
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //�����鸳ֵ
	while (filein0 >> id_account[k] && filein0 >> id_card[k] && filein0 >> name[k] && filein0 >> address[k] && filein0 >> balance[k])
	{
		k++;
	}
	filein0.close();
	//���ı��ļ�ת��Ϊ�������ļ�
	TxtToBinary(FILE_NAME);
	//�ҵ�ָ������
	string account = "";
	for (int j = 0; j < i; j++)
	{
		if (this->id_account == id_account[j])
		{
			double double_balance = atof(const_cast<const char*>(balance[j].c_str())); //���ַ���ת��Ϊ������
			BankAccount bankaccount(id_account[j], id_card[j], name[j], address[j], double_balance);
			//���ҵ����˻��еĶ���ת��Ϊstring������Ϊ����ֵ
			account = "{\"id_account\":\"" + bankaccount.getId_account()
				+ "\"," + "\"id_card\":\"" + bankaccount.getId_card()
				+ "\"," + "\"name\":\"" + bankaccount.getName()
				+ "\"," + "\"address\":\"" + bankaccount.getAddress()
				+ "\"," + "\"balance\":\" " + to_string(bankaccount.getBalance())
				+ "\"}";
			break;
		}
	}
	//�ͷ��ڴ�
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return account;
}
bool AccountFile::deleteObject()                               //ɾ������
{
	//���������ļ�ת��Ϊ�ı��ļ�
	BinaryToTxt(FILE_NAME);
	//���ļ�
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //��ʧ��
	{
		filein.close();
		return false;
	}
	//��ȡ��������
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //��¼��������
	while (filein >> get_id_account && filein >> get_id_card && filein >> get_name && filein >> get_address && filein >> get_balance)
	{
		i++;
	}
	filein.close();
	//��ȡ���ж���
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //�����鸳ֵ
	while (filein0 >> id_account[k] && filein0 >> id_card[k] && filein0 >> name[k] && filein0 >> address[k] && filein0 >> balance[k])
	{
		k++;
	}
	filein0.close();
	//�ҵ�ָ������λ��
	BankAccount account; //Ĭ�϶��� �ַ�����Ա��Ϊnull
	int place = -1; //ָ�������λ��
	int count = i; //��������
	for (int j = 0; j < i; j++)
	{
		if (this->id_account == id_account[j])
		{
			place = j;
			break;
		}
	}
	if (place == -1) //δ�ҵ�ָ������
		return false;
	//ɾ����������д����������
	ofstream fileout(FILE_NAME, ios::out | ios::binary);
	for (int i = 0; i < place; i++)            //д��ɾ������֮ǰ�Ķ���
	{
		fileout << id_account[i] << " "
			<< id_card[i] << " "
			<< name[i] << " "
			<< address[i] << " "
			<< balance[i] << endl;
	}
	for (int i = place + 1; i < count; i++)    //д��ɾ������֮��Ķ���
	{
		fileout << id_account[i] << " "
			<< id_card[i] << " "
			<< name[i] << " "
			<< address[i] << " "
			<< balance[i] << endl;
	}
	fileout.close();
	//���ı��ļ�ת��Ϊ�������ļ�
	TxtToBinary(FILE_NAME);
	//�ͷ��ڴ�
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return true;
}
int AccountFile::allObject(string** result)                    //�����˺�
{
	//���������ļ�ת��Ϊ�ı��ļ�
	BinaryToTxt(FILE_NAME);
	//���ļ�
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //��ʧ��
	{
		filein.close();
		return NULL;
	}
	//��ȡ��������
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //��¼��������
	while (filein >> get_id_account && filein >> get_id_card && filein >> get_name && filein >> get_address && filein >> get_balance)
	{
		i++;
	}
	filein.close();
	//��ȡ���ж���
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //�����鸳ֵ
	while (filein0 >> id_account[k] && filein0 >> id_card[k] && filein0 >> name[k] && filein0 >> address[k] && filein0 >> balance[k])
	{
		k++;
	}
	filein0.close();
	//���ı��ļ�ת��Ϊ�������ļ�
	TxtToBinary(FILE_NAME);
	//д���ַ�������
	string* allObject = new string[i];
	for (int j = 0; j < i; j++)
	{
		allObject[j] = id_account[j];
	}
	//��������
	*result = allObject;
	//�ͷ��ڴ�
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return i;
}
bool AccountFile::judge()                                      //һ��С���жϺ���
{
	string* id_account = NULL;
	int nums = this->allObject(&id_account);
	for (int i = 0; i < nums; i++)
	{
		if (this->id_account == id_account[i]) //����ͬ��
			return true;
	}
	return false;
}
BankAccount AccountFile::findAccount(string input_id_account)  //Adapt����Ҫ�õ���һ������
{
	//���������ļ�ת��Ϊ�ı��ļ�
	BinaryToTxt(FILE_NAME);
	//���ļ�
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //��ʧ��
	{
		filein.close();	
	}
	//��ȡ��������
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //��¼��������
	while (filein >> get_id_account && filein >> get_id_card && filein >> get_name && filein >> get_address && filein >> get_balance)
	{
		i++;
	}
	filein.close();
	//��ȡ���ж���
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string id_account = "";
	string id_card = "";
	string name = "";
	string address = "";
	string balance = "";
	BankAccount account;
	while (filein0 >> id_account && filein0 >> id_card && filein0 >> name && filein0 >> address && filein0 >> balance)
	{
		if(id_account == input_id_account)
		{
			double double_balance = atof(const_cast<const char*>(balance.c_str())); //���ַ���ת��Ϊ������
			account = BankAccount(id_account, id_card, name, address, double_balance);
			break;
		}
	}
	filein0.close();
	//���ı��ļ�ת��Ϊ�������ļ�
	TxtToBinary(FILE_NAME);
	return account;
}
AccountFile::~AccountFile()                                                            //��������
{

}