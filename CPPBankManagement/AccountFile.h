#pragma once
#include "BankAccount.h"
#include <string>
#define FILE_NAME "file_bankaccount.txt"   //文件名
using namespace std;
//账户文件类
class AccountFile
{
public:
	//构造函数
	AccountFile(string id_account, BankAccount* object_account);       //构造函数 有账号有对象
	AccountFile(BankAccount* object_account);                          //构造函数 无账号有对象
	AccountFile(string id_account);                                    //构造函数 有账号无对象
	AccountFile();                                                     //构造函数 无账号无对象
	//读写对象
	bool writeObject();                                                //写入对象
	string readObject();                                          //读取对象
	bool deleteObject();                                               //删除对象
	BankAccount findAccount(string id_account);
	int allObject(string** result);								       //所有账号
	//修改成员
	void setBankAccount(BankAccount* object_account)                   //修改此类成员中账户成员，并非修改银行账户
	{
		this->object_account = object_account;
	}
	void setId_account(string id_account)                              //修改此类成员中账号成员，并非修改银行账号
	{
		this->id_account = id_account;
	}
	~AccountFile();                                                    //析构函数
	bool judge();                                                      //一个判断是否有重复账户的函数
private:
	string file_name;                      //文件名
	string id_account;                     //账号
	BankAccount* object_account;           //账户对象
};
