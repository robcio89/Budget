#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

//! Authorizer Interface
/*!
Interface for all Authorizers.
This interface will be used for all made authorizers.
*/
class abstract_authorizer
{
public:
	abstract_authorizer() = default;
	//! Login into user account.
	/*!
	\brief brief about that function
	\details login function checks user name and password in conneted database.
	\param a_user defines user name
	\param a_password defines password (plain text)
	\return 0 as success, other number as fault.
	*/
	virtual int login(const std::string& user, const std::string& password) = 0;

	//! Allows to create new account.
	/*!
	Function creates new account
	\param a_user defines name of new user (at least 5 characters)
	\param a_password defines password for new account (plain text, at least 5 characters)
	\return 0 as success
	\return 1 as error: wrong login
	\return 2 as error: wrong password
	\return 3 as error: login already exists

	*/
	virtual int create_account(const std::string & a_user, const std::string & a_password) = 0;
	virtual ~abstract_authorizer() = default;
};

class authorizer_file : public abstract_authorizer
{
public:
	authorizer_file(const std::string& file_name);
	int login(const std::string& user, const std::string& password) override;
	int create_account(const std::string& name, const std::string& password) override;

private:
	void open_file_db(const std::string& file_name);
	void load_file_db(const std::string& file_name);

private:
	std::fstream m_file_db;
	std::unordered_map<std::string, std::string> accounts;
};

