#include "SQLite.h"
#include <QtSql/qsqlquery.h>
#include <QVariant>

using namespace toptal::utils;
using namespace toptal::storage::sqlite;

SQLite::SQLite(const QString& dbPath)
{
	_db = std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
	_db->setDatabaseName(dbPath);
	if (!_db->open())
	{
		// error
	}
}

bool SQLite::tableExists(const QString& tableName)
{
	QStringList tableList = _db->tables();

	return tableList.contains(tableName);
}

bool SQLite::createTable(const QString& tableName, const SqlColumns& columns)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "CREATE TABLE '" + tableName + "' (";

	for (const SqlColumn& column : columns)
	{
		queryStr += " '" + column.name + "' " + "TEXT" + ",";
	}

	// remove the last comma "," character
	queryStr.remove(queryStr.size() - 1, 1);

	queryStr += ");";

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	closeDataBase();

	return true;
}

bool SQLite::getAll(const QString& tableName, std::vector<QStringList>& records)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "SELECT * FROM '" + tableName + "'";

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	while (query.next())
	{
		QStringList lst;
		int i = 0;
		while (!query.value(i).toString().isEmpty())
		{
			lst.push_back(query.value(i).toString());
			i++;
		}

		records.push_back(lst);
	}

	closeDataBase();

	return true;
}

bool SQLite::getByColumn(const QString& tableName, const SqlColumn& selectColumn, std::vector<QStringList>& records)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "SELECT * FROM '" + tableName + "' WHERE ";

	queryStr += selectColumn.name + "='" + selectColumn.value + "'";

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	while (query.next())
	{
		QStringList lst;
		int i = 0;
		while (!query.value(i).toString().isEmpty())
		{
			lst.push_back(query.value(i).toString());
			i++;
		}

		records.push_back(lst);
	}

	closeDataBase();

	return true;
}

bool SQLite::getByColumns(const QString& tableName, const SqlColumns& criteriaList, std::vector<QStringList>& records)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "SELECT * FROM '" + tableName + "' WHERE ";

	for (const SqlColumn& col : criteriaList)
	{
		queryStr += col.name + "='" + col.value + "'" + " AND ";
	}

	// remove the last 'AND' character
	queryStr.remove(queryStr.size() - 4, 4);

	QSqlQuery query;
	query.exec(queryStr);

	// add all columns to outVals
	while (query.next())
	{
		QStringList lst;
		int i = 0;
		while (!query.value(i).toString().isEmpty())
		{
			lst.push_back(query.value(i).toString());
			i++;
		}

		records.push_back(lst);
	}

	closeDataBase();

	return true;
}

bool SQLite::update(const QString& tableName, const SqlColumns& columnsToBeUpdated, const SqlColumns& criteriaList)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "UPDATE '" + tableName + "' SET ";

	for (const SqlColumn& col : columnsToBeUpdated)
	{
		queryStr += col.name + "='" + col.value + "',";
	}

	// delete last ","
	queryStr.remove(queryStr.size() - 1, 1);

	queryStr += " WHERE ";
	for (const SqlColumn& col : criteriaList)
	{
		queryStr += col.name + "='" + col.value + "'";
	}

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	closeDataBase();

	return true;
}

bool SQLite::deleteByColumns(const QString& tableName, const SqlColumns& criteriaList)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "DELETE FROM '" + tableName + "' WHERE ";

	for (const SqlColumn& col : criteriaList)
	{
		queryStr += col.name + "='" + col.value + "'" + " AND ";
	}

	// remove the last 'AND' character
	queryStr.remove(queryStr.size() - 4, 4);

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	closeDataBase();

	return true;
}


bool SQLite::insert(const QString& tableName, const SqlColumns& columns)
{
	if (!_db->isOpen())
	{
		_db->open();
	}

	QString queryStr = "INSERT INTO '" + tableName + "' VALUES(";

	for (const SqlColumn& column : columns)
	{
		queryStr += " '" + column.value + "' " + ",";
	}

	// remove the last comma "," character
	queryStr.remove(queryStr.size() - 1, 1);

	queryStr += ");";

	QSqlQuery query;
	if (!query.exec(queryStr))
		return false;

	closeDataBase();

	return true;
}

void SQLite::closeDataBase()
{
	_db->close();
}

std::shared_ptr<SQLite> SQLite::makePtr(const QString& dbPath)
{
	return std::make_shared<SQLite>(dbPath);
}
