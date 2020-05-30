#include "AccountFile.h"
#include "Adapt.h"
#include "Text_Binary.h"
#include <fstream>
#include <iostream>
AccountFile::AccountFile(string id_account, BankAccount* object_account)               //构造函数 有账号有对象
	: id_account(id_account), object_account(object_account), file_name(FILE_NAME)
{

}
AccountFile::AccountFile(BankAccount* object_account)                                  //构造函数 无账号有对象
	: id_account("null"), object_account(object_account), file_name(FILE_NAME)
{

}
AccountFile::AccountFile(string id_account)                                            //构造函数 有账号无对象
	: id_account(id_account), object_account(0), file_name(FILE_NAME)
{

}
AccountFile::AccountFile()                                                             //构造函数 无账号无对象
	: id_account("null"), object_account(0), file_name(FILE_NAME)
{

}
bool AccountFile::writeObject()                                //写入对象
{
	//将二进制文件转换为文本文件
	BinaryToTxt(FILE_NAME);
	ofstream fileout(FILE_NAME, ios::app | ios::binary); //打开文件
	if (!fileout) //读取失败
	{
		fileout.close();
		return false;
	}
	//写入对象的数据成员
	fileout << object_account->getId_account() << DEliM
		<< object_account->getId_card() << DEliM
		<< object_account->getName() << DEliM
		<< object_account->getAddress() << DEliM
		<< to_string(object_account->getBalance()) << DEliM;
	fileout.close();
	//将文本文件转化为二进制文件
	TxtToBinary(FILE_NAME);
	return true;
}
string AccountFile::readObject()                               //读取对象
{
	//将二进制文件转换为文本文件
	BinaryToTxt(FILE_NAME);
	//打开文件
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //打开失败
	{
		filein.close();
		BankAccount account;
		return "null"; //默认对象 字符串成员均为null
	}
	//读取对象数量
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //记录对象数量
	while (getline(filein, get_id_account, DEliM)
		&& getline(filein, get_id_card, DEliM)
		&& getline(filein, get_name, DEliM)
		&& getline(filein, get_address, DEliM)
		&& getline(filein, get_balance, DEliM))
	{
		i++;
	}
	filein.close();
	//读取所有对象
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //给数组赋值
	while (1)
	{
		string get_id_account = "null"; //防止溢出
		getline(filein0, get_id_account, DEliM);
		if (get_id_account == "") //判断是否溢出
		{
			break;
		}
		id_account[k] = get_id_account;
		getline(filein0, id_card[k], DEliM);
		getline(filein0, name[k], DEliM);
		getline(filein0, address[k], DEliM);
		getline(filein0, balance[k], DEliM);
		k++;
	}
	filein0.close();
	//将文本文件转化为二进制文件
	TxtToBinary(FILE_NAME);
	//找到指定对象
	string account = "";
	for (int j = 0; j < i; j++)
	{
		if (this->id_account == id_account[j])
		{
			double double_balance = atof(const_cast<const char*>(balance[j].c_str())); //把字符串转换为浮点型
			BankAccount bankaccount(id_account[j], id_card[j], name[j], address[j], double_balance);
			//将找到的账户中的对象转化为string类型作为返回值
			account = "{\"id_account\":\"" + bankaccount.getId_account()
				+ "\"," + "\"id_card\":\"" + bankaccount.getId_card()
				+ "\"," + "\"name\":\"" + bankaccount.getName()
				+ "\"," + "\"address\":\"" + bankaccount.getAddress()
				+ "\"," + "\"balance\":\" " + to_string(bankaccount.getBalance())
				+ "\"}";
			break;
		}
	}
	//释放内存
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return account;
}
bool AccountFile::deleteObject()                               //删除对象
{
	//将二进制文件转换为文本文件
	BinaryToTxt(FILE_NAME);
	//打开文件
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //打开失败
	{
		filein.close();
		return false;
	}
	//读取对象数量
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //记录对象数量
	while (getline(filein, get_id_account, DEliM)
		&& getline(filein, get_id_card, DEliM)
		&& getline(filein, get_name, DEliM)
		&& getline(filein, get_address, DEliM)
		&& getline(filein, get_balance, DEliM))
	{
		i++;
	}
	filein.close();
	//读取所有对象
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //给数组赋值
	while (1)
	{
		string get_id_account = "null"; //防止溢出
		getline(filein0, get_id_account, DEliM);
		if (get_id_account == "") //判断是否溢出
		{
			break;
		}
		id_account[k] = get_id_account;
		getline(filein0, id_card[k], DEliM);
		getline(filein0, name[k], DEliM);
		getline(filein0, address[k], DEliM);
		getline(filein0, balance[k], DEliM);
		k++;
	}
	filein0.close();
	//找到指定对象位置
	BankAccount account; //默认对象 字符串成员均为null
	int place = -1; //指定对象的位置
	int count = i; //对象数量
	for (int j = 0; j < i; j++)
	{
		if (this->id_account == id_account[j])
		{
			place = j;
			break;
		}
	}
	if (place == -1) //未找到指定对象
		return false;
	//删除对象重新写入其他对象
	ofstream fileout(FILE_NAME, ios::out | ios::binary);
	for (int i = 0; i < place; i++)            //写入删除对象之前的对象
	{
		fileout << id_account[i] << DEliM
			<< id_card[i] << DEliM
			<< name[i] << DEliM
			<< address[i] << DEliM
			<< balance[i] << DEliM;
	}
	for (int i = place + 1; i < count; i++)    //写入删除对象之后的对象
	{
		fileout << id_account[i] << DEliM
			<< id_card[i] << DEliM
			<< name[i] << DEliM
			<< address[i] << DEliM
			<< balance[i] << DEliM;
	}
	fileout.close();
	//将文本文件转化为二进制文件
	TxtToBinary(FILE_NAME);
	//释放内存
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return true;
}
int AccountFile::allObject(string** result)                    //所有账号
{
	//将二进制文件转换为文本文件
	BinaryToTxt(FILE_NAME);
	//打开文件
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //打开失败
	{
		filein.close();
		return NULL;
	}
	//读取对象数量
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //记录对象数量
	while (getline(filein, get_id_account, DEliM)
		&& getline(filein, get_id_card, DEliM)
		&& getline(filein, get_name, DEliM)
		&& getline(filein, get_address, DEliM)
		&& getline(filein, get_balance, DEliM))
	{
		i++;
	}
	filein.close();
	//读取所有对象
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string* id_account = new string[i];
	string* id_card = new string[i];
	string* name = new string[i];
	string* address = new string[i];
	string* balance = new string[i];
	int k = 0; //给数组赋值
	while (1)
	{
		string get_id_account = "null"; //防止溢出
		getline(filein0, get_id_account, DEliM);
		if (get_id_account == "") //判断是否溢出
		{
			break;
		}
		id_account[k] = get_id_account;
		getline(filein0, id_card[k], DEliM);
		getline(filein0, name[k], DEliM);
		getline(filein0, address[k], DEliM);
		getline(filein0, balance[k], DEliM);
		k++;
	}
	filein0.close();
	//将文本文件转化为二进制文件
	TxtToBinary(FILE_NAME);
	//写入字符串数组
	string* allObject = new string[i];
	for (int j = 0; j < i; j++)
	{
		allObject[j] = id_account[j];
	}
	//传给输入
	*result = allObject;
	//释放内存
	delete[] id_account;
	delete[] id_card;
	delete[] name;
	delete[] address;
	delete[] balance;
	return i;
}
bool AccountFile::judge()                                      //一个小的判断函数
{
	string* id_account = NULL;
	int nums = this->allObject(&id_account);
	for (int i = 0; i < nums; i++)
	{
		if (this->id_account == id_account[i]) //有相同的
			return true;
	}
	return false;
}
BankAccount AccountFile::findAccount(string input_id_account)  //Adapt类中要用到的一个函数
{
	//将二进制文件转换为文本文件
	BinaryToTxt(FILE_NAME);
	//打开文件
	ifstream filein(FILE_NAME, ios::in | ios::binary);
	if (!filein) //打开失败
	{
		filein.close();	
	}
	//读取对象数量
	string get_id_account, get_id_card, get_name, get_address, get_balance;
	int i = 0; //记录对象数量
	while (getline(filein, get_id_account, DEliM)
		&& getline(filein, get_id_card, DEliM)
		&& getline(filein, get_name, DEliM)
		&& getline(filein, get_address, DEliM)
		&& getline(filein, get_balance, DEliM))
	{
		i++;
	}
	filein.close();
	//读取所有对象
	ifstream filein0(FILE_NAME, ios::in | ios::binary);
	string id_account = "";
	string id_card = "";
	string name = "";
	string address = "";
	string balance = "";
	BankAccount account;
	while (getline(filein0, id_account, DEliM)
		&& getline(filein0, id_card, DEliM)
		&& getline(filein0, name, DEliM)
		&& getline(filein0, address, DEliM)
		&& getline(filein0, balance, DEliM))
	{
		if (id_account == input_id_account)
		{
			double double_balance = atof(const_cast<const char*>(balance.c_str())); //把字符串转换为浮点型
			account = BankAccount(id_account, id_card, name, address, double_balance);
			break;
		}
	}
	filein0.close();
	//将文本文件转化为二进制文件
	TxtToBinary(FILE_NAME);
	return account;
}
AccountFile::~AccountFile()                                                            //析构函数
{

}