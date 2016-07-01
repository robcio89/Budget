#pragma once
#include <gtest/gtest.h>
#include "../SMSITBudgetClient/SMSITBudgetClient/abstract_authorizer.h"
#include <memory>

struct authorizer_file_test : public testing::Test
{
public:
	authorizer_file_test()
		: login_fine("Mateusz")
		, password_fine("Matheo321")
		, login_wrong("An")
		, password_wrong("An")
		, file_name_fine("Accounts.smsitdb")
		, file_name_wrong("wrong_name.smsitdb")
	{
		prepareFileDbs();
		authorizer = std::make_unique<authorizer_file>(file_name_fine);
	}

	virtual ~authorizer_file_test()
	{
		deleteExistingFileDbs();
	}

	void prepareFileDbs();
	void deleteExistingFileDbs();
	void prepareFineFileDb();
	void prepareWrongFileDb();

	std::unique_ptr<abstract_authorizer> authorizer;
	std::string login_fine, password_fine;
	std::string login_wrong, password_wrong;
	std::string file_name_fine, file_name_wrong;
};

