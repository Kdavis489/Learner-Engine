#ifndef ACCT_H
#define ACCT_H

int username;
int password;

enum class menu
{
	menu,
	login,
	createAcc,
	DelAcc,
	credits,
};

//read if account exists::verify pass::Login
struct login
{
	std::string Getusername();
	std::string Getpassword();
};

//create player account
struct createAcc
{
	std::string setUsername();
	std::string setPassword();
};

#endif // !ACCT_H
