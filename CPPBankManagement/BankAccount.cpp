#include "BankAccount.h"
BankAccount::BankAccount(string id_account, string id_card, string name, string address, double balance)   //构造函数 包括余额
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(balance)
{

}
BankAccount::BankAccount(string id_account, string id_card, string name, string address)                   //构造函数 不包括余额
	: id_account(id_account), id_card(id_card), name(name), address(address), balance(0.00)
{
	
}
BankAccount::BankAccount(string id_account)                                                                //构造函数 只有账号
	: id_account(id_account), id_card(""), name(""), address(""), balance(0.00)
{

}
BankAccount::BankAccount()                                                                                 //构造函数 默认所有字符串为"null"
	: id_account("null"), id_card("null"), name("null"), address("null"), balance(0.00)
{
	
}
BankAccount::~BankAccount()                                                                                //析构函数
{
	
}