#include "UserRepository.h"

#include "../utils/Constants.h"
#include <QStringList>

using namespace toptal::utils;
using namespace toptal::entities::users;
using namespace toptal::storage::sqlite;
using namespace toptal::storage::repository;

static const QString kTableName = "Users";

// Do not use Constants.h for this! it is not initialized before static kColoumns
const SqlColumns kColumns =
{
	{"email", ""},
	{"name", ""},
	{"password", ""},
	{"usertype", ""}
};

UserRepository::UserRepository(SQLitePtr sqlDb):
	_sqlite(sqlDb)
{
	assert(_sqlite);

	if (!_sqlite->tableExists(kTableName))
	{
		_sqlite->createTable(kTableName, kColumns);
	}
}

bool UserRepository::login(const QString& email, const QString& password, User& outUser)
{
	SqlColumns columns = { { kEmail, email }, {kPassword, password} };
	std::vector<QStringList> records;

	if (!_sqlite->getByColumns(kTableName, columns, records))
		return false; 

	if (records.size() == 0)
		return false; // invalid username or password

	outUser.setEmail(records[0][0]);
	outUser.setName(records[0][1]);
	outUser.setPassword(records[0][2]);
	outUser.setUserType(records[0][3]);

	return true;
}

bool UserRepository::registerUser(const QString& email, const QString& name, const QString& password, const QString& userType)
{
	SqlColumns columns = { { kEmail, email }, {kName, name}, {kPassword, password}, {kUserType, userType} };

	if (!_sqlite->insert(kTableName, columns))
		return false;

	return true;
}

bool UserRepository::userExists(const QString& email)
{
	SqlColumn emailColumn = { kEmail, email };
	std::vector<QStringList> records;

	if (!_sqlite->getByColumn(kTableName, emailColumn, records))
		return false;

	if (records.size() == 0)
		return false; // user doesn't exist

	return true;
}

bool UserRepository::getAll(UserList& outUsrList)
{
	std::vector<QStringList> records;

	if (!_sqlite->getAll(kTableName, records))
		return false;

	outUsrList = entriesToUserList(records);

	return true;
}

bool UserRepository::getOne(const QString& email, User& outUser)
{
	SqlColumn column(kEmail, email);

	std::vector<QStringList> records;

	if (!_sqlite->getByColumn(kTableName, column, records))
		return false;

	if (records.size() == 0)
		return false; // invalid username or password

	// should be just 1 entry
	outUser.setEmail(records[0][0]);
	outUser.setName(records[0][1]);
	outUser.setPassword(records[0][2]);
	outUser.setUserType(records[0][3]);

	return true;
}

bool UserRepository::deleteUser(const QString& email)
{
	SqlColumns whereCriteria = { { kEmail, email } };

	if (!_sqlite->deleteByColumns(kTableName, whereCriteria))
		return false;

	return true;
}

bool UserRepository::editUser(const QString& email, const User& newUsr)
{
	SqlColumns columnsToBeUpdated = { { kEmail, newUsr.email()}, { kName, newUsr.name() }, 
									{ kPassword, newUsr.password() }, { kUserType, newUsr.stringUserType() } };
	SqlColumns whereCriteria = { { kEmail, email } };

	if (!_sqlite->update(kTableName, columnsToBeUpdated, whereCriteria))
		return false;

	return true;
}

std::unique_ptr<UserRepository> UserRepository::makePtr(SQLitePtr sqlDb)
{
	return std::make_unique<UserRepository>(sqlDb);
}

UserList UserRepository::entriesToUserList(const std::vector<QStringList>& entries)
{
	UserList usrList;
	for (const QStringList& entry : entries)
	{
		User user;
		user.setEmail(entry[0]);
		user.setName(entry[1]);		// password should be retrieved back to UI
		user.setUserType(entry[3]);

		usrList.push_back(user);
	}

	return usrList;
}
