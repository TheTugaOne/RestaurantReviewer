#include "Tests.h"
#include <QString>
#include <QDir>
#include "utils/Constants.h"
#include "utils/Utils.h"
#include "storage/sqlite/SQLite.h"

#include <gtest/gtest.h>

using namespace toptal::storage::sqlite;
using namespace toptal::utils;

static const QString kTableName = "Users";

// Do not use Constants.h for this! it is not initialized before static kColoumns
const SqlColumns kColumns =
{
	{"email", ""},
	{"name", ""},
	{"password", ""},
	{"usertype", ""}
};

TEST(RepositoryTest, checkMethods)
{
	// create and init db
	const QString databaseName = Utils::instance().dataDirectory() + kDirSeparator + kDataFolderName
		+ kDirSeparator + "test.sqlite";
	SQLitePtr sqliteDb = SQLite::makePtr(databaseName);

	ASSERT_TRUE(sqliteDb->createTable(kTableName, kColumns));

	SqlColumns columns = { { kEmail, "test" }, {kName, "test" }, {kPassword, "test" }, {kUserType, "test" } };

	ASSERT_TRUE(sqliteDb->insert(kTableName, columns));

	SqlColumn emailColumn = { kEmail, "test" };
	std::vector<QStringList> records;

	ASSERT_TRUE(sqliteDb->getByColumn(kTableName, emailColumn, records));

	ASSERT_NE(records.size(), 0);
	ASSERT_EQ(records[0][0], "test");

	sqliteDb->closeDataBase();
	QSqlDatabase::removeDatabase(databaseName);
	bool test = QDir().remove(databaseName);
}