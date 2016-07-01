#include "authorizer_file_test.h"
#include <fstream>

void authorizer_file_test::prepareFileDbs()
{
	deleteExistingFileDbs();
	prepareFineFileDb();
	prepareWrongFileDb();
}

void authorizer_file_test::deleteExistingFileDbs()
{
	remove(file_name_fine.c_str());
	remove(file_name_wrong.c_str());
}

void authorizer_file_test::prepareFineFileDb()
{
	std::fstream file_db;
	file_db.open(file_name_fine.c_str(), std::fstream::out);
	if (!file_db.good())
	{
		std::string msg = "Could not open file: " + file_name_fine;
		throw std::exception(msg.c_str());
	}
	file_db << login_fine << " " << password_fine << "\n";
	file_db.close();
}

void authorizer_file_test::prepareWrongFileDb()
{
	std::fstream keep_file_db;
	keep_file_db.open(file_name_wrong.c_str(), std::fstream::out);
	keep_file_db.close();
	_chmod(file_name_wrong.c_str(), _S_IREAD);
}
