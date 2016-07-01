#include "authorizer_file_test.h"

TEST_F(authorizer_file_test, OpenFileDB)
{
	EXPECT_THROW(authorizer_file test_authorizer(file_name_wrong), std::exception);

	try {
		authorizer_file test_authorizer(file_name_wrong);
	}
	catch (std::exception& exc) {
		std::string expection_msg = "Could not open file: " + file_name_wrong;
		EXPECT_STREQ(exc.what(), expection_msg.c_str());
	}

	EXPECT_NO_THROW(authorizer_file(file_name_fine.c_str()));
}

TEST_F(authorizer_file_test, login_and_password_wrong)
{
	EXPECT_EQ(authorizer->login(login_wrong, password_wrong), 1);
}

TEST_F(authorizer_file_test, login_ok_password_wrong)
{
	EXPECT_EQ(authorizer->login(login_fine, password_wrong), 1);
}

TEST_F(authorizer_file_test, login_wrong_password_ok)
{
	EXPECT_EQ(authorizer->login(login_wrong, password_fine), 1);
}

TEST_F(authorizer_file_test, login_and_password_ok)
{
	EXPECT_EQ(authorizer->login(login_fine, password_fine), 0);
}

TEST_F(authorizer_file_test, create_account_new_login_and_password)
{
	std::string new_login = "some_new_login";
	std::string new_password = "some_new_password";

	EXPECT_EQ(authorizer->create_account(new_login, new_password), 0);
}

TEST_F(authorizer_file_test, create_account_login_wrong_password_ok)
{
	EXPECT_EQ(authorizer->create_account(login_wrong, password_fine), 1);
}

TEST_F(authorizer_file_test, create_account_login_ok_password_wrong)
{
	EXPECT_EQ(authorizer->create_account(login_fine, password_wrong), 2);
}

TEST_F(authorizer_file_test, create_account_login_and_password_wrong)
{
	EXPECT_EQ(authorizer->create_account(login_wrong, password_wrong), 1);
}

TEST_F(authorizer_file_test, create_account_login_and_password_ok)
{
	EXPECT_EQ(authorizer->create_account(login_fine, password_fine), 3);
}
