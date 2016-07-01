#include "abstract_authorizer.h"
#include <iostream>
#include <sstream> 

authorizer_file::authorizer_file(const std::string& file_name)
{
	open_file_db(file_name);
	load_file_db(file_name);
}

void authorizer_file::open_file_db(const std::string& file_name)
{
	m_file_db.open(file_name.c_str(), std::fstream::out | std::fstream::in);
	if (!m_file_db.good())
	{
		std::string msg = "Could not open file: " + file_name;
		throw exception(msg.c_str());
	}
}

void authorizer_file::load_file_db(const std::string& file_name)
{
	string line;
	while (getline(m_file_db, line))
	{
		std::istringstream temp_istring_stream(line);
		string name, password;

		if (!(temp_istring_stream >> name >> password))
		{
			throw exception("DB is corrupted!");
		}

		accounts.insert(make_pair(name, password));
	}
}

int authorizer_file::login(const string& name, const string& password)
{
	if (accounts.empty())
	{
		return 1;
	}

	auto account_it = accounts.find(name);
	if (account_it == accounts.end())
	{
		return 1;
	}

	const auto & account_password = account_it->second;
	if (password != account_password)
	{
		return 1;
	}

	return 0;
}

int authorizer_file::create_account(const string& name, const string& password)
{
	if (name.size() < 5)
	{
		return 1;
	}

	if (password.size() < 5)
	{
		return 2;
	}

	auto account_it = accounts.find(name);
	if (account_it != accounts.end())
	{
		return 3;
	}

	accounts.insert(make_pair(name, password));
	m_file_db << name << " " << name << "\n";
	return 0;
}
