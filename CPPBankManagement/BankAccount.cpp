#include <string>
#include "BankAccount.h"

//构造函数 包括余额
BankAccount::BankAccount(string id_account, string id_card, string name, string address, double balance)
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(balance)
{

}

//构造函数 不包括余额
BankAccount::BankAccount(string id_account, string id_card, string name, string address)
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(0.00)
{
	
}

//构造函数 只有账号
BankAccount::BankAccount(string id_account)
	: id_account(id_account), id_card(""), name(""), address(""), balance(0.00)
{

}

//构造函数 默认所有字符串为"null"
BankAccount::BankAccount()
	: id_account("null"), id_card("null"), name("null"), address("null"), balance(0.00)
{
	
}

//析构函数
BankAccount::~BankAccount()
{
	
}