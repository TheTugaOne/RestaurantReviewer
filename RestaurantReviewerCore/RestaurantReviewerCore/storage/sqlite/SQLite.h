#ifndef SQLITE_H
#define SQLITE_H

#include <memory>
#include <QtSql/qsqldatabase.h>
#include <QStringList>

#include "../utils/Constants.h"

namespace toptal
{
namespace storage
{
namespace sqlite
{

/*!
*	\class	SQLite.
*	\brief	Interface that must be implemented by classes that offer serialization.
*/
class SQLite
{
public:
	SQLite(const QString& dbPath);

	bool	tableExists(const QString& tableName);

	bool	createTable(const QString& tableName, const utils::SqlColumns& columns);

	bool	getAll(const QString& tableName, std::vector<QStringList>& outVals);

	bool	getByColumn(const QString& tableName, const utils::SqlColumn& selectColumn, std::vector<QStringList>& records);

	bool	getByColumns(const QString& tableName, const utils::SqlColumns& criteriaList, std::vector<QStringList>& records);

	bool	update(const QString& tableName, const utils::SqlColumns& columnsToBeUpdated, const utils::SqlColumns& criteriaList);

	bool	deleteByColumns(const QString& tableName, const utils::SqlColumns& criteriaList);

	bool	insert(const QString& tableName, const utils::SqlColumns& columns);

	void	closeDataBase();

	static std::shared_ptr<SQLite> makePtr(const QString& dbPath);

private:
	std::shared_ptr<QSqlDatabase> _db;

}; // class SQLite

using SQLitePtr = std::shared_ptr<SQLite>;

}

} } // toptal::storage::sqlite

#endif // SQLITE_H
